//class LambdaAnalyzer LambdaAnalyzer.cc Analysis/LambdaAnalyzer/src/LambdaAnalyzer.cc
// Original Author:  Andrzej Zuranski,Address unknown,NONE,
//         Created:  Fri Dec 11 13:59:16 EST 2009

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//#include "DataFormats/Common/interface/EDProduct.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include <TString.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <iostream>
#include "TMath.h"
#include "TTree.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "RecoVertex/KalmanVertexFit/interface/SingleTrackVertexConstraint.h"

//GEN MC Matching
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/OneToManyWithQuality.h"
#include "DataFormats/Common/interface/OneToManyWithQualityGeneric.h"

#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"

class LambdaAnalyzer : public edm::EDAnalyzer {
   public:
      explicit LambdaAnalyzer(const edm::ParameterSet&);
      ~LambdaAnalyzer();

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      void printGenInfo(const edm::Event& iEvent);
      void loop(const edm::Event& iEvent, const edm::EventSetup&, const reco::Vertex& RecVtx);
      void assignStableDaughters(const reco::Candidate* p, std::vector<int> & pids);
      void initialize();
      // ----------member data ---------------------------
      bool doGen, doK3pi, doKpi;
      double m_pi, m_K, m_p;
      std::vector<int> LambdaDPicands;
      std::vector<int> dScandsK3pi;
      std::vector<reco::TransientTrack*> goodTracks;
      std::vector<reco::TransientTrack*> slowPiTracks;
      std::vector<reco::TransientTrack> t_tks;
      std::vector<reco::TransientTrack> t_tks_noPXB1;
      TTree *tree1;
      
      const std::vector<TrackingParticle> *tPC;
      //std::vector<TrackingParticle> trkParticle;


      //ntuple variables
      int NKpiCand,NK3piCand,trigflag[160],NKpiMC,NK3piMC;
       
      //run, event, lumi section
      int run_n,event_n,lumi;
 
      //Kpi & K3pi Lambda D* vector vars
      std::vector<double> LambdaMass,DSMassKpi,LambdaVtxProb,LambdaVtxLSig,LambdaVtxLSig3D,LambdaPtKpi,DSPtKpi,LambdaVtxPosx,LambdaVtxPosy,LambdaVtxPosz,LambdaVtxerrx,LambdaVtxerry,LambdaVtxcxy,LambdaVtxcxz,LambdaVtxcyz;
      std::vector<double> LambdaVtxerrz,Lambdaeta,Lambdaphi,DSetaKpi,DSphiKpi,LambdaMassK3pi,LambdaMassK3pi1,DSMassK3pi,DSMassK3pi1,LambdaVtxProb3,LambdaVtx3LSig,LambdaVtx3LSig3D,LambdaPtK3pi,DSPtK3pi,LamdaVertexCAx,LamdaVertexCAy,LamdaVertexCAz;
      std::vector<double> cosAlphaK3pi,cosAlpha,cosAlpha3D,cosAlpha3DK3pi,flightLengthK3pi,flightLength,flightLength_noPXB1,flightLength_noPXB1_error;
      std::vector<double> LambdaVtxPosx3,LambdaVtxPosy3,LambdaVtxPosz3,LambdaVtxerrx3,LambdaVtxerry3,LambdaVtxerrz3,LambdaVtx3cxy,LambdaVtx3cxz,LambdaVtx3cyz,LambdaetaK3pi,LambdaphiK3pi;
      std::vector<double> DSetaK3pi,DSphiK3pi,LambdaMassK3proton,DSMassK3proton;

      std::vector<int> LambdaSharedHitLayer,LambdaSharedHitLadder,LambdaSharedHitModule;
 
      //Gen quantities
      std::vector<double> GenLambdaVtxPosx, GenLambdaVtxPosy, GenLambdaVtxPosz, GenLambdaSourceVtxPosx, GenLambdaSourceVtxPosy, GenLambdaSourceVtxPosz,GenLambdaPt, GenLambdaP, GenLambdaPhi, GenLambdaEta, GenLambdaMass, GenLambdaMt, GenLambdaE, GenLambdaEt, GenLambdaPx, GenLambdaPy, GenLambdaPz, GenFlightLength, GenDeltaR;
      std::vector<bool> GenVertexMatch; 
      
      //primarty vtx vars
      double PVx,PVy,PVz,PVerrx,PVerry,PVerrz,PVcxy,PVcxz,PVcyz;
      double BSx,BSy,BSz,BSerrx,BSerry,BSerrz;
      int nPV, PVOrder;     
 
      //tracks
      int ntracks;

      //Kpi tracks vars
      std::vector<double> KpiTrkKnhits,KpiTrkpinhits,KpiTrkSnhits;
      std::vector<double> KpiTrkKchi2,KpiTrkpichi2,KpiTrkSchi2;
      std::vector<double> TrkPi1pt,TrkProtonpt,TrkPi1eta,TrkProtoneta,TrkPi1mass,TrkProtonmass,TrkPi1phi,TrkProtonphi,TrkPi1chi2,TrkPi1ndof,TrkProtonndof,TrkProtonchi2,KpiTrkpipt,KpiTrkSpt,TrkPi1dxy,TrkPi1dz,TrkProtondxy,TrkProtondz,PionProtondz;
      std::vector<double> KpiTrkKdxy,KpiTrkpidxy,KpiTrkSdxy,KpiTrkSdxyErr;
      std::vector<double> KpiTrkKdz,KpiTrkpidz,KpiTrkSdz,KpiTrkSdzErr;
      std::vector<double> KpiTrkKeta,KpiTrkpieta,KpiTrkSeta;
      std::vector<double> KpiTrkKphi,KpiTrkpiphi,KpiTrkSphi;
      std::vector<double> KpiDSDeltaR;
      std::vector<double> KpiTrkScharge;
      //MC
      std::vector<double> MCLambdaDeltaR;
      //K3pi tracks vars
      std::vector<double> K3piTrkKnhits,K3piTrk1pinhits,K3piTrk2pinhits,K3piTrk3pinhits,K3piTrkSnhits;
      std::vector<double> K3piTrkKchi2,K3piTrk1pichi2,K3piTrk2pichi2,K3piTrk3pichi2,K3piTrkSchi2;
      std::vector<double> K3piTrkKpt,K3piTrk1pipt,K3piTrk2pipt,K3piTrk3pipt,K3piTrkSpt;
      std::vector<double> K3piTrkKdxy,K3piTrk1pidxy,K3piTrk2pidxy,K3piTrk3pidxy,K3piTrkSdxy,K3piTrkSdxyErr;
      std::vector<double> K3piTrkKdz,K3piTrk1pidz,K3piTrk2pidz,K3piTrk3pidz,K3piTrkSdz,K3piTrkSdzErr;
      std::vector<double> K3piTrkKeta,K3piTrk1pieta,K3piTrk2pieta,K3piTrk3pieta,K3piTrkSeta;
      std::vector<double> K3piTrkKphi,K3piTrk1piphi,K3piTrk2piphi,K3piTrk3piphi,K3piTrkSphi;
      std::vector<double> K3piDSDeltaR;
      std::vector<double> K3piTrkScharge;
      //MC
      std::vector<double> MCLambdaDeltaR3;
      std::vector<int> K3pi_MC_mode;

      edm::EDGetTokenT<reco::TrackCollection> TrackCollT_;
      edm::EDGetTokenT<reco::TrackCollection> TrackCollT_noPXB1_;
      edm::EDGetTokenT<reco::VertexCollection> VtxCollT_;
      edm::EDGetTokenT<reco::GenParticleCollection> GenCollT_;
  
      edm::Handle<reco::GenParticleCollection> genParticles;
  
