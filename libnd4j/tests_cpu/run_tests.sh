#!/usr/bin/env bash

################################################################################
# Copyright (c) 2015-2018 Skymind, Inc.
#
# This program and the accompanying materials are made available under the
# terms of the Apache License, Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0.
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
#
# SPDX-License-Identifier: Apache-2.0
################################################################################


set -exo pipefail

IS_RELEASE='true'
OSARCH=$(arch)

if [ -f /opt/rh/devtoolset-7/enable ]; then
    source /opt/rh/devtoolset-7/enable
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
    export CC=$(ls -1 /usr/local/bin/gcc-? | head -n 1)
    export CXX=$(ls -1 /usr/local/bin/g++-? | head -n 1)
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
    export CC=$(which gcc)
    export CXX=$(which g++)
fi

parse_commandline ()
{
	while test $# -gt 0
	do
		_key="$1"
		case "$_key" in
			--release=*)
				IS_RELEASE="${_key##--release=}"
				;;
			*)
				;;
		esac
		shift
	done
}

parse_commandline "$@"

if [[ "$IS_RELEASE" == "false" ]]; then
    ../buildnativeoperations.sh -t -b debug
else
    ../buildnativeoperations.sh -t -b release
fi

if [[ -f /etc/redhat-release && "$OSARCH" == "x86_64" && "$IS_RELEASE" == "false" ]]; then
    # sudo is used as workaround for LeakSanitizer that requires root permissions on CentOS
    sudo bash -c '../blasbuild/cpu/tests_cpu/layers_tests/runtests --gtest_output="xml:../target/surefire-reports/TEST-results.xml"'
    sudo chown -R "${USER:-jenkins}":"${USER:-jenkins}" ../target
else
    ../blasbuild/cpu/tests_cpu/layers_tests/runtests --gtest_output="xml:../target/surefire-reports/TEST-results.xml"
fi
