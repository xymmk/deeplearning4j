/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// @author Yurii Shyrma (iuriish@yahoo.com), created on 25.11.2017.
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_softmax_cross_entropy_loss)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
namespace ops  {


//////////////////////////////////////////////////////////////////////////
CUSTOM_OP_IMPL(softmax_cross_entropy_loss, 3, 1, false, 1, 1) {

  	NDArray<T>* logits  = INPUT_VARIABLE(0);
    NDArray<T>* weights = INPUT_VARIABLE(1);
    NDArray<T>* labels  = INPUT_VARIABLE(2);
    NDArray<T>* output  = OUTPUT_VARIABLE(0);

    int reductionMode = INT_ARG(0);			// 0 - "none"; 1 - "weighted_sum";  2 - "weighted_mean";  3 - "weighted_sum_by_nonzero_weights"
    T labelsSmoothing = T_ARG(0);
    
    // input validation    		       
    REQUIRE_TRUE(labels->isSameShape(logits), 0, "SOFTMAX_CROSS_ENTROPY_LOSS OP: labels and logits arrays must have the same shapes, but got %s and %s correspondingly !", ShapeUtils<T>::shapeAsString(labels).c_str(), ShapeUtils<T>::shapeAsString(logits).c_str());    
    // weights array can be single scalar or has the same shape as output, and must be broadcastable to output shape
    REQUIRE_TRUE(!(!weights->isScalar() && weights->rankOf() != output->rankOf() && !output->isScalar()), 0, "SOFTMAX_CROSS_ENTROPY_LOSS OP: weights array must have the same rank as output array, but got %i and %i correspondingly!", weights->rankOf(), output->rankOf());
    // check whether broadcast operation is possible for weights array
    if(!weights->isScalar())
    	for (int i = 0; i < weights->rankOf(); ++i)
        	REQUIRE_TRUE(!(weights->shapeOf()[i] != output->shapeOf()[i] && weights->shapeOf()[i] != 1 && !output->isScalar()), 0, "SOFTMAX_CROSS_ENTROPY_LOSS OP: shape of weights array %s is not broadcastable to output array shape %s !", ShapeUtils<T>::shapeAsString(weights).c_str(), ShapeUtils<T>::shapeAsString(output).c_str());

	// If label_smoothing is nonzero, smooth the labels towards 1/num_classes: new_onehot_labels = onehot_labels * (1 - label_smoothing) + label_smoothing / num_classes
	NDArray<T>* newLabels = labels;
	if(labelsSmoothing != (T)0.) {
		T numClasses = (T)labels->sizeAt(1);
		auto smooth = LAMBDA_T(value, labelsSmoothing, numClasses) { return value * ((T)1. - labelsSmoothing) + labelsSmoothing/numClasses; };
    	newLabels = new NDArray<T>(*labels);
    	newLabels->applyLambda(smooth);  
	}	
		
	std::vector<int> dimensions = {-1};
	// Find the max in each batch, resulting in a tensor of shape [batch]
	NDArray<T> logitsMax = logits->template reduceAlongDims<simdOps::Max<T>>(dimensions, true);
	// Subtract the max in batch b from every element in batch b, broadcasts along the batch dimension.
	NDArray<T> shiftedLogits = *logits - logitsMax;
	// exp(logits - max_logits)
	NDArray<T> expShiftedLogits = shiftedLogits.template transform<simdOps::Exp<T>>();
	// sum_{class} (exp(logits - max_logits))
	NDArray<T> sumExp = expShiftedLogits.template reduceAlongDims<simdOps::Sum<T>>(dimensions, true);	
	// log(sum(exp(logits - max_logits)))
	NDArray<T> logSumExp = sumExp.template transform<simdOps::Log<T>>();
	// sum(-labels *((logits - max_logits) - log(sum(exp(logits - max_logits))))) along classes
	// The subtraction broadcasts along the batch dimension
	NDArray<T> weightedLosses = ((-*newLabels)*(shiftedLogits - logSumExp)).template reduceAlongDims<simdOps::Sum<T>>(dimensions);
	
	// perform weights broadcasting/tile to weightedLosses if it is necessary
	NDArray<T>* weightsBroad = weights;	
	if(!weights->isScalar() && !weights->isSameShape(&weightedLosses)) {
		// evaluate repeat dimensions for tile operation
		std::vector<Nd4jLong> reps(weightedLosses.rankOf());
		for(int i = 0; i < reps.size(); ++i)
			reps[i] = weightedLosses.shapeOf()[i] / weights->shapeOf()[i];
		weightsBroad = new NDArray<T>(weights->tile(reps));
	}	

    // multiply weightedLosses on weights
 	if(weights->isScalar())
 		weightedLosses *= (*weights)(0);
 	else
 		weightedLosses *= (*weights); 	
 	// regard 4 possible reduction modes below
 	REQUIRE_TRUE(reductionMode==0 || reductionMode==1 || reductionMode==2 || reductionMode==3, 0, "SOFTMAX_CROSS_ENTROPY_LOSS OP: reduction mode value is not acceptable, possible values are 0, 1, 2, 3, but got %i instead!", reductionMode);
	switch (reductionMode) {
		case 0:												// 0 - "none", un-reduced weighted losses with the same shape as labels.
			output->assign(&weightedLosses);
			break;
		
		case 1: {											// 1 - "weighted_sum", output is scalar and equal to sum of all elements of weightedLosses array
			(*output)(0) = weightedLosses.template reduceNumber<simdOps::Sum<T>>();
			break;
		}
		case 2: {											// 2 - "weighted_mean", output is scalar and equal to sum of all elements of weightedLosses array divided by sum of all elements of weightsBroad array
			T sum;
			if (weights->isScalar())
				sum = (*weights)(0) * weightedLosses.lengthOf();
			else 
				sum = weightsBroad->template reduceNumber<simdOps::Sum<T>>();
			
			if (sum == (T)0.)
				(*output)(0) = (T)0.;
			else 
				(*output)(0) = weightedLosses.template reduceNumber<simdOps::Sum<T>>() / sum;
			break;
		}
		case 3: {											// 3 - "weighted_sum_by_nonzero_weights", output is scalar and equal to scalar sum of all elements of weightedLosses array divided by number of non-zero weights
			int numOfNonZeroWeights = 0;
			if(weights->isScalar()) {
				if((*weights)(0) != (T)0.)
					numOfNonZeroWeights = weightedLosses.lengthOf();
			}
			else {
				for(int i = 0; i < weightsBroad->lengthOf(); ++i)
					if((*weightsBroad)(i) != (T)0.)
						++numOfNonZeroWeights;
			}

			if (numOfNonZeroWeights == 0)
				(*output)(0) = (T)0.;
			else 
				(*output)(0) = weightedLosses.template reduceNumber<simdOps::Sum<T>>() / numOfNonZeroWeights;
			break;
		}
	}


    STORE_RESULT(*output);

    if(weightsBroad != weights)
    	delete weightsBroad;
    if(newLabels != labels)
    	delete newLabels; 
   		
    return Status::OK();
}


DECLARE_SHAPE_FN(softmax_cross_entropy_loss) {
	
	auto logitsShapeInfo  = inputShape->at(0);
    auto labelsShapeInfo  = inputShape->at(2);

	// labels and logits must have the same shapes 
    REQUIRE_TRUE(shape::shapeEquals(logitsShapeInfo, labelsShapeInfo), 0, "SOFTMAX_CROSS_ENTROPY_LOSS OP: labels and logits arrays must have the same shapes, but got %s and %s correspondingly!", ShapeUtils<T>::shapeAsString(labelsShapeInfo).c_str(), ShapeUtils<T>::shapeAsString(logitsShapeInfo).c_str());    

	std::vector<int> dimensions = {-1};
    auto reducedShapeInfo = ShapeUtils<T>::evalReduceShapeInfo(shape::order(labelsShapeInfo), dimensions, labelsShapeInfo, false, true, block.getWorkspace());
   
    // if scalar is required
    const int rank = 2;
    if(INT_ARG(0) != 0) {
    	RELEASE(reducedShapeInfo, block.workspace());
    	ALLOCATE(reducedShapeInfo, block.getWorkspace(), shape::shapeInfoLength(rank), Nd4jLong);
    	reducedShapeInfo[0] = rank;
    	reducedShapeInfo[1] = reducedShapeInfo[2] = reducedShapeInfo[3] = reducedShapeInfo[4] = 1;
    	reducedShapeInfo[5] = 0;
    	reducedShapeInfo[6] = 1;
    	reducedShapeInfo[7] = 99;    	
    }    

    return SHAPELIST(reducedShapeInfo);    

}

// INT_ARG(0) - reduction mode

}
}

#endif