      typedef edm::AssociationMap<edm::OneToManyWithQuality< reco::VertexCollection, reco::TrackCollection, int> > TrackVertexAssMap;
      edm::Handle<TrackVertexAssMap> assomap;
      edm::EDGetTokenT<TrackVertexAssMap> T2VCollT_;
      typedef std::vector<TrackingParticle> TrackingParticleCollection;
      edm::EDGetTokenT<TrackingParticleCollection> TrackingParticleCollT_;
      typedef std::vector<TrackingVertex> TrackingVertexCollection;
      edm::EDGetTokenT<TrackingVertexCollection> TrackingVertexCollT_;

};

LambdaAnalyzer::LambdaAnalyzer(const edm::ParameterSet& iConfig):
   doGen(iConfig.getParameter<bool>("doGen")),
   doK3pi(iConfig.getParameter<bool>("doK3pi")),
   doKpi(iConfig.getParameter<bool>("doKpi"))
{
   //now do what ever initialization is needed
   edm::Service<TFileService> fs;
   tree1 = fs->make<TTree>("tree1","tree1");
   //tree2 = fs->make<TTree>("tree2","tree2");
  
   TrackCollT_ = consumes<reco::TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"));
   TrackCollT_noPXB1_ = consumes<reco::TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks_noPXB1"));
   VtxCollT_ = consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("vertices"));
   GenCollT_ = consumes<reco::GenParticleCollection>(iConfig.getUntrackedParameter<edm::InputTag>("genParticles"));
   T2VCollT_ = consumes<TrackVertexAssMap>(iConfig.getUntrackedParameter<edm::InputTag>("T2V"));
    //MixCollT_ = consumes<edm::TrackingParticle>(iConfig.getUntrackedParameter<edm::InputTag>("mix"));

   TrackingParticleCollT_ = consumes<TrackingParticleCollection>(iConfig.getParameter<edm::InputTag>("trackingParticles") );
   TrackingVertexCollT_ = consumes<TrackingVertexCollection>(iConfig.getParameter<edm::InputTag>("trackingParticles") );


}

LambdaAnalyzer::~LambdaAnalyzer(){}

void LambdaAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;

  m_pi=0.13957018;
  m_K=0.493677;
  m_p = 0.9382720813;

  //clean vectors and vars
  initialize();

  //run, event, lumi section
  run_n = iEvent.id().run();
  event_n = iEvent.id().event();
  lumi = iEvent.luminosityBlock();

  //if (run_n != 254790 || lumi != 292) {
  //    return;
  //}
 
  //if (event_n != 387623140)  {
  //    //std::cout<<"Found the right lumi and run number, but not the correct event number"<<std::endl;
  //    //std::cout<<"event_n = "<<event_n<<std::endl;      
  //    return; 
 // }

  //std::cout<<"We found the event!!!!"<<std::endl;

  //HLT trigger
  //edm::Handle<TriggerResults> HLTR;
  //iEvent.getByLabel("TriggerResults",HLTR);
  //
  //for(size_t itrig=0;itrig != HLTR->size();++itrig){
  // if(HLTR->accept(itrig)) 
  //   trigflag[itrig]=1;
  // else 
  //   trigflag[itrig]=0;
 // }

/*
  Handle<TriggerResults>  hltresults;
  InputTag tag("TriggerResults");
  iEvent.getByLabel(tag,hltresults);

  TriggerNames triggerNames_;
  triggerNames_.init(* hltresults);

  int ntrigs = hltresults->size();
  for (int itrig = 0; itrig != ntrigs; ++itrig){
    TString trigName=triggerNames_.triggerName(itrig);
    bool accept = hltresults->accept(itrig);
    if (accept){trigflag[itrig] = 1;}
    else {trigflag[itrig] = 0;}
  }
*/
 
  // wasn't working on MC, I don't think we need it anyway
  /*//BeamSpot
  reco::BeamSpot vertexBeamSpot;
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
  //iEvent.getByType(recoBeamSpotHandle);
  iEvent.getByLabel("offlineBeamSpot", recoBeamSpotHandle); 
  vertexBeamSpot = *recoBeamSpotHandle;

  BSx=vertexBeamSpot.x0();
  BSy=vertexBeamSpot.y0();
  BSz=vertexBeamSpot.z0();
  BSerrx=vertexBeamSpot.x0Error();
  BSerry=vertexBeamSpot.y0Error();
  BSerrz=vertexBeamSpot.z0Error();*/


  Handle<TrackCollection> generalTracks;
  iEvent.getByToken(TrackCollT_, generalTracks);
  Handle<TrackCollection> generalTracks_noPXB1;
  iEvent.getByToken(TrackCollT_noPXB1_, generalTracks_noPXB1);
  //iEvent.getByLabel("generalTracks",generalTracks);

  edm::Handle<TrackingParticleCollection> TruthTrackContainer ;
  iEvent.getByToken( TrackingParticleCollT_, TruthTrackContainer );
  //const TrackingParticleCollection *tPC = TruthTrackContainer.product();

  tPC = TruthTrackContainer.product();
  edm::Handle<TrackingVertexCollection> TruthVertexContainer ;
  iEvent.getByToken( TrackingVertexCollT_, TruthVertexContainer );
  const TrackingVertexCollection *tVC = TruthVertexContainer.product();

  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  ///////t_tks = (*theB).build(generalTracks_noPXB1);
  t_tks = (*theB).build(generalTracks);
  t_tks_noPXB1 = (*theB).build(generalTracks_noPXB1);

  // Primary Vtx with most tracks
  Handle<reco::VertexCollection> recVtxs;
  iEvent.getByToken(VtxCollT_, recVtxs);
  //iEvent.getByLabel("offlinePrimaryVertices", recVtxs); //has a BeamSpot if no vtx found;

  std::vector<reco::Track> slowPitrks;
  std::vector<reco::Track> goodtrks;

  // Get Matched Vertices
  //typedef AssociationMap<OneToManyWithQuality< VertexCollection, TrackCollection, int> > TrackVertexAssMap;
  //Handle<TrackVertexAssMap> assomap;
  //iEvent.getByLabel("Tracks2Vertex",assomap); 
  /////iEvent.getByToken(T2VCollT_, assomap);
 
  //////nPV = assomap->size();
  nPV = recVtxs->size();
  int itnum = 0;
  for(size_t i = 0; i < recVtxs->size(); ++ i) {
  //for(TrackVertexAssMap::const_iterator iAM = assomap->begin(); iAM != assomap->end(); iAM++) {
    itnum++;
    //if (itnum==1) continue; // ignore first PV, as per Vincenzo's suggestion
    //if (itnum!=1) continue; // only consider first vertex, to match with Valentina
    const Vertex &RecVtx = (*recVtxs)[i];
    //const Vertex &RecVtx = *(iAM->key);
    //std::cout<<"processing a reco vtx: "<<i<<std::endl;
    //std::cout<<"ndof = "<<RecVtx.ndof()<<std::endl;
    //std::cout<<"tracksSize = "<<RecVtx.tracksSize()<<std::endl;
    //std::cout<<"isFake = "<<RecVtx.isFake()<<std::endl;
    if(RecVtx.ndof()<4 || RecVtx.tracksSize()<3 || RecVtx.isFake()) continue;  
    //std::cout << "vertex: " << itnum << " ntracks: " << RecVtx.tracksSize() << std::endl;
   
    PVOrder = itnum;
    PVx = RecVtx.x();
    PVy = RecVtx.y();
    PVz = RecVtx.z();
    PVerrx = sqrt(RecVtx.covariance(0,0));
    PVerry = sqrt(RecVtx.covariance(1,1));
    PVerrz = sqrt(RecVtx.covariance(2,2));
    PVcxy = RecVtx.covariance(0,1);
    PVcxz = RecVtx.covariance(0,2);
    PVcyz = RecVtx.covariance(1,2);

    // track selector


    // first build transient tracks 
    std::vector<TransientTrack> vtx_trks;
    vtx_trks.reserve(RecVtx.tracksSize());

    for(reco::Vertex::trackRef_iterator trk_it = RecVtx.tracks_begin(); trk_it != RecVtx.tracks_end(); ++trk_it){

      const Track& track = *trk_it->get();
      vtx_trks.push_back( (*theB).build(track) );	
    }
     //for(size_t j=0;j<vtx_trks.size();j++){
     for (size_t j=0;j<t_tks.size();j++) {     

     //TransientTrack t_trk = vtx_trks.at(j);
     TransientTrack t_trk = t_tks.at(j);
  
      if( fabs(t_trk.track().eta())<2.4 && 
       //   t_trk.track().normalizedChi2() < 10.0 &&
          t_trk.track().pt() > 0.25){
        //if ( fabs(t_trk.track().dxy(RecVtx.position()) / t_trk.track().d0Error()) < 3.0
        //  && fabs(t_trk.track().dz(RecVtx.position()) / t_trk.track().dzError()) < 3.0) {
        //    slowPiTracks.push_back( &t_tks.at(j));
        //}
        if( (t_trk.track().numberOfValidHits() >= 7) && (t_trk.track().pt() > 0.35) &&
          fabs(t_trk.track().dz(RecVtx.position()))<2.0 &&
          fabs(t_trk.track().dxy(RecVtx.position()) / t_trk.track().d0Error()) > 2.0 ) {
          //fabs(t_trk.track().dxy(RecVtx.position()))<0.1 && 
          goodTracks.push_back( &t_tks.at(j) );
        }
      }
      //slowPiTracks.push_back( &t_tks.at(j));
      //goodTracks.push_back( &t_tks.at(j) );
      //slowPiTracks.push_back( &vtx_trks.at(j));
      //goodTracks.push_back( &vtx_trks.at(j) );
      //cout<<"track pt, eta, phi, dxy, dz, nhits, chi2: "<<t_trk.track().pt()<<", "<<t_trk.track().eta()<<", "<<t_trk.track().phi()<<", "<<t_trk.track().dxy(RecVtx.position())<<", "<<t_trk.track().dz(RecVtx.position())<<", "<<t_trk.track().numberOfValidHits()<<", "<<t_trk.track().normalizedChi2()<<endl;
    }

    ntracks = slowPiTracks.size();

    //cout << t_tks.size() << "  " << slowPiTracks.size() << " " << goodTracks.size() << endl;

    if(doGen)
      printGenInfo(iEvent);
    loop(iEvent,iSetup,RecVtx);
    //cout << "loop done" << endl;
    goodTracks.clear();
    initialize();
  }
  
  
}

