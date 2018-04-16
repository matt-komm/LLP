#!/bin/bash

STOP=""


function execute() 
{
    if [ -z "$STOP" ]; then
        echo -n $@ " ... "
        out=$($@ 2>&1)
        ret=$?

        if [ $ret -eq 0 ]; then
            echo "ok"
        else
            echo "error"
            STOP=$out
            return 1
        fi
    fi
}

function run_setup()
{
    source /vols/grid/cms/setup.sh
    
    export SCRAM_ARCH=slc6_amd64_gcc530

    CMSSWVERSION="CMSSW_9_4_2"

    execute "scramv1 project CMSSW $CMSSWVERSION" || return 1
    cd $CMSSWVERSION/src || return 1

    eval `scramv1 runtime -sh` || return 1
    
    execute "git cms-init" || return 1
    
    execute "git cms-merge-topic cms-nanoAOD:master" || return 1
    execute "git checkout -b nanoAOD cms-nanoAOD/master" || return 1
    execute "git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools" || return 1
    execute "git clone git@github.com:matt-komm/DeepNTuples.git" || return 1
    execute "git clone git@github.com:matt-komm/XTag.git" || return 1
}

run_setup
