function setup_script()
{
    if [[ `uname -r` != *".el7."* ]]; then
        echo "EL 7 required - try different node!"
        return 1
    fi
    echo "Preparing up CPU environment for training"

    SCRIPT_DIR=`dirname ${BASH_SOURCE[0]}`

    source $SCRIPT_DIR/Env/env.sh
    source activate tf_cpu
    
    source $SCRIPT_DIR/DeepJet/environment/env.sh

    export TF_CPP_MIN_LOG_LEVEL=2
    export OMP_NUM_THREADS=12 #reduce further if out-of-memory

    ulimit -s unlimited
}

setup_script
