import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

from CommonTools.RecoUtils.pf_pu_assomap_cfi import *
#from CommonTools.RecoUtils import PF_PU_AssoMap

process = cms.Process("Analysis")

#process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Services_cff")
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

#process.GlobalTag.globaltag = 'GR_R_36X_V12A::All'
#process.GlobalTag.globaltag = 'GR_R_39X_V6::All'
#process.GlobalTag.globaltag = 'FT_R_42_V13A::All'
#process.GlobalTag.globaltag = 'GR_P_V23::All'
#process.GlobalTag.globaltag = 'FT_R_42_V20A::All'
#process.GlobalTag.globaltag = 'GR_P_V23::All'
#process.GlobalTag.globaltag = 'GR_P_V56::All'
#process.GlobalTag.globaltag = '101X_dataRun2_Prompt_v11'
process.GlobalTag.globaltag = '101X_upgrade2018_realistic_v7'

###process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

#filelist = FileUtils.loadListFromFile("inputlist.list")
#filelist = FileUtils.loadListFromFile("onefile.list")

process.source = cms.Source('PoolSource',
#fileNames = cms.untracked.vstring(*filelist),
fileNames = cms.untracked.vstring(#'/store/data/Run2018C/ZeroBias/RAW-RECO/LogError-PromptReco-v1/000/319/347/00000/86EFC8CD-DE84-E811-8983-FA163EC985ED.root'
#'/store/data/Run2018C/ZeroBias/RAW-RECO/LogError-PromptReco-v1/000/319/347/00000/86EFC8CD-DE84-E811-8983-FA163EC985ED.root'
#'/store/mc/RunIIAutumn18DRPremix/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/GEN-SIM-RECO/102X_upgrade2018_realistic_v15_ext1-v2/60000/7E8A8DF4-FBBE-EF4F-97DB-0B1C8EE1A059.root'
'/store/mc/RunIIAutumn18DRPremix/SingleNeutrino/GEN-SIM-RECO/forRECO_102X_upgrade2018_realistic_v15_ext1-v1/100000/18847E99-339C-634B-8F2B-C5CB4E0869CE.root'
),
#skipEvents = cms.untracked.uint32(100000)
inputCommands=cms.untracked.vstring(
                  'keep *',
                  'drop Totem*_*_*_*',
          )
)

#process.source = cms.Source("PoolSource",
#    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        #'file:/tigress-hsm/zuranski/work/cms/data/FullSim/MinBias_Dstar_7TeV/K3pi/reco2data-1.root'
#        #'file:/tigress-hsm/zuranski/work/cms/releases/CMSSW_3_5_6/src/Analysis/DSD0analyzer/MinBias.root'
#        #'/store/mc/Spring10/MinBias/GEN-SIM-RECO/START3X_V25_356ReReco-v2/0123/C86FED5C-AC3B-DF11-A1BC-002618943898.root',
#        #'/store/mc/Spring10/MinBias/GEN-SIM-RECO/START3X_V25_356ReReco-v2/0123/C4A5C01A-AD3B-DF11-A37A-001A92971B7E.root'
#        #'file:/tigress-hsm/phedex/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Dec19thSkim_336p3_v1/0006/7CA100C2-D7EE-DE11-BCC3-001D0967D643.root'
#        #'file:/pnfs/cms/WAX/11/store/data/Run2010A/Mu/RECO/Nov4ReReco_v1/0008/32AE1FA0-CFEA-DF11-8C75-0017A4770404.root'
#        #'file:myfile.root'
#        #'file:/uscms/home/mrmooney/3DayLifetime/file.root'
#        '/store/data/Run2015B/MinimumBias/RECO/PromptReco-v1/000/251/555/00000/84F65189-D029-E511-BD96-02163E011DAE.root',
#        #'/store/data/Run2015B/MinimumBias/RECO/PromptReco-v1/000/251/557/00000/FE4F2BB9-EE29-E511-B871-02163E011D37.root',
#        #'/store/data/Run2015B/MinimumBias/RECO/PromptReco-v1/000/250/974/00000/4CADD93C-B125-E511-985F-02163E01463E.root',
#        #'/store/data/Run2015A/MinimumBias/RECO/PromptReco-v1/000/246/941/00000/E4BC8984-AE0B-E511-B5EF-02163E011D25.root',
#        #'/store/data/Run2015B/HLTPhysics/RECO/PromptReco-v1/000/250/985/00000/84B623B2-A625-E511-A4A5-02163E0120B0.root',
#        #'/store/data/Run2015B/ZeroBias1/RECO/PromptReco-v1/000/250/985/00000/70530BE4-A425-E511-905B-02163E0144D6.root',
#    )
#)

