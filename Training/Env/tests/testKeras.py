#!/usr/bin/env python
import tensorflow as tf
import keras
import os
print "Keras package" 
print "  Installation: ",os.path.dirname(keras.__file__)
print "  Version: ",keras.__version__
print "Tensorflow package"
print "  Installation: ",os.path.dirname(tf.__file__)
print "  Version: ",tf.__version__

print "Computing devices:"
from tensorflow.python.client import device_lib
for dev in device_lib.list_local_devices():
    print "  Devices:",dev.name
    print "  Type:",dev.device_type
    print "  Memory:",dev.memory_limit
    print "  Locality:",dev.locality
    print "  Description:",dev.physical_device_desc
    
    print "  Testing device: ",dev.name,"..."
    with tf.device(dev.name):
        
        hello = tf.constant('Hello, TensorFlow!')
        sess = tf.Session(config=tf.ConfigProto(log_device_placement=True))
        sess.run(hello)
        sess.close()
    print "  ... done testing device: ",dev.name
    print

