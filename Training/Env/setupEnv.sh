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
    if [[  -z  $1  ]] ; then
        echo 'Usage:'
        echo '  setupCentralEnv.sh <install_dir>'
        return 1
    fi

    if [[ `uname -r` != *".el7."* ]]; then
        echo "EL 7 required - try different node!, e.g. lx03 (imperial) or lxplus005 (CERN)"
        return 1
    fi

    INSTALL_DIR=`realpath $1`

    if [ -d "$1" ]; then
        echo "Error - directory "$INSTALL_DIR" exists!"
        return 1
    fi
    echo "Setting up central environment for training under "$INSTALL_DIR

    execute mkdir $INSTALL_DIR || return 1

    if [ ! -d "$1" ]; then
        echo "Error - failed to create directory "$INSTALL_DIR"!"
        return 1
    fi

    execute wget -P $INSTALL_DIR https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh || return 1
    execute bash $INSTALL_DIR/Miniconda3-latest-Linux-x86_64.sh -b -s -p $INSTALL_DIR/miniconda || return 1

    CONDA_BIN=$INSTALL_DIR/miniconda/bin
    export PATH=$CONDA_BIN:$PATH


    echo "Create environment for CPU"
    #conda create --file conda_tensorflow_cpu_env.yml

    conda create -n tf_cpu python=2.7 --yes || return 1
    source activate tf_cpu || return 1
    
    echo "Installing packages"
    conda install -c nlesc root-numpy=4.4.0 --yes || return 1
    pip install --ignore-installed --upgrade -r packages.pip || return 1
}

run_setup $1

#export PATH=$CONDA_BIN:$PATH

#git clone https://github.com/matt-komm/DeepJet.git

#cd DeepJet/environment

#echo "Setting up CPU usage"
#./setupEnv.sh deepjetLinux3.conda

#echo "Setting up GPU usage"
#./setupEnv.sh deepjetLinux3.conda gpu
