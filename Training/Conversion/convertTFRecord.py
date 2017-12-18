import tensorflow as tf
import numpy as np
import ROOT
import sys
import os
import time
import threading
import logging

logging.basicConfig(
    level=logging.DEBUG,
    format='(%(threadName)-10s) %(message)s',
)

featureDict = {}

def addBranches(featureName,nameList, multplicity=0):
    featureDict[featureName]={"names":nameList,"multiplicity":multplicity}
    print "add feature ",featureName," with entries ",len(nameList)*(multplicity if multplicity>=1 else 1)
    
    
def convert(rootFileName):
    '''
    if os.path.exists(rootFileName+".tfrecord.uncompressed"):
        logging.info("exists ... "+rootFileName+".tfrecord.uncompressed -> skip")
        return
    '''
    logging.info("converting ... "+rootFileName)
    writer = tf.python_io.TFRecordWriter(rootFileName+".tfrecord.uncompressed")#,options=tf.python_io.TFRecordOptions(tf.python_io.TFRecordCompressionType.GZIP))
    rootFile = ROOT.TFile(rootFileName)
    tree = rootFile.Get("deepntuplizer/tree")

    for entry in range(tree.GetEntries()):
        # print how many images are saved every 1000 images
        tree.GetEntry(entry)
            
        record = {}
        for featureName in sorted(featureDict.keys()):
            featureConfig = featureDict[featureName]
            nFeatures = len(featureConfig["names"])
            array = None
            if featureConfig["multiplicity"]==0:
                array = np.zeros((nFeatures),dtype=np.float32)
                for iname,name in enumerate(featureConfig["names"]):
                    array[iname]=getattr(tree,name)
            else:
                array = np.zeros((nFeatures*featureConfig["multiplicity"]))
                for iname,name in enumerate(featureConfig["names"]):
                    rootArray=getattr(tree,name)
                    for imultiplicity in range(min(len(rootArray),featureConfig["multiplicity"])):
                        array[iname*featureConfig["multiplicity"]+imultiplicity]=rootArray[imultiplicity]
            
            #print featureName,array
            record[featureName]=_float_feature(array)
        # Create an example protocol buffer
        example = tf.train.Example(features=tf.train.Features(feature=record))

        # Serialize to string and write on the file
        writer.write(example.SerializeToString())

    writer.close()
    sys.stdout.flush()
    logging.info("done ... "+rootFileName)
    
addBranches("truth",[
    'isB',
    'isBB',
    'isGBB',
    'isLeptonicB',
    'isLeptonicB_C',
    'isC',
    'isCC',
    'isGCC',
    'isUD',
    'isS',
    'isG',
    'isUndefined',
    'isFromLLgno_isB',
    'isFromLLgno_isBB',
    'isFromLLgno_isGBB',
    'isFromLLgno_isLeptonicB',
    'isFromLLgno_isLeptonicB_C',
    'isFromLLgno_isC',
    'isFromLLgno_isCC',
    'isFromLLgno_isGCC',
    'isFromLLgno_isUD',
    'isFromLLgno_isS',
    'isFromLLgno_isG',
    'isFromLLgno_isUndefined'
])

addBranches("global",[
    'jet_pt',
    'jet_eta',
    'nCpfcand',
    'nNpfcand',
    'nsv',
    'npv',
    'TagVarCSV_trackSumJetEtRatio', 
    'TagVarCSV_trackSumJetDeltaR', 
    'TagVarCSV_vertexCategory', 
    'TagVarCSV_trackSip2dValAboveCharm', 
    'TagVarCSV_trackSip2dSigAboveCharm', 
    'TagVarCSV_trackSip3dValAboveCharm', 
    'TagVarCSV_trackSip3dSigAboveCharm', 
    'TagVarCSV_jetNSelectedTracks', 
    'TagVarCSV_jetNTracksEtaRel'
])

addBranches("Cpfcan",[
    'Cpfcan_BtagPf_trackEtaRel',
    'Cpfcan_BtagPf_trackPtRel',
    'Cpfcan_BtagPf_trackPPar',
    'Cpfcan_BtagPf_trackDeltaR',
    'Cpfcan_BtagPf_trackPParRatio',
    'Cpfcan_BtagPf_trackSip2dVal',
    'Cpfcan_BtagPf_trackSip2dSig',
    'Cpfcan_BtagPf_trackSip3dVal',
    'Cpfcan_BtagPf_trackSip3dSig',
    'Cpfcan_BtagPf_trackJetDistVal',
    #'Cpfcan_BtagPf_trackJetDistSig',

    'Cpfcan_ptrel', 
    'Cpfcan_drminsv',
    #'Cpfcan_fromPV',
    'Cpfcan_VTX_ass',
    'Cpfcan_puppiw',
    'Cpfcan_chi2',
    'Cpfcan_quality'
],25)
        
 
addBranches("Npfcan",[
    'Npfcan_ptrel',
    'Npfcan_deltaR',
    'Npfcan_isGamma',
    'Npfcan_HadFrac',
    'Npfcan_drminsv',
    'Npfcan_puppiw'
],25)
        
        
addBranches("sv",[
    'sv_pt',
    'sv_deltaR',
    'sv_mass',
    'sv_ntracks',
    'sv_chi2',
    'sv_normchi2',
    'sv_dxy',
    'sv_dxysig',
    'sv_d3d',
    'sv_d3dsig',
    'sv_costhetasvpv',
    'sv_enratio',
],4)

def _int64_feature(array):
    return tf.train.Feature(int64_list=tf.train.Int64List(value=array))
    
def _float_feature(array):
    return tf.train.Feature(float_list=tf.train.FloatList(value=array))
    
def _bytes_feature(array):
    return tf.train.Feature(bytes_list=tf.train.BytesList(value=array))
    
rootFiles = []

filePath = "/vols/cms/mkomm/LLP/samples/rootFiles.uncompressed.txt"
#filePath = "/vols/build/cms/mkomm/LLP/Training/Conversion/rootFiles.txt"

f = open(filePath)
for l in f:
    absPath = os.path.join(filePath.rsplit('/',1)[0],l.replace("\n","").replace("\r",""))
    rootFiles.append(absPath)
f.close()

#rootFiles = rootFiles[:10]

threads = []
while (len(rootFiles)!=0):
    rootFileName = rootFiles.pop()
    while (len(threads)>5):
        time.sleep(1)
        for thread in threads[:]:
            if not thread.isAlive():
                threads.remove(thread)
                thread.join()
    t = threading.Thread(name="conv"+str(len(rootFiles)), target=convert, args=(rootFileName,))
    threads.append(t)
    t.start()
for thread in threads:
    thread.join()
    
