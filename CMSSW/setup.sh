#!/bin/bash

STOP=""

VARS=""

function addVar
{
    VARS=$VARS" "$1"="$2
}

function execute 
{
    if [ -z "$STOP" ]; then
        echo -n $@ " ... "
        out=$(eval $@ 2>&1)
        ret=$?

        if [ $ret -eq 0 ]; then
            echo "ok"
        else
            echo "error"
            STOP=$out
        fi
    fi
}

export SCRAM_ARCH=slc6_amd64_gcc530
addVar SCRAM_ARCH $SCRAM_ARCH

CMSSWVERSION="CMSSW_8_0_25"

execute "scramv1 project CMSSW $CMSSWVERSION"
cd $CMSSWVERSION/src

eval `scramv1 runtime -sh`
execute "git cms-init"


execute "git clone git@github.com:matt-komm/DeepNTuples.git"
cd DeepNTuples
git submodule init
git submodule update

cd -
git cms-merge-topic -u mverzett:DeepFlavour-from-CMSSW_8_0_21
mkdir RecoBTag/DeepFlavour/data/
cd RecoBTag/DeepFlavour/data/
wget http://home.fnal.gov/~verzetti/DeepFlavour/training/DeepFlavourNoSL.json
cd -

ln -s ../../LLPTagger

execute "scram b -j10"



