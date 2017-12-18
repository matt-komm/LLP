import tensorflow as tf
import keras
from keras import backend as K
import os
import time

from keras.layers import Dense, Dropout, Flatten,Convolution2D, Convolution1D,LSTM,Concatenate
from keras.layers.pooling import MaxPooling2D
from keras.layers.normalization import BatchNormalization

def block_deepFlavourConvolutions(charged,neutrals,vertices,dropoutRate,active=True,batchnorm=False,batchmomentum=0.6):
    '''
    deep Flavour convolution part. 
    '''
    cpf=charged
    if active:
        cpf  = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv0')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum ,name='cpf_batchnorm0')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout0')(cpf)                                                   
        cpf  = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv1')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum,name='cpf_batchnorm1')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout1')(cpf)                                                   
        cpf  = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv2')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum,name='cpf_batchnorm2')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout2')(cpf)                                                   
        cpf  = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu' , name='cpf_conv3')(cpf)
    else:
        cpf = Convolution1D(1,1, kernel_initializer='zeros',trainable=False)(cpf)
        
    npf=neutrals
    if active:
        npf = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='npf_conv0')(npf)
        if batchnorm:
            npf = BatchNormalization(momentum=batchmomentum,name='npf_batchnorm0')(npf)
        npf = Dropout(dropoutRate,name='npf_dropout0')(npf) 
        npf = Convolution1D(16, 1, kernel_initializer='lecun_uniform',  activation='relu', name='npf_conv1')(npf)
        if batchnorm:
            npf = BatchNormalization(momentum=batchmomentum,name='npf_batchnorm1')(npf)
        npf = Dropout(dropoutRate,name='npf_dropout1')(npf)
        npf = Convolution1D(4, 1, kernel_initializer='lecun_uniform',  activation='relu' , name='npf_conv2')(npf)
    else:
        npf = Convolution1D(1,1, kernel_initializer='zeros',trainable=False)(npf)

    vtx = vertices
    if active:
        vtx = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv0')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm0')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout0')(vtx) 
        vtx = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv1')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm1')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout1')(vtx)
        vtx = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv2')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm2')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout2')(vtx)
        vtx = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv3')(vtx)
    else:
        vtx = Convolution1D(1,1, kernel_initializer='zeros',trainable=False)(vtx)

    return cpf,npf,vtx

def block_deepFlavourDense(x,dropoutRate,active=True,batchnorm=False,batchmomentum=0.6):
    if active:
        x=  Dense(200, activation='relu',kernel_initializer='lecun_uniform', name='df_dense0')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm0')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout0')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense1')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm1')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout1')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense2')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm2')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout2')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense3')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm3')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout3')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense4')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm4')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout4')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense5')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm5')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout5')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense6')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm6')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout6')(x)
        x=  Dense(100, activation='relu',kernel_initializer='lecun_uniform', name='df_dense7')(x)
        if batchnorm:
            x = BatchNormalization(momentum=batchmomentum,name='df_dense_batchnorm7')(x)
        x = Dropout(dropoutRate,name='df_dense_dropout7')(x)
    else:
        x= Dense(1,kernel_initializer='zeros',trainable=False,name='df_dense_off')(x)
    
    return x

