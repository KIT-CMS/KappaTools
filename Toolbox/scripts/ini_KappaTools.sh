#!/bin/bash

if [ ! -z "$ZSH_VERSION" ]; then
	this_file="${(%):-%x}"
else
	this_file="${BASH_SOURCE[0]}"
fi


# get path of KappaTools installation for bash
if [[ "$this_file" == *"${CMSSW_BASE}/bin/"* || "$this_file" == *"${CMSSW_BASE}/src/KappaTools/"* ]]; then
        export KAPPATOOLSPATH="$CMSSW_BASE/src/KappaTools"
else
        # get KappaTools dir relative to location of this script for bash
        export KAPPATOOLSPATH=$(readlink -f $(dirname $(readlink -f "$this_file"))/../..)
fi

export KAPPAPATH=$(readlink -f $KAPPATOOLSPATH/../Kappa)

if [[ ! -n ${CMSSW_BASE} ]] || [[ ! $(dirname $(readlink -mf "$this_file")) == ${CMSSW_BASE}* ]];  # i.e. 'if installed inside CMSSW'
then
	# configurations needed for compilation of C++ code
	#export BOOSTPATH=$(ls /afs/cern.ch/cms/${SCRAM_ARCH}/external/boost/* -d | tail -n 1)/
	export LD_LIBRARY_PATH="$KAPPATOOLSPATH/lib:$KAPPAPATH/lib:$LD_LIBRARY_PATH"
fi
