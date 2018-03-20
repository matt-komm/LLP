function setup_script()
{
    if [[ `uname -r` != *".el7."* ]]; then
        echo "EL 7 required - try different node!"
        return 1
    fi
    echo "Preparing up GPU environment for training"

    SCRIPT_DIR=`dirname ${BASH_SOURCE[0]}`

    source $SCRIPT_DIR/Env/env.sh
    source activate tf_gpu
    
    export PATH=/usr/local/cuda-8.0/bin:$PATH
    export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH
    source /vols/build/cms/mkomm/cuDNNv6_cuda8/setupCuDNN.sh

    #source $SCRIPT_DIR/DeepJet/environment/env.sh

    export TF_CPP_MIN_LOG_LEVEL=2
    export OMP_NUM_THREADS=18

    ulimit -s unlimited
}

setup_script