def model_deepFlavourReference(Inputs,nclasses,nregclasses,dropoutRate=0.1,momentum=0.6):
    #deep flavor w/o pt regression
    
    globalvars = BatchNormalization(momentum=momentum,name='globals_input_batchnorm') (Inputs[0])
    cpf    =     BatchNormalization(momentum=momentum,name='cpf_input_batchnorm')     (Inputs[1])
    npf    =     BatchNormalization(momentum=momentum,name='npf_input_batchnorm')     (Inputs[2])
    vtx    =     BatchNormalization(momentum=momentum,name='vtx_input_batchnorm')     (Inputs[3])
    #ptreginput = BatchNormalization(momentum=momentum,name='reg_input_batchnorm')     (Inputs[4])

   
    batchnorm=True
    batchmomentum = momentum
    with tf.device('/gpu:0'):
        cpf  = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv0')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum ,name='cpf_batchnorm0')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout0')(cpf)                                                   
        cpf  = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv1')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum,name='cpf_batchnorm1')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout1')(cpf)                                                   
        cpf  = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='cpf_conv2')(cpf)
        if batchnorm:
            cpf = BatchNormalization(momentum=batchmomentum,name='cpf_batchnorm2')(cpf)
        cpf = Dropout(dropoutRate,name='cpf_dropout2')(cpf)                                                   
        cpf  = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu' , name='cpf_conv3')(cpf)

        
        cpf  = LSTM(150,go_backwards=True,implementation=2, name='cpf_lstm')(cpf)
        cpf=BatchNormalization(momentum=momentum,name='cpflstm_batchnorm')(cpf)
        cpf = Dropout(dropoutRate)(cpf)
    
    
    with tf.device('/gpu:1'):
        npf = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='npf_conv0')(npf)
        if batchnorm:
            npf = BatchNormalization(momentum=batchmomentum,name='npf_batchnorm0')(npf)
        npf = Dropout(dropoutRate,name='npf_dropout0')(npf) 
        npf = Convolution1D(16, 1, kernel_initializer='lecun_uniform',  activation='relu', name='npf_conv1')(npf)
        if batchnorm:
            npf = BatchNormalization(momentum=batchmomentum,name='npf_batchnorm1')(npf)
        npf = Dropout(dropoutRate,name='npf_dropout1')(npf)
        npf = Convolution1D(4, 1, kernel_initializer='lecun_uniform',  activation='relu' , name='npf_conv2')(npf)

        npf = LSTM(50,go_backwards=True,implementation=2, name='npf_lstm')(npf)
        npf=BatchNormalization(momentum=momentum,name='npflstm_batchnorm')(npf)
        npf = Dropout(dropoutRate)(npf)
    
    
    
    with tf.device('/gpu:2'):
        vtx = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv0')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm0')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout0')(vtx) 
        vtx = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv1')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm1')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout1')(vtx)
        vtx = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv2')(vtx)
        if batchnorm:
            vtx = BatchNormalization(momentum=batchmomentum,name='vtx_batchnorm2')(vtx)
        vtx = Dropout(dropoutRate,name='vtx_dropout2')(vtx)
        vtx = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='vtx_conv3')(vtx)

        vtx = LSTM(50,go_backwards=True,implementation=2, name='vtx_lstm')(vtx)
        vtx=BatchNormalization(momentum=momentum,name='vtxlstm_batchnorm')(vtx)
        vtx = Dropout(dropoutRate)(vtx)



    with tf.device('/cpu:0'):
        x = Concatenate()( [globalvars,cpf,npf,vtx ])
        
    with tf.device('/gpu:2'):
        x = block_deepFlavourDense(x,dropoutRate,active=True,batchnorm=True,batchmomentum=momentum)

        flavour_pred=Dense(nclasses, activation='softmax',kernel_initializer='lecun_uniform',name='ID_pred')(x)

    #reg = Concatenate()( [flavour_pred, ptreginput ] ) 

    #reg_pred=Dense(nregclasses, activation='linear',kernel_initializer='ones',name='regression_pred',trainable=True)(reg)

    #predictions = [flavour_pred,reg_pred]
    #model = Model(inputs=Inputs, outputs=predictions)

    return flavour_pred

fileList = []

#filePath = "/media/matthias/HDD/matthias/Analysis/LLP/training/samples/rootFiles.txt"
filePath = "/vols/cms/mkomm/LLP/samples/rootFiles.txt"

f = open(filePath)
for l in f:
    absPath = os.path.join(filePath.rsplit('/',1)[0],l.replace("\n","").replace("\r","")+".tfrecord")
    fileList.append(absPath)
f.close()
print len(fileList)


featureList = {
    #need to explicity specify length - is auto range not supported in 1.0.1
    'truth': tf.FixedLenFeature([24], tf.float32),
    'global': tf.FixedLenFeature([15], tf.float32),
    'Cpfcan': tf.FixedLenFeature([400], tf.float32),
    'Npfcan': tf.FixedLenFeature([150], tf.float32),
    'sv': tf.FixedLenFeature([48], tf.float32),
}


def readFileSingleEntry(filenameQueue):
    reader = tf.TFRecordReader(options=tf.python_io.TFRecordOptions(tf.python_io.TFRecordCompressionType.GZIP))
    key, rawData = reader.read(filenameQueue) 
    #key is just a dataset identifier set by the reader
    #rawData is of type string
    parsedData = tf.parse_single_example(rawData, features=featureList)
    #decodedData = tf.decode_raw(parsedExample["Npfcan"], tf.float32)
    #TODO: what about decoding multiple records simulaneously?
    #print parsedData['Cpfcan'],parsedData['Cpfcan'].shape.dims[0]/25
    parsedData['Cpfcan']=tf.reshape(parsedData['Cpfcan'],[25,16])
    parsedData['Npfcan']=tf.reshape(parsedData['Npfcan'],[25,6])
    parsedData['sv']=tf.reshape(parsedData['sv'],[4,12])
    return parsedData
    