void LambdaAnalyzer::loop(const edm::Event& iEvent, const edm::EventSetup& iSetup, const reco::Vertex& RecVtx){

  using namespace std;
  using namespace reco;
  using namespace edm;

  //cout << RecVtx.position() << endl;
  //cout<<"Starting loop"<<endl;

  for(size_t i=0;i<goodTracks.size();i++){  

    TransientTrack* trk1 = goodTracks.at(i);

    for(size_t j=i+1;j<goodTracks.size();j++){
    
      TransientTrack* trk2 = goodTracks.at(j);

      if(trk1->charge() == trk2->charge()) continue;
      //cout<<"pass1"<<std::endl;

      ////math::XYZVector Lambda_p = trk1->track().momentum() + trk2->track().momentum();

      //////if(sqrt(Lambda_p.perp2()) < 3.) continue;
      //cout<<"pass2"<<std::endl;

      //for(size_t k=0;k<slowPiTracks.size();k++){

        //TransientTrack* trkS = slowPiTracks.at(k);

        //if(*trkS == *trk1 || *trkS == *trk2) continue;
        //cout<<"pass3"<<std::endl;

        //math::XYZVector DS_p = Lambda_p + trkS->track().momentum();
        //if(sqrt(DS_p.perp2())<4.) continue;
        //cout<<"pass4"<<std::endl;
   
        TransientTrack *pi1=0,*proton=0;

        // tag the tracks
        if (trk1->charge() < 0.) {
            pi1 = trk1;
            proton = trk2;
        }
        else {
            pi1 = trk2;
            proton = trk1;
        }
        //if (abs(pi1->track().pt() - 1.1041716) < 0.01) {
        //    cout<<"Found the pions!!"<<endl;
        //    cout<<"Pion1 pt: "<<pi1->track().pt()<<endl;
        //    cout<<"Pion2 pt: "<<proton->track().pt()<<endl;
        //}
        //before vertexing do loose preselection
        //math::XYZTLorentzVector ip4_pi1(pi1->track().px(),pi1->track().py(),pi1->track().pz(),sqrt(pow(pi1->track().p(),2)+pow(m_pi,2)));
        //math::XYZTLorentzVector ip4_proton(proton->track().px(),proton->track().py(),proton->track().pz(),sqrt(pow(proton->track().p(),2)+pow(m_pi,2)));

        //math::XYZTLorentzVector ip4_Lambda = ip4_pi1 + ip4_proton;
  
        //cout<<"pass5"<<std::endl;

        //math::XYZTLorentzVector p4_S(trkS->track().px(),trkS->track().py(),trkS->track().pz(),sqrt(pow(trkS->track().p(),2)+pow(m_pi,2)));
        //math::XYZTLorentzVector ip4_DS = ip4_Lambda + p4_S;
        //if((ip4_DS.M() - ip4_Lambda.M()) > 0.3) continue;
      //cout<<"pass6"<<std::endl;

        //now the time consuming vertexing

        vector<TransientTrack> tks;
        tks.push_back(*pi1);
        tks.push_back(*proton);
        KalmanVertexFitter kalman(true);
        TransientVertex v = kalman.vertex(tks);
        if(!v.isValid() || !v.hasRefittedTracks()) continue;
      //cout<<"pass7"<<std::endl;
        double vtxProb =TMath::Prob( (Double_t) v.totalChiSquared(), (Int_t) v.degreesOfFreedom());
        if (vtxProb < 0.05) continue;
      //cout<<"pass8"<<std::endl;
        TransientTrack pi1_f = v.refittedTrack(*pi1);
        TransientTrack proton_f = v.refittedTrack(*proton);        
        //TransientTrack pi1_f = *pi1;
        //TransientTrack proton_f = *proton;
      
        GlobalPoint vert(v.position().x(), v.position().y(), v.position().z());
        TrajectoryStateClosestToPoint  traj1 = pi1->trajectoryStateClosestToPoint(vert );
        TrajectoryStateClosestToPoint  traj2 = proton->trajectoryStateClosestToPoint(vert );
        double d0_1 = traj1.perigeeParameters().transverseImpactParameter();
        double d0_1_error = traj1.perigeeError().transverseImpactParameterError();
        double d0_2 = traj2.perigeeParameters().transverseImpactParameter();
        double d0_2_error = traj2.perigeeError().transverseImpactParameterError();
        //if ( (d0_1/d0_1_error) > 4.0 || (d0_2/d0_2_error) > 4.0) continue;
        

 
        math::XYZTLorentzVector ip4_pi1(pi1_f.track().px(),pi1_f.track().py(),pi1_f.track().pz(),sqrt(pow(pi1_f.track().p(),2)+pow(m_pi,2)));
        math::XYZTLorentzVector ip4_proton(proton_f.track().px(),proton_f.track().py(),proton_f.track().pz(),sqrt(pow(proton_f.track().p(),2)+pow(m_p,2)));

        math::XYZTLorentzVector ip4_Lambda = ip4_pi1 + ip4_proton;
        //double d0mass = d0_p4.M();
        //if(fabs(d0mass - 1.86484)>0.030) continue;
      //cout<<"d0mass = "<<d0mass<<endl;
      //cout<<"pass9"<<std::endl;
        if( fabs(ip4_Lambda.M()-1.1157)  > 0.05) continue;
   
       // math::XYZTLorentzVector dS_p4 = d0_p4 + p4_S;
       // double dsmass = dS_p4.M();
       // if( (dsmass - d0mass) > 0.16) continue;
      //cout<<"pass10"<<std::endl;

        //reco::vertex RecVtx (PV), TransientVertex v (Lambda vertex)  
        math::XYZVector PV_position = math::XYZVector(RecVtx.position().x(), RecVtx.position().y(), RecVtx.position().z() );
        math::XYZVector Lambda_position = math::XYZVector(v.position().x(), v.position().y(), v.position().z() );

        math::XYZVector displacement = Lambda_position - PV_position;
        math::XYZVector Lambda_3vector = math::XYZVector(ip4_Lambda.Px(), ip4_Lambda.Py(), ip4_Lambda.Pz());
        double cosalpha = (displacement.Dot(Lambda_3vector) - displacement.Z()*Lambda_3vector.Z() ) / ( sqrt(displacement.perp2()) * sqrt(Lambda_3vector.perp2()) );
        //double flightlength = sqrt(displacement.perp2()) * (cosalpha/fabs(cosalpha)); // flight length in the transverse plane
        //double flightlength = sqrt(displacement.perp2()) * cosalpha; // flight length in the transverse plane in the direction of momentum (what we call lifetime in AN)
        double flightlength = sqrt( displacement.perp2());

        // calculate lifetime significance
        double deriv_x = displacement.X() / fabs(flightlength);
        double deriv_y = displacement.Y() / fabs(flightlength);
    
        double sigma_L = pow(deriv_x,2) * (pow(PVerrx,2) + v.positionError().cxx()) + pow(deriv_y,2) * (pow(PVerry,2) + v.positionError().cyy()) + 2*deriv_x*deriv_y * (PVcxy + v.positionError().cyx());
        sigma_L = sqrt(sigma_L);
        double LSig = flightlength / sigma_L;
       
        if (LSig < 10.) continue;
 
        //double flightlength3D = (displacement.Dot(Lambda_3vector) ) / ( sqrt(Lambda_3vector.Mag2()) );
        double flightlength3D = sqrt(displacement.Mag2());
        double cosalpha3D = (displacement.Dot(Lambda_3vector) ) / ( sqrt(Lambda_3vector.Mag2()) * sqrt(displacement.Mag2()) );
        double deriv3D_x = displacement.X() / fabs(flightlength3D);
        double deriv3D_y = displacement.Y() / fabs(flightlength3D);
        double deriv3D_z = displacement.Z() / fabs(flightlength3D);

        double sigma_L3D = pow(deriv3D_x,2) * (pow(PVerrx,2) + v.positionError().cxx()) + pow(deriv3D_y,2) * (pow(PVerry,2) + v.positionError().cyy()) + pow(deriv3D_z,2) * (pow(PVerrz,2) + v.positionError().czz()) + 2*deriv3D_x*deriv3D_y * (PVcxy + v.positionError().cyx()) + 2*deriv3D_x*deriv3D_z * (PVcxz + v.positionError().czx()) + 2*deriv3D_y*deriv3D_z * (PVcyz + v.positionError().czy());

        sigma_L3D = sqrt(sigma_L3D);
        double LSig3D = flightlength3D / sigma_L3D;

        if (cosalpha < 0.9998) continue;
        //if (cosalpha < 0) continue;
      //cout<<"passALL"<<std::endl;
      //cout<<"pion has pt: "<<pi1->track().pt()<<std::endl;
      //cout<<"pion has unfitted pt: "<<pi1->track().pt()<<std::endl;
        if(doGen){
        
          //Handle<GenParticleCollection> genParticles;
          //iEvent.getByLabel("genParticles",genParticles);
          iEvent.getByToken(GenCollT_, genParticles);
        
          double dR = 99.;
 
          for(size_t i=0; i<LambdaDPicands.size();i++){
            const reco::GenParticle & la = genParticles->at(LambdaDPicands.at(i));
            double delta_R = deltaR(ip4_Lambda.eta(),ip4_Lambda.phi(),la.eta(),la.phi());
            //double delta_R = 99.;
            //if(delta_R < 0.15 && delta_R < dR)
            if(delta_R < dR)
              dR = delta_R;
          }

          MCLambdaDeltaR.push_back(dR);
        }
        // little test
        //std::cout<<"testing..."<<std::endl;
        //std::cout<<pi1_f.numberOfValidHits()<<std::endl;
        //std::cout<<pi1->hitPattern().getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,0)<<std::endl;
        //for (int i=0; i<pi1->numberOfValidHits(); i++) {
        //    std::cout<<"i = "<<i<<std::endl;
        //    std::cout<<pi1->hitPattern().getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,i)<<std::endl;

        //}
        //for (int i=0; i<proton->numberOfValidHits(); i++) {
        //    std::cout<<"i = "<<i<<std::endl;
        //    std::cout<<proton->hitPattern().getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,i)<<std::endl;

        //}
        //pixelBarrelHitFilter
//        int nSharedPBHits = 0;
//        std::vector<uint16_t> pion_pxb_hits;
//        reco::HitPattern hp_pion = pi1->hitPattern();
//        reco::HitPattern hp_proton = proton->hitPattern();
//        for (int i=0; i<pi1->numberOfValidHits(); i++) {
//            uint16_t hit = hp_pion.getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,i);
//            if (!hp_pion.validHitFilter(hit) || !hp_pion.pixelBarrelHitFilter(hit)) { continue;}
//            pion_pxb_hits.push_back(hit);
//        }
//        for (int i=0; i<proton->numberOfValidHits(); i++) {
//            uint16_t hit2 = hp_proton.getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,i);
//            if (!hp_proton.validHitFilter(hit2) || !hp_proton.pixelBarrelHitFilter(hit2)) { continue;}
//            if(std::find(pion_pxb_hits.begin(), pion_pxb_hits.end(), hit2) != pion_pxb_hits.end()) {
//                nSharedPBHits += 1;
//                std::cout<<"found shared pixel barrel hit! : "<<hit2<<" layer : "<<hp_proton.getLayer(hit2)<<std::endl;
//            }
//        }
//        std::cout<<"nSharedPBHits = "<<nSharedPBHits<<std::endl;
        trackingRecHit_iterator hb_pi1 = pi1->recHitsBegin();
        trackingRecHit_iterator hb_proton = proton->recHitsBegin();
        TrackingRecHit const * h1[4] = { (*hb_pi1), (*(hb_pi1+1)), (*(hb_pi1+2)), (*(hb_pi1+3))  };
        TrackingRecHit const * h2[4] = { (*hb_proton), (*(hb_proton+1)), (*(hb_proton+2)), (*(hb_proton+3)) };
        //std::cout<<"new lambda pairing"<<std::endl;
        bool foundSharedHit = false;
        bool foundSharedHitLayer0 = true;
        for (int k1=0; k1<4; k1++) {
            if (!h1[k1]->isValid()) continue;
            for (int k2=0; k2<4; k2++) {
                if (!h2[k2]->isValid()) continue;
                bool shared = h1[k1]->sharesInput(h2[k2],TrackingRecHit::some);
                if (shared) {
                    //std::cout<<"k1, k2 = "<<k1<<" : "<<k2<<std::endl;
                    //std::cout<<"h1[k1], h2[k2] = "<<h1[k1]<<" : "<<h2[k2]<<std::endl;
                    //std::cout<<h1[k1]->geographicalId()<<std::endl;
                    PXBDetId pxb_id = h1[k1]->geographicalId();
                    //std::cout<<pxb_id.layer()<<std::endl;
                    //std::cout<<pxb_id.ladder()<<std::endl;
                    //std::cout<<pxb_id.module()<<std::endl;
                    LambdaSharedHitLayer.push_back(pxb_id.layer());
                    LambdaSharedHitLadder.push_back(pxb_id.ladder());
                    LambdaSharedHitModule.push_back(pxb_id.module());
                    foundSharedHit = true;
                    if (pxb_id.layer() == 0) {
                        foundSharedHitLayer0 = true;
                    }
                    break; // only consider the innermost shared hit
                    //std::cout<<int(h1[k1]->geographicalId())<<std::endl;
                    //std::cout<<h1[k1]->det().subDetector().<<std::endl;
                    //std::cout<<h1[k1]->globalPosition().perp()<<std::endl;
                    //std::cout<<"position = "<<h1[k1]->globalPosition().x()<<" : "<<h1[k1]->globalPosition().y()<<" : "<<h1[k1]->globalPosition().z()<<" : "<<std::endl;
                }
            }
        }
        if (!foundSharedHit) {
            LambdaSharedHitLayer.push_back(-99);
            LambdaSharedHitLadder.push_back(-99);
            LambdaSharedHitModule.push_back(-99);
        } 

        double flightlength_noPXB1 = -99.;
        double flightlength_noPXB1_error = -99.;
        // try to rebuild Lambda candidate using the corresponding proton/pion tracks with hits at layer 0 removed
        if (foundSharedHitLayer0) {
            double minDR_pi1 = 999.;
            double minDR_proton = 999.;
            TransientTrack pi1_noPXB1; 
            TransientTrack proton_noPXB1; 
            for (size_t j=0;j<t_tks_noPXB1.size();j++) {
                TransientTrack t_trk = t_tks_noPXB1.at(j);
         
                if( fabs(t_trk.track().eta())<2.4 && 
                        t_trk.track().pt() > 0.25){
                    if( (t_trk.track().numberOfValidHits() >= 6) && (t_trk.track().pt() > 0.35) &&
                        fabs(t_trk.track().dz(RecVtx.position()))<2.0 &&
                        fabs(t_trk.track().dxy(RecVtx.position()) / t_trk.track().d0Error()) > 2.0 ) {
                        double deta_pi1 = fabs(pi1->track().eta() - t_trk.track().eta()); 
                        double dphi_pi1 = fabs(pi1->track().phi() - t_trk.track().phi());
                        double dr_pi1 = TMath::Sqrt(TMath::Power(deta_pi1,2) + TMath::Power(dphi_pi1,2));
                        if (dr_pi1 < minDR_pi1) {
                            minDR_pi1 = dr_pi1;
                            pi1_noPXB1 = t_trk;
                        }
                        double deta_proton = fabs(proton->track().eta() - t_trk.track().eta()); 
                        double dphi_proton = fabs(proton->track().phi() - t_trk.track().phi());
                        double dr_proton = TMath::Sqrt(TMath::Power(deta_proton,2) + TMath::Power(dphi_proton,2));
                        if (dr_proton < minDR_proton && minDR_pi1 != dr_pi1) {
                            minDR_proton = dr_proton;
                            proton_noPXB1 = t_trk;
                        }
                    }
                }
            }
            if (minDR_pi1 < 0.01 && minDR_proton < 0.01) {
                //std::cout<<"min DR's: "<<minDR_pi1<<" : "<<minDR_proton<<std::endl;
                vector<TransientTrack> tks_noPXB1;
                tks_noPXB1.push_back(pi1_noPXB1);
                tks_noPXB1.push_back(proton_noPXB1);
                //KalmanVertexFitter kalman(true);
                TransientVertex v_noPXB1 = kalman.vertex(tks_noPXB1);
                if(v_noPXB1.isValid() && v_noPXB1.hasRefittedTracks()) {
                    //double vtxProb =TMath::Prob( (Double_t) v.totalChiSquared(), (Int_t) v.degreesOfFreedom());
                    //if (vtxProb < 0.05) continue;
                    //TransientTrack pi1_f_noPXB1 = v_noPXB1.refittedTrack(*pi1_noPXB1);
                    //TransientTrack proton_f_noPXB1 = v_noPXB1.refittedTrack(*proton_noPXB1);        
                    math::XYZVector Lambda_position_noPXB1 = math::XYZVector(v_noPXB1.position().x(), v_noPXB1.position().y(), v_noPXB1.position().z() );

                    math::XYZVector displacement_noPXB1 = Lambda_position_noPXB1 - PV_position;
                    flightlength_noPXB1 = sqrt( displacement_noPXB1.perp2());
                    //std::cout<<"flight length with PXB1: "<<flightlength<<" : and without PXB1: "<<flightlength_noPXB1<<std::endl;
                    double deriv_x_noPXB1 = displacement_noPXB1.X() / fabs(flightlength_noPXB1);
                    double deriv_y_noPXB1 = displacement_noPXB1.Y() / fabs(flightlength_noPXB1);
                    flightlength_noPXB1_error = pow(deriv_x_noPXB1,2) * (pow(PVerrx,2) + v_noPXB1.positionError().cxx()) + pow(deriv_y_noPXB1,2) * (pow(PVerry,2) + v_noPXB1.positionError().cyy()) + 2*deriv_x_noPXB1*deriv_y_noPXB1 * (PVcxy + v_noPXB1.positionError().cyx());
                    flightlength_noPXB1_error = sqrt(flightlength_noPXB1_error);
                    //std::cout<<"change in relative flight length error: "<<sigma_L<< " : "<<sigma_L_noPXB1<<std::endl;
                } 
            }
        }
        

        //}
        //std::cout<<pi1_f.hitPattern().getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,0)<<std::endl;
        //std::cout<<proton_f.hitPattern().getHitPattern(reco::HitPattern::HitCategory::TRACK_HITS,0)<<std::endl;

        // find point of closest approach between lambda momentum vector and vertex
        double x_p = ip4_Lambda.X(); 
        double y_p = ip4_Lambda.Y(); 
        double z_p = ip4_Lambda.Z();
        double scale_ca = (x_p*PVx + y_p*PVy + z_p*PVz )/(x_p*x_p + y_p*y_p + z_p*z_p);

        //Iterate over lambdas to find the best match to pion/proton tracks
        double min_dR = 99;
        double pion_dR = 99;
        double p_dR = 99;
        
        TrackingParticle genLambda;
        TrackingVertexRef genLambdaVtx;
        TrackingParticleRef genPion;
        TrackingParticleRef genProton;
        TrackingParticleRefVector decayTracks;

        for(TrackingParticleCollection::const_iterator iter = tPC->begin(); iter != tPC->end(); ++iter){
           //is lambda?
           if(iter->pdgId()==3122){
              TrackingVertexRef decayVtx = *(iter->decayVertices().end()-1);//some lambdas have multiple decay vertices, looking at just the last one seems to work
              decayTracks = decayVtx->daughterTracks();
              
              //check lambda decays to p,pi?
              if(decayTracks.size() >= 2){
                 if(decayTracks.at(0)->pdgId()==-211 && decayTracks.at(1)->pdgId()==2212){
                    genPion = decayTracks.at(0);
                    genProton = decayTracks.at(1);
                 }
                 else if(decayTracks.at(0)->pdgId()==2212 && decayTracks.at(1)->pdgId()==-211){
                    genPion = decayTracks.at(1);
                    genProton = decayTracks.at(0);
                 }
                 else continue;
                 //Now we have the pion/proton tracks
                 pion_dR = deltaR(ip4_pi1.Eta(),ip4_pi1.Phi(),genPion->eta(),genPion->phi());  
                 p_dR = deltaR(ip4_proton.Eta(),ip4_proton.Phi(),genProton->eta(),genProton->phi());   
                 if(pion_dR + p_dR < min_dR){
                    min_dR = pion_dR + p_dR;
                    genLambda = tPC->at(std::distance(tPC->begin(), iter));
                    genLambdaVtx = decayVtx;
                 }
              }
           }
        }
         
        LambdaVtxProb.push_back(vtxProb);
        LambdaVtxLSig.push_back(LSig);
        LambdaVtxLSig3D.push_back(LSig3D);
        LambdaMass.push_back(ip4_Lambda.M());
        LambdaPtKpi.push_back(ip4_Lambda.Pt());
        Lambdaeta.push_back(ip4_Lambda.eta());
        Lambdaphi.push_back(ip4_Lambda.phi());
        LamdaVertexCAx.push_back(scale_ca*x_p);
        LamdaVertexCAy.push_back(scale_ca*y_p);
        LamdaVertexCAz.push_back(scale_ca*z_p);

        cosAlpha3D.push_back(cosalpha3D);
        cosAlpha.push_back(cosalpha);
        flightLength.push_back(flightlength);
        flightLength_noPXB1.push_back(flightlength_noPXB1);
        flightLength_noPXB1_error.push_back(flightlength_noPXB1_error);

        LambdaVtxPosx.push_back(v.position().x());
        LambdaVtxPosy.push_back(v.position().y());
        LambdaVtxPosz.push_back(v.position().z());
        LambdaVtxerrx.push_back(sqrt(v.positionError().cxx()));
        LambdaVtxerry.push_back(sqrt(v.positionError().cyy()));
        LambdaVtxerrz.push_back(sqrt(v.positionError().czz()));
        LambdaVtxcxy.push_back(v.positionError().cyx());
        LambdaVtxcxz.push_back(v.positionError().czx());
        LambdaVtxcyz.push_back(v.positionError().czy());

//        KpiTrkKdxy.push_back(K_f.track().dxy(RecVtx.position()));
//        KpiTrkpidxy.push_back(pi_f.track().dxy(RecVtx.position()));
//        KpiTrkSdxy.push_back(trkS->track().dxy(RecVtx.position()));
//        KpiTrkSdxyErr.push_back(trkS->track().d0Error());

//        KpiTrkKdz.push_back(K_f.track().dz(RecVtx.position()));
//        KpiTrkpidz.push_back(pi_f.track().dz(RecVtx.position()));
//        KpiTrkSdz.push_back(trkS->track().dz(RecVtx.position()));
//        KpiTrkSdzErr.push_back(trkS->track().dzError());

//        KpiTrkKnhits.push_back(K->track().numberOfValidHits());
//        KpiTrkpinhits.push_back(pi->track().numberOfValidHits());
//        KpiTrkSnhits.push_back(trkS->track().numberOfValidHits());

//        KpiTrkKchi2.push_back(K->track().normalizedChi2());
//        KpiTrkpichi2.push_back(pi->track().normalizedChi2());
//        KpiTrkSchi2.push_back(trkS->track().normalizedChi2());

//        KpiDSDeltaR.push_back(deltaR(d0_p4.eta(),d0_p4.phi(),trkS->track().eta(),trkS->track().phi()));

          TrkPi1pt.push_back(ip4_pi1.Pt());
          TrkProtonpt.push_back(ip4_proton.Pt());
          TrkPi1eta.push_back(ip4_pi1.Eta());
          TrkProtoneta.push_back(ip4_proton.Eta());
          TrkPi1mass.push_back(ip4_pi1.M());
          TrkProtonmass.push_back(ip4_proton.M());
          TrkPi1phi.push_back(ip4_pi1.Phi());
          TrkProtonphi.push_back(ip4_proton.Phi());
          TrkPi1chi2.push_back(pi1->track().normalizedChi2());
          TrkProtonchi2.push_back(proton->track().normalizedChi2());
          TrkPi1ndof.push_back(pi1->track().ndof());
          TrkProtonndof.push_back(proton->track().ndof());
          TrkPi1dxy.push_back(pi1->track().dxy(RecVtx.position()));
          TrkPi1dz.push_back(pi1->track().dz(RecVtx.position()));
          TrkProtondxy.push_back(pi1->track().dxy(RecVtx.position()));
          TrkProtondz.push_back(pi1->track().dz(RecVtx.position()));
          PionProtondz.push_back(fabs(traj1.position().z()-traj2.position().z()));
          //TrkPi1pt.push_back(pi1->track().pt());
          //TrkProtonpt.push_back(proton->track().pt());
          //TrkPi1eta.push_back(pi1->track().eta());
          //TrkProtoneta.push_back(proton->track().eta());
          //TrkPi1mass.push_back(ip4_pi1.M());
          //TrkProtonmass.push_back(ip4_proton.M());
          //TrkPi1phi.push_back(pi1->track().phi());
          //TrkProtonphi.push_back(proton->track().phi());
          //TrkPi1chi2.push_back(pi1->track().normalizedChi2());
          //TrkProtonchi2.push_back(proton->track().normalizedChi2());
          //TrkPi1ndof.push_back(pi1->track().ndof());
          //TrkProtonndof.push_back(proton->track().ndof());
//        KpiTrkpipt.push_back(pi_f.track().pt());
//        KpiTrkSpt.push_back(trkS->track().pt());

//        KpiTrkKeta.push_back(K_f.track().eta());
//        KpiTrkpieta.push_back(pi_f.track().eta());
//        KpiTrkSeta.push_back(trkS->track().eta());

//        KpiTrkKphi.push_back(K_f.track().phi());
//        KpiTrkpiphi.push_back(pi_f.track().phi());
//        KpiTrkSphi.push_back(trkS->track().phi());

//        KpiTrkScharge.push_back(trkS->charge());

        GenLambdaVtxPosx.push_back(genLambdaVtx->position().x());
        GenLambdaVtxPosy.push_back(genLambdaVtx->position().y());
        GenLambdaVtxPosz.push_back(genLambdaVtx->position().z());
        GenLambdaSourceVtxPosx.push_back(genLambda.vx());
        GenLambdaSourceVtxPosy.push_back(genLambda.vy());
        GenLambdaSourceVtxPosz.push_back(genLambda.vz());
        GenLambdaPt.push_back(genLambda.pt());
        GenLambdaP.push_back(genLambda.p());
        GenLambdaPhi.push_back(genLambda.phi());
        GenLambdaEta.push_back(genLambda.eta());
        GenLambdaMass.push_back(genLambda.mass());
        GenLambdaMt.push_back(genLambda.mt());
        GenLambdaE.push_back(genLambda.energy());
        GenLambdaEt.push_back(genLambda.et());
        GenLambdaPx.push_back(genLambda.px());
        GenLambdaPy.push_back(genLambda.py());
        GenLambdaPz.push_back(genLambda.pz());
        GenDeltaR.push_back(min_dR);
        //genLambdaVtx->position is the lambda->pion,proton vertex.  genLambda.v() is the vertex the lambda is created at
        GenFlightLength.push_back(sqrt(pow(genLambdaVtx->position().x()-genLambda.vx(),2) + pow(genLambdaVtx->position().y() - genLambda.vy(),2) + pow(genLambdaVtx->position().z() - genLambda.vz(),2)));
        NKpiCand++;

        if(NKpiCand>999) break;
      //
      if(NKpiCand>999) break;
    } 
    if(NKpiCand>999) break;
  }

  if (NKpiCand > 0) {
      tree1->Fill();
  }
}