process.options = cms.untracked.PSet(
    #Rethrow = cms.untracked.vstring('ProductNotFound'),
    IgnoreCompletely = cms.untracked.vstring('MismatchedInputFiles','ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

from SimTracker.TrackAssociation.LhcParametersDefinerForTP_cfi import *
from SimTracker.TrackAssociation.CosmicParametersDefinerForTP_cfi import *
from Validation.RecoTrack.MTVHistoProducerAlgoForTrackerBlock_cfi import *

#import FWCore.PythonUtilities.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_314472-319851_13TeV_PromptReco_Collisions18_JSON.txt').getVLuminosityBlockRange()

#process.Tracks2Vertex = AssociationMaps.clone()

process.Tracks2Vertex = cms.EDProducer('PF_PU_AssoMap',                 
          #Choose which map should be created
          #"VertexToTracks", "TracksToVertex" or "Both"
          AssociationType = cms.InputTag('TracksToVertex'),

          #Set the number of associations per track/vertex                          
          MaxNumberOfAssociations = cms.int32(1),

          #Set the Input Collections
          TrackCollection = cms.InputTag('generalTracks'),
          VertexCollection = cms.InputTag('offlinePrimaryVertices'),

          #Set the BeamSpot
          BeamSpot = cms.InputTag('offlineBeamSpot'),

          #Check for tracks from secondary vertices
          doReassociation = cms.bool(True),
          GetCleanedCollections = cms.bool(False),

          #Configuration for the reassociation of gamma conversion particles
          ConversionsCollection = cms.InputTag('allConversions'),

          #Configuration for the reassociation of particles from V0 decays
          V0KshortCollection = cms.InputTag('generalV0Candidates','Kshort'),
          V0LambdaCollection = cms.InputTag('generalV0Candidates','Lambda'),

          #Configuration for the reassociation of particles from nuclear interactions
          NIVertexCollection = cms.InputTag('particleFlowDisplacedVertex'),

          #Configuration for the final association
          # 0 == always first vertex (default)
          # 1 == closest vertex in z/longitudinal distance
          # 2 == closest vertex in 3D
          FinalAssociation = cms.untracked.int32(1),

          #What to do if the dipl vertex coll can't be found
          ignoreMissingCollection = cms.bool(True),

          #Input for the search of the closest vertex
          nTrackWeight = cms.double(0.001),

)

#process.Tracks2Vertex = AssociationMaps.clone(		
#	 
#	#Choose which map should be created
#	#"VertexToTracks", "TracksToVertex" or "Both"
#	AssociationType = cms.InputTag('TracksToVertex'),
#	 	 
#)

process.trig = cms.EDFilter("HLTHighLevel",
                                     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
                                     HLTPaths = cms.vstring("HLT_PFJet*"
#                                     HLTPaths = cms.vstring("HLT_ZeroBias_v*"
#                                     HLTPaths = cms.vstring("HLT_*"
                                                            ),
                                     eventSetupPathsKey = cms.string(''),
                                     andOr = cms.bool(True),
                                     throw = cms.bool(False)
                                     )

#process.analyzer = cms.EDAnalyzer('TrkEffAnalyzer',
#    pionPixel=cms.bool(False),
#    kaonPixel=cms.bool(False),
#    runMode=cms.int32(1)
#)

process.analyzer = cms.EDAnalyzer('LambdaAnalyzer',
    doGen=cms.bool(True),
    doK3pi=cms.bool(True),
    doKpi=cms.bool(True),
    
    tracks_noPXB1 = cms.untracked.InputTag("ctfProducerCustomised"),
    tracks = cms.untracked.InputTag("generalTracks"),
    vertices = cms.untracked.InputTag("offlinePrimaryVertices"),
    genParticles = cms.untracked.InputTag("genParticles"),
    T2V = cms.untracked.InputTag("Tracks2Vertex"),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TrkAnalysis_generalTracks.root')
)

#process.output = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring('drop *',
#                                           'keep *_Tracks2Vertex_*_*'),
#    fileName = cms.untracked.string('t2vColl.root'),
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string(''),
#        filterName = cms.untracked.string('')
#    )
#)
process.content = cms.EDAnalyzer("EventContentAnalyzer")

###process.load("PhysicsTools.HepMCCandAlgos.HiGenParticles_cfi")
###process.genParticles = process.hiGenParticles.clone(useCrossingFrame = True)

# parameters for TrackRefitter
import RecoTracker.TrackProducer.TrackRefitters_cff
process.TrackRefitter1 = RecoTracker.TrackProducer.TrackRefitter_cfi.TrackRefitter.clone()
process.TrackRefitter1.src = 'generalTracks'

process.load("RecoVertex.BeamSpotProducer.BeamSpot_cff")
process.load("RecoTracker.FinalTrackSelectors.TrackerTrackHitFilter_cff")
process.TrackerTrackHitFilter.src = 'TrackRefitter1'
#process.TrackerTrackHitFilter.src = 'generalTracks'
process.TrackerTrackHitFilter.commands = cms.vstring("drop PXB","keep PXB 2","keep PXB 3","keep PXB 4","keep PXE","keep TIB","keep TID","keep TOB","keep TEC")

# Might want to customize other options of the tracker track hit filter
# Refit tracks after hit filter
# You might want to customize the options, or use a different refitter
import RecoTracker.TrackProducer.CTFFinalFitWithMaterial_cff
process.ctfProducerCustomised = RecoTracker.TrackProducer.CTFFinalFitWithMaterial_cff.ctfWithMaterialTracks.clone()
process.ctfProducerCustomised.src = 'TrackerTrackHitFilter'

process.all = cms.Path(process.MeasurementTrackerEvent*process.TrackRefitter1*process.TrackerTrackHitFilter*process.ctfProducerCustomised*process.analyzer)

#process.all = cms.Path(process.bscMinBias*process.analyzer)
#process.all = cms.Path(process.analyzer)
###process.all = cms.Path(process.Tracks2Vertex*process.analyzer)
####process.all = cms.Path(process.trig*process.Tracks2Vertex*process.analyzer)
#process.all = cms.Path(process.trig*process.analyzer)
#process.all = cms.Path(process.analyzer)
#process.all = cms.Path(process.trig*process.Tracks2Vertex)
#process.theoutput = cms.EndPath(process.output)

process.schedule = cms.Schedule(process.all)
#process.schedule = cms.Schedule(process.all, process.theoutput)


