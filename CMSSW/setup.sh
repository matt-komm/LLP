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

    CMSSWVERSION="CMSSW_8_0_25"

    execute "scramv1 project CMSSW $CMSSWVERSION" || return 1
    cd $CMSSWVERSION/src || return 1

    #follows instructions of https://github.com/CMSRA1/RA1OPS/wiki/1.-Flat-Tree-Production-(80X)#set-up-and-enter-an-environment-in-the-first-session
    eval `scramv1 runtime -sh` || return 1
    export CMSSW_GIT_REFERENCE=/vols/cms/RA1/cmg-cmssw-bare
    
    execute "git cms-init" || return 1
    
    execute "git remote add ra1-private git@github.com:CMSRA1/cmg-cmssw-private.git" || return 1
    execute "git fetch --no-tags ra1-private" || return 1
    
    echo ".gitignore" >> .git/info/sparse-checkout
    echo "PhysicsTools/Heppy" >> .git/info/sparse-checkout
    echo "PhysicsTools/HeppyCore" >> .git/info/sparse-checkout
    echo "EgammaAnalysis/ElectronTools" >> .git/info/sparse-checkout
    echo "RecoEgamma/ElectronIdentification" >> .git/info/sparse-checkout
    echo "RecoEgamma/PhotonIdentification" >> .git/info/sparse-checkout
    echo "RecoBTag/Configuration" >> .git/info/sparse-checkout
    echo "RecoBTag/DeepFlavour" >> .git/info/sparse-checkout
    echo "RecoBTag/LWTNN" >> .git/info/sparse-checkout
    echo "RecoBTag/SecondaryVertex" >> .git/info/sparse-checkout
    echo "PhysicsTools/PatAlgos" >> .git/info/sparse-checkout
    echo "DataFormats/BTauReco" >> .git/info/sparse-checkout

    git config core.sparsecheckout true
    
    execute "git checkout heppy_80X_ra1-0.7.x-Moriond17Prod" || return 1
    
    echo "CMGTools/" >> .git/info/exclude
    
    
    #make a sparse checkout instead (do not want other analyses filling up sandbox)
    #mkdir CMGTools
    cd CMGTools
    #execute "git init" || return 1
    #git config core.sparseCheckout true
    #echo ".gitignore" >> .git/info/sparse-checkout
    #echo ".gitmodules" >> .git/info/sparse-checkout
    #echo "RA1" >> .git/info/sparse-checkout
    #echo "Production" >> .git/info/sparse-checkout
    #echo "RootTools" >> .git/info/sparse-checkout
    #echo "TTHAnalysis/interface" >> .git/info/sparse-checkout
    #echo "TTHAnalysis/src" >> .git/info/sparse-checkout
    #echo "TTHAnalysis/python" >> .git/info/sparse-checkout
    
    
    execute "git clone -o ra1 git@github.com:CMSRA1/cmgtools-lite-private.git CMGTools" || return 1
    cd CMGTools
    
    execute "git remote add -f origin git@github.com:matt-komm/cmgtools-lite-private.git" || return 1

    #execute "git checkout 80X-ra1-0.7.x-Moriond17Prod" || return 1
    execute "git checkout 80X-ra1-0.7.x-Moriond17Prod-DNN" || return 1
    
    execute "git submodule init" || return 1
    execute "git submodule update" || return 1

    cd ${CMSSW_BASE}/src || return 1
    
    execute "git clone git@github.com:matt-komm/XTag.git" || return 1

    #add legacy Ntuple producer
    echo "DeepNTuples/" >> .git/info/exclude
    execute "git clone git@github.com:matt-komm/DeepNTuples.git" || return 1
    cd DeepNTuples || return 1
    execute "git submodule init" || return 1
    execute "git submodule update" || return 1
    #cd ${CMSSW_BASE}/src || return 1
    #execute "git cms-merge-topic -u mverzett:DeepFlavour-from-CMSSW_8_0_21" || return 1
    #cd ${CMSSW_BASE}/src || return 1
    
    #execute "git clone -b 80X https://gitlab.cern.ch/mrieger/CMSSW-DNN.git DNN" || return 1
    #execute "./DNN/setup_legacy.sh" || return 1
    
    execute "scram b || scram b -j4 || scram b -j4" || return 1
}

run_setup
