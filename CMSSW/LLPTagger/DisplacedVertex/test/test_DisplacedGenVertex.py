import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("DISPLACED")

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        "root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/SMS-T1qqqq_ctau-1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_GridpackScan_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/10000/023CA233-4289-E711-9B01-002590FD5A48.root"
    )
)

process.options   = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    allowUnscheduled = cms.untracked.bool(True)
)

#merge GenParticles for easy matching of GenJets to vertices
process.genParticlesMerged = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles")
)

#select only stable particles (status=1) for reclustering GenJets for the matching; exclude neutrinos
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
process.genParticlesForGenJets = cms.EDFilter(
    "CandPtrSelector", 
    src = cms.InputTag("genParticlesMerged"),
    cut = cms.string("status==1 && abs(pdgId) != 12 && abs(pdgId) != 14 && abs(pdgId) != 16")
)

#recluster GenJets
process.genJetsReclustered = ak4GenJets.clone(
    src = 'genParticlesForGenJets'
)

#produce DisplacedGenVertices and match to GenJets
process.displacedGenVertices = cms.EDProducer(
    "DisplacedGenVertexProducer",
    srcGenParticles = cms.InputTag("genParticlesMerged"),
    srcGenJets = cms.InputTag("genJetsReclustered")
)

process.MINIAODSIMoutput = cms.OutputModule("PoolOutputModule",                     
    compressionAlgorithm = cms.untracked.string('LZMA'),    
    compressionLevel = cms.untracked.int32(4),              
    dataset = cms.untracked.PSet(   
        dataTier = cms.untracked.string(''),                
        filterName = cms.untracked.string('')               
    ),      
    dropMetaData = cms.untracked.string('ALL'),             
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),                   
    fastCloning = cms.untracked.bool(False),                
    fileName = cms.untracked.string('BTagging.root'),  
    outputCommands = cms.untracked.vstring(
       'drop *',
       'keep *_*_*_DISPLACED',
                                           ),
    overrideInputFileSplitLevels = cms.untracked.bool(True) 
)           
            
process.endpath = cms.EndPath(process.MINIAODSIMoutput)             