void LambdaAnalyzer::assignStableDaughters(const reco::Candidate* p, std::vector<int> & pids){

  std::cout<<"called assignStableDaughters for: "<<p->pdgId()<<std::endl;
  for(size_t i=0;i<p->numberOfDaughters();i++){
    if(p->daughter(i)->status()==1) {
      std::cout<<"adding stable daughter: "<<p->daughter(i)->pdgId()<<std::endl;
      pids.push_back(abs(p->daughter(i)->pdgId()));
    }
    else {
     std::cout<<"recursive call"<<std::endl;
     assignStableDaughters(p->daughter(i),pids);
    }
  }
  return;
}


void LambdaAnalyzer::printGenInfo(const edm::Event& iEvent){

  using namespace std;
  using namespace reco;
  using namespace edm;

  //Handle<GenParticleCollection> genParticles;
  //iEvent.getByLabel("genParticles",genParticles);
  iEvent.getByToken(GenCollT_, genParticles);

  for(size_t i=0;i<genParticles->size();i++){

    const reco::GenParticle & p = (*genParticles)[i];

    if(p.pdgId()==3122){ //Lambda
     
      LambdaDPicands.push_back(i); 
    }

  }
}

void LambdaAnalyzer::initialize(){
//clearing the vectors
  //analysis
  //ntracks.clear(); PVx.clear(); PVy.clear(); PVz.clear(); PVerrx.clear(); PVerry.clear(); PVerrz.clear();
  LambdaDPicands.clear();  dScandsK3pi.clear();  goodTracks.clear(); slowPiTracks.clear();
  //Kpi D* Lambda
  LambdaMass.clear();  DSMassKpi.clear();  LambdaVtxProb.clear(); LambdaVtxLSig.clear(); LambdaVtxLSig3D.clear();  LambdaPtKpi.clear();  DSPtKpi.clear();  LambdaVtxPosx.clear();
  LambdaVtxPosy.clear();  LambdaVtxPosz.clear();  Lambdaeta.clear();  Lambdaphi.clear();  LambdaVtxerrx.clear();  LambdaVtxerry.clear(); LamdaVertexCAx.clear(); LamdaVertexCAy.clear(); LamdaVertexCAz.clear();
  LambdaVtxerrz.clear();  LambdaVtxcxy.clear();   LambdaVtxcxz.clear();  LambdaVtxcyz.clear();  DSetaKpi.clear(); DSphiKpi.clear();
  cosAlphaK3pi.clear(); cosAlpha.clear(); cosAlpha3D.clear(); cosAlpha3DK3pi.clear(); flightLengthK3pi.clear(); flightLength.clear(); flightLength_noPXB1.clear(); flightLength_noPXB1_error.clear();
  LambdaSharedHitLayer.clear(); LambdaSharedHitLadder.clear(); LambdaSharedHitModule.clear();
  //K3pi D* Lambda
  LambdaMassK3pi.clear(); DSMassK3pi.clear(); LambdaMassK3pi1.clear();  DSMassK3pi1.clear();  LambdaVtxProb3.clear(); LambdaVtx3LSig.clear(); LambdaVtx3LSig3D.clear(); LambdaPtK3pi.clear();  DSPtK3pi.clear();  LambdaVtxPosx3.clear();
  LambdaVtxPosy3.clear();  LambdaVtxPosz3.clear();  LambdaetaK3pi.clear();  LambdaphiK3pi.clear();  LambdaVtxerrx3.clear();  LambdaVtxerry3.clear(); 
  LambdaVtxerrz3.clear(); LambdaVtx3cxy.clear();  LambdaVtx3cxz.clear();  LambdaVtx3cyz.clear(); DSetaK3pi.clear(); DSphiK3pi.clear();
  LambdaMassK3proton.clear(); DSMassK3proton.clear();
  //Kpi tracks
  KpiTrkKdxy.clear();  KpiTrkpidxy.clear();  KpiTrkSdxy.clear(); KpiTrkSdxyErr.clear();
  KpiTrkKdz.clear();  KpiTrkpidz.clear();  KpiTrkSdz.clear(); KpiTrkSdzErr.clear();
  TrkPi1pt.clear(); TrkProtonpt.clear(); TrkPi1eta.clear(); TrkProtoneta.clear(); TrkPi1phi.clear(); TrkProtonphi.clear(); TrkPi1mass.clear(); TrkProtonmass.clear(); TrkPi1chi2.clear(); TrkProtonchi2.clear(); TrkPi1ndof.clear(); TrkProtonndof.clear(); TrkPi1dxy.clear(); TrkPi1dz.clear(); TrkProtondxy.clear(); TrkProtondz.clear(); PionProtondz.clear();

  KpiTrkpipt.clear();  KpiTrkSpt.clear();
  KpiTrkKchi2.clear();  KpiTrkpichi2.clear();  KpiTrkSchi2.clear();
  KpiTrkKnhits.clear();  KpiTrkpinhits.clear();  KpiTrkSnhits.clear();
  KpiTrkKeta.clear();  KpiTrkpieta.clear();  KpiTrkSeta.clear();
  KpiTrkKphi.clear();  KpiTrkpiphi.clear();  KpiTrkSphi.clear();
  KpiDSDeltaR.clear(); KpiTrkScharge.clear();
  //MC
  MCLambdaDeltaR.clear();MCLambdaDeltaR3.clear(),K3pi_MC_mode.clear();

  //K3pi tracks
  K3piTrkKdxy.clear();  K3piTrk1pidxy.clear();  K3piTrk2pidxy.clear();  K3piTrk3pidxy.clear();  K3piTrkSdxy.clear(); K3piTrkSdxyErr.clear();
  K3piTrkKdz.clear();  K3piTrk1pidz.clear();  K3piTrk2pidz.clear();  K3piTrk3pidz.clear();  K3piTrkSdz.clear(); K3piTrkSdzErr.clear();
  K3piTrkKpt.clear();  K3piTrk1pipt.clear();  K3piTrk2pipt.clear();  K3piTrk3pipt.clear();  K3piTrkSpt.clear();
  K3piTrkKchi2.clear();  K3piTrk1pichi2.clear();  K3piTrk2pichi2.clear();  K3piTrk3pichi2.clear();  K3piTrkSchi2.clear();
  K3piTrkKnhits.clear();  K3piTrk1pinhits.clear();  K3piTrk2pinhits.clear();  K3piTrk3pinhits.clear();
  K3piTrkSnhits.clear();
  K3piTrkKeta.clear();  K3piTrk1pieta.clear();  K3piTrk2pieta.clear();  K3piTrk3pieta.clear();  K3piTrkSeta.clear();
  K3piTrkKphi.clear();  K3piTrk1piphi.clear();  K3piTrk2piphi.clear();  K3piTrk3piphi.clear();  K3piTrkSphi.clear();
  K3piDSDeltaR.clear(); K3piTrkScharge.clear();
  
  //Gen quantities
  GenLambdaVtxPosx.clear(); GenLambdaVtxPosy.clear(); GenLambdaVtxPosz.clear();
  GenLambdaSourceVtxPosx.clear(); GenLambdaSourceVtxPosy.clear(); GenLambdaSourceVtxPosz.clear();
  GenLambdaMass.clear(); GenLambdaPt.clear(); GenLambdaPhi.clear(); GenLambdaEta.clear(); GenLambdaMt.clear(); GenLambdaE.clear(); GenLambdaEt.clear(); GenLambdaPx.clear(); GenLambdaPy.clear(); GenLambdaPz.clear(); GenFlightLength.clear(); GenDeltaR.clear(); GenVertexMatch.clear();



  //MC ids
  //static variables
  for(int i=0;i<160;i++)
    trigflag[i]=0;
  BSx = BSy = BSz = BSerrx = BSerry = BSerrz = -99.;
  NKpiCand=0,NK3piCand=0,NKpiMC=0,NK3piMC=0;//,run_n=0,event_n=0,lumi=0;
}