def readFileMultiEntry(filenameQueue, nBatches=200):
    reader = tf.TFRecordReader(options=tf.python_io.TFRecordOptions(tf.python_io.TFRecordCompressionType.GZIP))
    key, rawData = reader.read(filenameQueue) 
    #key is just a dataset identifier set by the reader
    #rawData is of type string
    
    #nBatches = 200
    rawDataBatch = tf.train.batch([rawData], nBatches, capacity=nBatches)
    parsedDataBatch = tf.parse_example(rawDataBatch, features=featureList)
    
    #decodedData = tf.decode_raw(parsedExample["Npfcan"], tf.float32)
    #TODO: what about decoding multiple records simulaneously?
    #print parsedData['Cpfcan'],parsedData['Cpfcan'].shape.dims[0]/25
    parsedDataBatch['Cpfcan']=tf.reshape(parsedDataBatch['Cpfcan'],[nBatches,25,16])
    parsedDataBatch['Npfcan']=tf.reshape(parsedDataBatch['Npfcan'],[nBatches,25,6])
    parsedDataBatch['sv']=tf.reshape(parsedDataBatch['sv'],[nBatches,4,12])
    return parsedDataBatch

 
def readFileMultiEntryAhead(filenameQueue, nBatches=200):
    reader = tf.TFRecordReader(options=tf.python_io.TFRecordOptions(tf.python_io.TFRecordCompressionType.GZIP))
    key, rawDataBatch = reader.read_up_to(filenameQueue,nBatches) 
    #key is just a dataset identifier set by the reader
    #rawData is of type string
    
    #nBatches = 200
    #rawDataBatch = tf.train.batch([rawData], nBatches, capacity=nBatches)
    parsedDataBatch = tf.parse_example(rawDataBatch, features=featureList)
    
    #decodedData = tf.decode_raw(parsedExample["Npfcan"], tf.float32)
    #TODO: what about decoding multiple records simulaneously?
    #print parsedData['Cpfcan'],parsedData['Cpfcan'].shape.dims[0]/25
    #NOTE: read_up_to may return less than nBatches
    parsedDataBatch['Cpfcan']=tf.reshape(parsedDataBatch['Cpfcan'],[-1,25,16])
    parsedDataBatch['Npfcan']=tf.reshape(parsedDataBatch['Npfcan'],[-1,25,6])
    parsedDataBatch['sv']=tf.reshape(parsedDataBatch['sv'],[-1,4,12])
    return parsedDataBatch

batchSize = 20000

#create queue and populate it with some filesnames from the list
fileListQueue = tf.train.string_input_producer(fileList, num_epochs=2, shuffle=True)

#read multiple files simultaneously
dataList = [readFileMultiEntryAhead(fileListQueue,100) for _ in range(6)] 
#dequeueFromList = fileListQueue.deqtensorflow/core/platform/cpu_feature_guard.ccueue()
print dataList

minAfterDequeue = batchSize*3
capacity = minAfterDequeue + 6 * batchSize

#trainingBatch = tf.train.batch_join(
trainingBatch = tf.train.shuffle_batch_join(
    dataList, 
    batch_size=batchSize, 
    capacity=capacity,
    min_after_dequeue=minAfterDequeue,
    enqueue_many=True #requires to read examples in batches!
)
#print trainingBatch


globalvars = keras.layers.Input(tensor=trainingBatch['global'])
cpf = keras.layers.Input(tensor=trainingBatch['Cpfcan'])
npf = keras.layers.Input(tensor=trainingBatch['Npfcan'])
vtx = keras.layers.Input(tensor=trainingBatch['sv'])
truth = trainingBatch["truth"]
#dequeueBatch = trainingBatch['Npfcan'].dequeue()

nclasses = truth.shape.as_list()[1]
print nclasses
inputs = [globalvars,cpf,npf,vtx]
prediction = model_deepFlavourReference(inputs,nclasses,1,dropoutRate=0.1,momentum=0.6)
loss = tf.reduce_mean(keras.losses.categorical_crossentropy(truth, prediction))
#model = keras.Model(inputs=inputs, outputs=prediction)
#model.add_loss(loss)
#model.compile(optimizer='rmsprop', loss=None)
#model.summary()
train_op = tf.train.GradientDescentOptimizer(0.01).minimize(loss)



#init_op = tf.global_variables_initializer() #bug https://github.com/tensorflow/tensorflow/issues/1045
init_op = tf.group(tf.global_variables_initializer(), tf.local_variables_initializer())

sess = K.get_session()

sess.run(init_op)

coord = tf.train.Coordinator()
threads = tf.train.start_queue_runners(sess=sess, coord=coord)

try:
    step = 0
    while not coord.should_stop():
        start_time = time.time()

        _, loss_value = sess.run([train_op, loss], feed_dict={K.learning_phase(): 0})

        
        #data = sess.run(trainingBatch)
        #print data
        duration = time.time() - start_time
        if step % 1 == 0:
            print 'Step %d: loss = %.2f (%.3f sec)' % (step, loss_value,duration)
        step += 1
except tf.errors.OutOfRangeError:
    print('Done training for %d steps.' % (step))
#sess.run(trainingBatch)
#print globalvars
#print truth

#train_model.fit(epochs=1000, steps_per_epoch=1000)
#sess.run(trainingBatch)



coord.request_stop()
coord.join(threads)
K.clear_session()
#print sess.run(dataList[0])
    
    
    
    
    
    
