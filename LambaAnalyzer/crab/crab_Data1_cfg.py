from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'LambdaAnalysis_ZeroBias_Dec17_Run2018B_LogError_PromptReco_v1_noPXB1Hits'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'trkeffanalyzer_Data_GeneralTracks_cfg.py'

config.Data.inputDataset = '/ZeroBias/Run2018B-LogError-PromptReco-v1/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/DCSOnly/json_DCSONLY_Run2015B.txt'
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-251252_13TeV_PromptReco_Collisions15_JSON.txt'
#config.Data.lumiMask = 'Cert_246908-251252_13TeV_PromptReco_Collisions15_JSON.txt'
#config.Data.lumiMask = 'Cert_251721_13TeV_lowPURun_JSON.txt'
#config.Data.lumiMask = 'Cert_314472-319851_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.lumiMask = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
#config.Data.runRange = '251000-252000'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.publishDataName = 'DStar_ZeroBias_Run251721-lowPU-July27'

config.Site.storageSite = 'T2_CH_CERN' 