void LambdaAnalyzer::beginJob()
{
tree1->Branch("trigflag",&trigflag,"trigflag[160]/I");
tree1->Branch("NKpiCand",&NKpiCand,"NKpiCand/I");
tree1->Branch("NKpiMC",&NKpiMC,"NKpiMC/I");

tree1->Branch("run_n",&run_n,"run_n/I");
tree1->Branch("event_n",&event_n,"event_n/I");
tree1->Branch("lumi",&lumi,"lumi/I");


tree1->Branch("LambdaMass",&LambdaMass);
tree1->Branch("LambdaVtxProb",&LambdaVtxProb);
tree1->Branch("LambdaVtxLSig",&LambdaVtxLSig);
tree1->Branch("LambdaVtxLSig3D",&LambdaVtxLSig3D);
tree1->Branch("LambdaVtxPosx",&LambdaVtxPosx);
tree1->Branch("LambdaVtxPosy",&LambdaVtxPosy);
tree1->Branch("LambdaVtxPosz",&LambdaVtxPosz);
tree1->Branch("LambdaVtxerrx",&LambdaVtxerrx);
tree1->Branch("LambdaVtxerry",&LambdaVtxerry);
tree1->Branch("LambdaVtxerrz",&LambdaVtxerrz);
tree1->Branch("LambdaVtxcxy", &LambdaVtxcxy);
tree1->Branch("LambdaVtxcxz", &LambdaVtxcxz);
tree1->Branch("LambdaVtxcyz", &LambdaVtxcyz);
tree1->Branch("Lambdaeta",&Lambdaeta);
tree1->Branch("Lambdaphi",&Lambdaphi);
tree1->Branch("LamdaVertexCAx",&LamdaVertexCAx);
tree1->Branch("LamdaVertexCAy",&LamdaVertexCAy);
tree1->Branch("LamdaVertexCAz",&LamdaVertexCAz);
tree1->Branch("cosAlpha",&cosAlpha);
tree1->Branch("cosAlpha3D",&cosAlpha3D);
tree1->Branch("flightLength", &flightLength);
tree1->Branch("flightLength_noPXB1", &flightLength_noPXB1);
tree1->Branch("flightLength_noPXB1_error", &flightLength_noPXB1_error);
tree1->Branch("LambdaSharedHitLayer",&LambdaSharedHitLayer);
tree1->Branch("LambdaSharedHitLadder",&LambdaSharedHitLadder);
tree1->Branch("LambdaSharedHitModule",&LambdaSharedHitModule);


//tracks
tree1->Branch("ntracks",&ntracks,"ntracks/I");
//primary vertex
tree1->Branch("PVOrder",&PVOrder,"PVOrder/I");
tree1->Branch("nPV",&nPV,"nPV/I");
tree1->Branch("PVx",&PVx,"PVx/D");
tree1->Branch("PVy",&PVy,"PVy/D");
tree1->Branch("PVz",&PVz,"PVz/D");
tree1->Branch("PVerrx",&PVerrx,"PVerrx/D");
tree1->Branch("PVerry",&PVerry,"PVerry/D");
tree1->Branch("PVerrz",&PVerrz,"PVerrz/D");
tree1->Branch("PVcxy", &PVcxy, "PVcxy/D");
tree1->Branch("PVcxz", &PVcxz, "PVcxz/D");
tree1->Branch("PVcyz", &PVcyz, "PVcyz/D");
tree1->Branch("BSx",&BSx,"BSx/D");
tree1->Branch("BSy",&BSy,"BSy/D");
tree1->Branch("BSz",&BSz,"BSz/D");
tree1->Branch("BSerrx",&BSerrx,"BSerrx/D");
tree1->Branch("BSerry",&BSerry,"BSerry/D");
tree1->Branch("BSerrz",&BSerrz,"BSerrz/D");

//pion tracks vars
tree1->Branch("TrkPi1pt",&TrkPi1pt);
tree1->Branch("TrkProtonpt",&TrkProtonpt);
tree1->Branch("TrkPi1eta",&TrkPi1eta);
tree1->Branch("TrkProtoneta",&TrkProtoneta);
tree1->Branch("TrkPi1mass",&TrkPi1mass);
tree1->Branch("TrkProtonmass",&TrkProtonmass);
tree1->Branch("TrkPi1phi",&TrkPi1phi);
tree1->Branch("TrkProtonphi",&TrkProtonphi);
tree1->Branch("TrkPi1chi2",&TrkPi1chi2);
tree1->Branch("TrkProtonchi2",&TrkProtonchi2);
tree1->Branch("TrkPi1ndof",&TrkPi1ndof);
tree1->Branch("TrkProtonndof",&TrkProtonndof);
tree1->Branch("TrkPi1dxy",&TrkPi1dxy);
tree1->Branch("TrkProtondxy",&TrkProtondxy);
tree1->Branch("TrkPi1dz",&TrkPi1dz);
tree1->Branch("TrkProtondz",&TrkProtondz);
tree1->Branch("PionProtondz",&PionProtondz);
//tree1->Branch("KpiTrkpipt",&KpiTrkpipt);
//tree1->Branch("KpiTrkSpt",&KpiTrkSpt);
tree1->Branch("LambdaPt",&LambdaPtKpi);
tree1->Branch("MCLambdaDeltaR",&MCLambdaDeltaR);
//tree1->Branch("DSPtKpi",&DSPtKpi);
//tree1->Branch("KpiDSDeltaR",&KpiDSDeltaR);
//tree1->Branch("KpiTrkKnhits",&KpiTrkKnhits);
//tree1->Branch("KpiTrkpinhits",&KpiTrkpinhits);
//tree1->Branch("KpiTrkSnhits",&KpiTrkSnhits);
//tree1->Branch("KpiTrkKchi2",&KpiTrkKchi2);
//tree1->Branch("KpiTrkpichi2",&KpiTrkpichi2);
//tree1->Branch("KpiTrkSchi2",&KpiTrkSchi2);
//tree1->Branch("KpiTrkKdxy",&KpiTrkKdxy);
//tree1->Branch("KpiTrkpidxy",&KpiTrkpidxy);
//tree1->Branch("KpiTrkSdxy",&KpiTrkSdxy);
//tree1->Branch("KpiTrkSdxyErr",&KpiTrkSdxyErr);
//tree1->Branch("KpiTrkKdz",&KpiTrkKdz);
//tree1->Branch("KpiTrkpidz",&KpiTrkpidz);
//tree1->Branch("KpiTrkSdz",&KpiTrkSdz);
//tree1->Branch("KpiTrkSdzErr",&KpiTrkSdzErr);
//tree1->Branch("KpiTrkKeta",&KpiTrkKeta);
//tree1->Branch("KpiTrkpieta",&KpiTrkpieta);
//tree1->Branch("KpiTrkSeta",&KpiTrkSeta);
//tree1->Branch("KpiTrkKphi",&KpiTrkKphi);
//tree1->Branch("KpiTrkpiphi",&KpiTrkpiphi);
//tree1->Branch("KpiTrkSphi",&KpiTrkSphi);
//tree1->Branch("KpiTrkScharge",&KpiTrkScharge);
//MC
//tree1->Branch("MCLambdaDeltaR",&MCLambdaDeltaR);

//Gen quantities
tree1->Branch("GenLambdaVtxPosx",&GenLambdaVtxPosx);
tree1->Branch("GenLambdaVtxPosy",&GenLambdaVtxPosy);
tree1->Branch("GenLambdaVtxPosz",&GenLambdaVtxPosz);
tree1->Branch("GenLambdaSourceVtxPosx",&GenLambdaSourceVtxPosx);
tree1->Branch("GenLambdaSourceVtxPosy",&GenLambdaSourceVtxPosy);
tree1->Branch("GenLambdaSourceVtxPosz",&GenLambdaSourceVtxPosz);
tree1->Branch("GenLambdaPt",&GenLambdaPt);
tree1->Branch("GenLambdaP",&GenLambdaP);
tree1->Branch("GenLambdaPhi",&GenLambdaPhi);
tree1->Branch("GenLambdaEta",&GenLambdaEta);
tree1->Branch("GenLambdaMass",&GenLambdaMass);
tree1->Branch("GenLambdaMt",&GenLambdaMt);
tree1->Branch("GenLambdaE",&GenLambdaE);
tree1->Branch("GenLambdaPx",&GenLambdaPx);
tree1->Branch("GenLambdaPy",&GenLambdaPy);
tree1->Branch("GenLambdaPz",&GenLambdaPz);
tree1->Branch("GenFlightLength",&GenFlightLength);
tree1->Branch("GenDeltaR",&GenDeltaR);
tree1->Branch("GenVertexMatch",&GenVertexMatch);




}

// ------------ method called once each job just after ending the event loop  ------------
void 
LambdaAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(LambdaAnalyzer);
