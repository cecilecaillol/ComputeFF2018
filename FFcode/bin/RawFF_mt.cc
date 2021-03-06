#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "ComputeFF2018/FFcode/interface/ScaleFactor.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "ComputeFF2018/FFcode/interface/myHelper.h"
#include "ComputeFF2018/FFcode/interface/mt_Tree.h"
#include "ComputeFF2018/FFcode/interface/LumiReweightingStandAlone.h"
#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeFF2018/FFcode/interface/SFtautrigger.h"
#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h"

using namespace std;

int main(int argc, char** argv) {

  int do_control_plots=0;

  std::string input = *(argv + 1);
  std::string output = *(argv + 2);
  std::string sample = *(argv + 3);
  std::string name = *(argv + 4);
  std::string year = *(argv+5);

  TFile *f_Double = new TFile(input.c_str());
  cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
  TTree *arbre = (TTree*) f_Double->Get("mutau_tree");
  TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
  float ngen = nbevt->GetBinContent(2);

  float xs=1.0; float weight=1.0; float luminosity=59740.0;
  if(year=="2017") luminosity=41529.0;
  if(year=="2016") luminosity=35922.0;
  if (sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
  if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
  else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
  else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
  else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
  else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
  else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
  else if (sample=="data_obs"){weight=1.0;}
  else if (sample=="embedded"){weight=1.0;}
  else if (sample=="WZ1L1Nu2Q") {xs=11.66; weight=luminosity*xs/ngen;}
  else if (sample=="WZ1L3Nu") {xs=3.293; weight=luminosity*xs/ngen;}
  else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
  else if (sample=="WZ3LNu") {xs=5.052; weight=luminosity*xs/ngen;}
  else if (sample=="WZ2L2Q") {xs=6.331; weight=luminosity*xs/ngen;}
  else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
  else if (sample=="ZZ4L") {xs=1.325; weight=luminosity*xs/ngen;}
  else if (sample=="VV2L2Nu") {xs=13.97; weight=luminosity*xs/ngen;}
  else if (sample=="WW2L2Nu") {xs=11.08; weight=luminosity*xs/ngen;}
  else if (sample=="ZZ2L2Nu") {xs=0.6008; weight=luminosity*xs/ngen;}
  else if (sample=="ZZ2L2Q") {xs=3.688; weight=luminosity*xs/ngen;}
  else if (sample=="WW4Q") {xs=47.73; weight=luminosity*xs/ngen;}
  else if (sample=="WWLNuQQ") {xs=45.99; weight=luminosity*xs/ngen;}
  else if (sample=="ST_tW_antitop") {xs=35.85; weight=luminosity*xs/ngen;}
  else if (sample=="ST_tW_top") {xs=35.85; weight=luminosity*xs/ngen;}
  else if (sample=="ST_t_antitop") {xs=26.23; weight=luminosity*xs/ngen;}
  else if (sample=="ST_t_top") {xs=44.07; weight=luminosity*xs/ngen;}
  else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
  else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
  else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
  else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
  else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
  else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
  else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
  else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
  else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
  else if (sample=="WGstarMuMu") {xs=2.793; weight=luminosity*xs/ngen;}
  else if (sample=="WGstarEE") {xs=3.526; weight=luminosity*xs/ngen;}
  else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
  else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
  else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=4.321; weight=luminosity*xs/ngen;}
  else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.66; weight=luminosity*xs/ngen;}

  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(10);

  arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
  arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
  arbre->SetBranchAddress("Rivet_stage0_cat", &Rivet_stage0_cat);
  arbre->SetBranchAddress("Rivet_stage1p1_cat", &Rivet_stage1p1_cat);
  arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);
    
  arbre->SetBranchAddress("passMu24", &passMu24);
  arbre->SetBranchAddress("passMu27", &passMu27);
  arbre->SetBranchAddress("passMu20Tau27", &passMu20Tau27);
  arbre->SetBranchAddress("passMu20HPSTau27", &passMu20HPSTau27);
  arbre->SetBranchAddress("matchMu24_1", &matchMu24_1); 
  arbre->SetBranchAddress("matchMu27_1", &matchMu27_1);
  arbre->SetBranchAddress("matchMu20Tau27_1", &matchMu20Tau27_1);
  arbre->SetBranchAddress("matchMu20Tau27_2", &matchMu20Tau27_2);
  arbre->SetBranchAddress("matchMu20HPSTau27_1",&matchMu20HPSTau27_1);
  arbre->SetBranchAddress("matchMu20HPSTau27_2", &matchMu20HPSTau27_2);
  //2016 triggers
  arbre->SetBranchAddress("passMu22eta2p1",&passMu22eta2p1);
  arbre->SetBranchAddress("matchMu22eta2p1_1",&matchMu22eta2p1_1);
  arbre->SetBranchAddress("filterMu22eta2p1_1",&filterMu22eta2p1_1);
  arbre->SetBranchAddress("passTkMu22eta2p1",&passTkMu22eta2p1);
  arbre->SetBranchAddress("matchTkMu22eta2p1_1",&matchTkMu22eta2p1_1);
  arbre->SetBranchAddress("filterTkMu22eta2p1_1",&filterTkMu22eta2p1_1);    

  arbre->SetBranchAddress("passMu19Tau20",&passMu19Tau20);
  arbre->SetBranchAddress("matchMu19Tau20_1",&matchMu19Tau20_1);
  arbre->SetBranchAddress("matchMu19Tau20_2",&matchMu19Tau20_2);
  arbre->SetBranchAddress("filterMu19Tau20_1",&filterMu19Tau20_1);
  arbre->SetBranchAddress("filterMu19Tau20_2",&filterMu19Tau20_2);
  arbre->SetBranchAddress("passMu19Tau20SingleL1",&passMu19Tau20SingleL1);
  arbre->SetBranchAddress("matchMu19Tau20SingleL1_1",&matchMu19Tau20SingleL1_1);
  arbre->SetBranchAddress("matchMu19Tau20SingleL1_2",&matchMu19Tau20SingleL1_2);
  arbre->SetBranchAddress("filterMu19Tau20SingleL1_1",&filterMu19Tau20SingleL1_1);
  arbre->SetBranchAddress("filterMu19Tau20SingleL1_2",&filterMu19Tau20SingleL1_2);
    
  /*
    arbre->SetBranchAddress("matchEmbFilter_Mu20Tau27_1", &matchEmbFilter_Mu20Tau27_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu24_1",&matchEmbFilter_Mu24_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu27_1",&matchEmbFilter_Mu27_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
    arbre->SetBranchAddress("matchEmbFilter_Mu20HPSTau27_2", &matchEmbFilter_Mu20HPSTau27_2);
  */
    
  arbre->SetBranchAddress("filterMu24_1", &filterMu24_1);
  arbre->SetBranchAddress("filterMu27_1", &filterMu27_1);
  arbre->SetBranchAddress("filterMu20Tau27_1", &filterMu20Tau27_1);
  arbre->SetBranchAddress("filterMu20Tau27_2", &filterMu20Tau27_2);
  arbre->SetBranchAddress("filterMu20HPSTau27_1", &filterMu20HPSTau27_1);
  arbre->SetBranchAddress("filterMu20HPSTau27_2", &filterMu20HPSTau27_2);

  arbre->SetBranchAddress("run", &run);
  arbre->SetBranchAddress("lumi", &lumi);
  arbre->SetBranchAddress("evt", &evt);
  arbre->SetBranchAddress("npv", &npv);
  arbre->SetBranchAddress("pt_1", &pt_1);
  arbre->SetBranchAddress("phi_1", &phi_1);
  arbre->SetBranchAddress("eta_1", &eta_1);
  arbre->SetBranchAddress("iso_1", &iso_1);
  //arbre->SetBranchAddress("isoDB_1", &isoDB_1);
  arbre->SetBranchAddress("m_1", &m_1);
  arbre->SetBranchAddress("q_1", &q_1);
  arbre->SetBranchAddress("nbtag", &nbtag);
  arbre->SetBranchAddress("nbtagL", &nbtagL);
  arbre->SetBranchAddress("bweight", &bweight);
  arbre->SetBranchAddress("prefiring_weight", &prefiring_weight);
  arbre->SetBranchAddress("q_2", &q_2);
  arbre->SetBranchAddress("pt_2", &pt_2);
  arbre->SetBranchAddress("eta_2", &eta_2);
  arbre->SetBranchAddress("m_2", &m_2);
  arbre->SetBranchAddress("phi_2", &phi_2);
  arbre->SetBranchAddress("met", &met);
  arbre->SetBranchAddress("m_sv", &m_sv);
  /*
    arbre->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    arbre->SetBranchAddress("m_sv_UP", &m_sv_UP);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
  */
  arbre->SetBranchAddress("met", &met);
  arbre->SetBranchAddress("metphi", &metphi);
  arbre->SetBranchAddress("met_UESUp", &met_UESUp);
  arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
  arbre->SetBranchAddress("met_UESDown", &met_UESDown);
  arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
  arbre->SetBranchAddress("met_responseUp", &met_responseUp);
  arbre->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
  arbre->SetBranchAddress("met_responseDown", &met_responseDown);
  arbre->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
  arbre->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
  arbre->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
  arbre->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
  arbre->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
  arbre->SetBranchAddress("metphi_JetEta0to3Down", &metphi_JetEta0to3Down);
  arbre->SetBranchAddress("met_JetEta0to3Down", &met_JetEta0to3Down);
  arbre->SetBranchAddress("metphi_JetEta0to3Up", &metphi_JetEta0to3Up);
  arbre->SetBranchAddress("met_JetEta0to3Up", &met_JetEta0to3Up);
  arbre->SetBranchAddress("metphi_JetEta0to5Down", &metphi_JetEta0to5Down);
  arbre->SetBranchAddress("met_JetEta0to5Down", &met_JetEta0to5Down);
  arbre->SetBranchAddress("metphi_JetEta0to5Up", &metphi_JetEta0to5Up);
  arbre->SetBranchAddress("met_JetEta0to5Up", &met_JetEta0to5Up);
  arbre->SetBranchAddress("metphi_JetEta3to5Down", &metphi_JetEta3to5Down);
  arbre->SetBranchAddress("met_JetEta3to5Down", &met_JetEta3to5Down);
  arbre->SetBranchAddress("metphi_JetEta3to5Up", &metphi_JetEta3to5Up);
  arbre->SetBranchAddress("met_JetEta3to5Up", &met_JetEta3to5Up);
  arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
  arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
  arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
  arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
  arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
  arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
  arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
  arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
  arbre->SetBranchAddress("metphi_JetEC2Down", &metphi_JetEC2Down);
  arbre->SetBranchAddress("met_JetEC2Down", &met_JetEC2Down);
  arbre->SetBranchAddress("metphi_JetEC2Up", &metphi_JetEC2Up);
  arbre->SetBranchAddress("met_JetEC2Up", &met_JetEC2Up);
  arbre->SetBranchAddress("njets_JetEC2Down", &njets_JetEC2Down);
  arbre->SetBranchAddress("njets_JetEC2Up", &njets_JetEC2Up);
  arbre->SetBranchAddress("mjj_JetEC2Down", &mjj_JetEC2Down);
  arbre->SetBranchAddress("mjj_JetEC2Up", &mjj_JetEC2Up);
  /*
    arbre->SetBranchAddress("pt_1_SigmaUp", &pt_1_SigmaUp);
    arbre->SetBranchAddress("pt_1_SigmaDown", &pt_1_SigmaDown);
    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);
  */
  /*
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("m_sv_JetEta3to5Up", &m_sv_JetEta3to5Up);
    arbre->SetBranchAddress("m_sv_JetEta3to5Down", &m_sv_JetEta3to5Down);
    arbre->SetBranchAddress("m_sv_JetEta0to3Up", &m_sv_JetEta0to3Up);
    arbre->SetBranchAddress("m_sv_JetEta0to3Down", &m_sv_JetEta0to3Down);
    arbre->SetBranchAddress("m_sv_JetEta0to5Up", &m_sv_JetEta0to5Up);
    arbre->SetBranchAddress("m_sv_JetEta0to5Down", &m_sv_JetEta0to5Down);
    arbre->SetBranchAddress("m_sv_JetEC2Up", &m_sv_JetEC2Up);
    arbre->SetBranchAddress("m_sv_JetEC2Down", &m_sv_JetEC2Down);
  */
  /*
    arbre->SetBranchAddress("m_sv_ESMEARUP", &m_sv_ESMEARUP);
    arbre->SetBranchAddress("m_sv_ESMEARDOWN", &m_sv_ESMEARDOWN);
    arbre->SetBranchAddress("m_sv_ESCALEUP", &m_sv_ESCALEUP);
    arbre->SetBranchAddress("m_sv_ESCALEDOWN", &m_sv_ESCALEDOWN);
  */
  arbre->SetBranchAddress("njets", &njets);
  arbre->SetBranchAddress("njets_JetEta0to3Down", &njets_JetEta0to3Down);
  arbre->SetBranchAddress("njets_JetEta0to3Up", &njets_JetEta0to3Up);
  arbre->SetBranchAddress("njets_JetRelativeSampleDown", &njets_JetRelativeSampleDown);
  arbre->SetBranchAddress("njets_JetRelativeSampleUp", &njets_JetRelativeSampleUp);
  arbre->SetBranchAddress("njets_JetRelativeBalDown", &njets_JetRelativeBalDown);
  arbre->SetBranchAddress("njets_JetRelativeBalUp", &njets_JetRelativeBalUp);
  arbre->SetBranchAddress("njets_JetEta0to5Down", &njets_JetEta0to5Down);
  arbre->SetBranchAddress("njets_JetEta0to5Up", &njets_JetEta0to5Up);
  arbre->SetBranchAddress("njets_JetEta3to5Down", &njets_JetEta3to5Down);
  arbre->SetBranchAddress("njets_JetEta3to5Up", &njets_JetEta3to5Up);
  arbre->SetBranchAddress("jpt_1", &jpt_1);
  arbre->SetBranchAddress("jeta_1", &jeta_1);
  arbre->SetBranchAddress("jphi_1", &jphi_1);
  arbre->SetBranchAddress("jpt_2", &jpt_2);
  arbre->SetBranchAddress("jeta_2", &jeta_2);
  arbre->SetBranchAddress("jphi_2", &jphi_2);
  arbre->SetBranchAddress("bpt_1", &bpt_1);
  arbre->SetBranchAddress("beta_1", &beta_1);
  arbre->SetBranchAddress("bphi_1", &bphi_1);
  arbre->SetBranchAddress("bpt_2", &bpt_2);
  arbre->SetBranchAddress("beta_2", &beta_2);
  arbre->SetBranchAddress("bphi_2", &bphi_2);
  arbre->SetBranchAddress("bflavor_1", &bflavor_1);
  arbre->SetBranchAddress("bflavor_2", &bflavor_2);
  arbre->SetBranchAddress("mjj", &mjj);
  arbre->SetBranchAddress("mjj_JetEta0to3Down", &mjj_JetEta0to3Down);
  arbre->SetBranchAddress("mjj_JetEta0to3Up", &mjj_JetEta0to3Up);
  arbre->SetBranchAddress("mjj_JetEta3to5Down", &mjj_JetEta3to5Down);
  arbre->SetBranchAddress("mjj_JetEta3to5Up", &mjj_JetEta3to5Up);
  arbre->SetBranchAddress("mjj_JetEta0to5Down", &mjj_JetEta0to5Down);
  arbre->SetBranchAddress("mjj_JetEta0to5Up", &mjj_JetEta0to5Up);
  arbre->SetBranchAddress("mjj_JetRelativeBalDown", &mjj_JetRelativeBalDown);
  arbre->SetBranchAddress("mjj_JetRelativeBalUp", &mjj_JetRelativeBalUp);
  arbre->SetBranchAddress("mjj_JetRelativeSampleDown", &mjj_JetRelativeSampleDown);
  arbre->SetBranchAddress("mjj_JetRelativeSampleUp", &mjj_JetRelativeSampleUp);
  arbre->SetBranchAddress("genweight", &genweight);
  arbre->SetBranchAddress("byVLooseIsolationMVArun2v2DBoldDMwLT_2",&byVLooseIsolationMVArun2v2DBoldDMwLT_2);
  arbre->SetBranchAddress("byLooseIsolationMVArun2v2DBoldDMwLT_2",&byLooseIsolationMVArun2v2DBoldDMwLT_2);
  arbre->SetBranchAddress("byMediumIsolationMVArun2v2DBoldDMwLT_2",&byMediumIsolationMVArun2v2DBoldDMwLT_2);
  arbre->SetBranchAddress("byTightIsolationMVArun2v2DBoldDMwLT_2",&byTightIsolationMVArun2v2DBoldDMwLT_2);
  arbre->SetBranchAddress("byVTightIsolationMVArun2v2DBoldDMwLT_2",&byVTightIsolationMVArun2v2DBoldDMwLT_2);

  arbre->SetBranchAddress("byVVVLooseDeepVSjet_2",&byVVVLooseDeepVSjet_2);
  arbre->SetBranchAddress("byVVLooseDeepVSjet_2",&byVVLooseDeepVSjet_2);
  arbre->SetBranchAddress("byVLooseDeepVSjet_2",&byVLooseDeepVSjet_2);
  arbre->SetBranchAddress("byLooseDeepVSjet_2",&byLooseDeepVSjet_2);
  arbre->SetBranchAddress("byMediumDeepVSjet_2",&byMediumDeepVSjet_2);
  arbre->SetBranchAddress("byTightDeepVSjet_2",&byTightDeepVSjet_2);
  arbre->SetBranchAddress("byVTightDeepVSjet_2",&byVTightDeepVSjet_2);
  arbre->SetBranchAddress("byVVVLooseDeepVSmu_2",&byVVVLooseDeepVSmu_2);
  arbre->SetBranchAddress("byVVLooseDeepVSmu_2",&byVVLooseDeepVSmu_2);
  arbre->SetBranchAddress("byVLooseDeepVSmu_2",&byVLooseDeepVSmu_2);
  arbre->SetBranchAddress("byLooseDeepVSmu_2",&byLooseDeepVSmu_2);
  arbre->SetBranchAddress("byMediumDeepVSmu_2",&byMediumDeepVSmu_2);
  arbre->SetBranchAddress("byTightDeepVSmu_2",&byTightDeepVSmu_2);
  arbre->SetBranchAddress("byVTightDeepVSmu_2",&byVTightDeepVSmu_2);
  arbre->SetBranchAddress("byVVVLooseDeepVSe_2",&byVVVLooseDeepVSe_2);
  arbre->SetBranchAddress("byVVLooseDeepVSe_2",&byVVLooseDeepVSe_2);
  arbre->SetBranchAddress("byVLooseDeepVSe_2",&byVLooseDeepVSe_2);
  arbre->SetBranchAddress("byLooseDeepVSe_2",&byLooseDeepVSe_2);
  arbre->SetBranchAddress("byMediumDeepVSe_2",&byMediumDeepVSe_2);
  arbre->SetBranchAddress("byTightDeepVSe_2",&byTightDeepVSe_2);
  arbre->SetBranchAddress("byVTightDeepVSe_2",&byVTightDeepVSe_2);

  arbre->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2",&byIsolationMVA3oldDMwLTraw_2);
  arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
  arbre->SetBranchAddress("againstElectronTightMVA6_2",&againstElectronTightMVA6_2);
  arbre->SetBranchAddress("againstElectronVTightMVA6_2",&againstElectronVTightMVA6_2);
  arbre->SetBranchAddress("againstElectronTightMVA62018_2",&againstElectronTightMVA62018_2);
  arbre->SetBranchAddress("againstElectronVTightMVA62018_2",&againstElectronVTightMVA62018_2);
  arbre->SetBranchAddress("againstMuonLoose3_2",&againstMuonLoose3_2);
  arbre->SetBranchAddress("gen_match_1",&gen_match_1);
  arbre->SetBranchAddress("gen_match_2",&gen_match_2);
  arbre->SetBranchAddress("npu",&npu);
  arbre->SetBranchAddress("genpT",&genpT);
  arbre->SetBranchAddress("genM",&genM);
  arbre->SetBranchAddress("pt_top1",&pt_top1);
  arbre->SetBranchAddress("pt_top2",&pt_top2);
  arbre->SetBranchAddress("numGenJets",&numGenJets);
  arbre->SetBranchAddress("Flag_BadChargedCandidateFilter",&Flag_BadChargedCandidateFilter);
  arbre->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter);
  arbre->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",&Flag_EcalDeadCellTriggerPrimitiveFilter);
  arbre->SetBranchAddress("Flag_HBHENoiseFilter",&Flag_HBHENoiseFilter);
  arbre->SetBranchAddress("Flag_HBHENoiseIsoFilter",&Flag_HBHENoiseIsoFilter);
  arbre->SetBranchAddress("Flag_eeBadScFilter",&Flag_eeBadScFilter);
  arbre->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices);
  arbre->SetBranchAddress("Flag_globalSuperTightHalo2016Filter",&Flag_globalSuperTightHalo2016Filter);
  arbre->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter);
  arbre->SetBranchAddress("Flag_duplicateMuons",&Flag_duplicateMuons);
  arbre->SetBranchAddress("Flag_badMuons",&Flag_badMuons);
  arbre->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter);

  int nbhist=1;

  float bins_mtt0[] = {30,35,40,45,50,55,60,70,80,100};
  int  binnum_mtt0 = sizeof(bins_mtt0)/sizeof(Float_t) - 1;

  TH1F* h0LT_qcd_iso = new TH1F ("h0LT_qcd_iso","h0LT_qcd_iso",binnum_mtt0,bins_mtt0); h0LT_qcd_iso->Sumw2();
  TH1F* h1LT_qcd_iso = new TH1F ("h1LT_qcd_iso","h1LT_qcd_iso",binnum_mtt0,bins_mtt0); h1LT_qcd_iso->Sumw2();
  TH1F* h2LT_qcd_iso = new TH1F ("h2LT_qcd_iso","h2LT_qcd_iso",binnum_mtt0,bins_mtt0); h2LT_qcd_iso->Sumw2();
  TH1F* h0LT_qcd_anti = new TH1F ("h0LT_qcd_anti","h0LT_qcd_anti",binnum_mtt0,bins_mtt0); h0LT_qcd_anti->Sumw2();
  TH1F* h1LT_qcd_anti = new TH1F ("h1LT_qcd_anti","h1LT_qcd_anti",binnum_mtt0,bins_mtt0); h1LT_qcd_anti->Sumw2();
  TH1F* h2LT_qcd_anti = new TH1F ("h2LT_qcd_anti","h2LT_qcd_anti",binnum_mtt0,bins_mtt0); h2LT_qcd_anti->Sumw2();
  TH1F* h0LT_w_iso = new TH1F ("h0LT_w_iso","h0LT_w_iso",binnum_mtt0,bins_mtt0); h0LT_w_iso->Sumw2();
  TH1F* h1LT_w_iso = new TH1F ("h1LT_w_iso","h1LT_w_iso",binnum_mtt0,bins_mtt0); h1LT_w_iso->Sumw2();
  TH1F* h2LT_w_iso = new TH1F ("h2LT_w_iso","h2LT_w_iso",binnum_mtt0,bins_mtt0); h2LT_w_iso->Sumw2();
  TH1F* h0LT_w_anti = new TH1F ("h0LT_w_anti","h0LT_w_anti",binnum_mtt0,bins_mtt0); h0LT_w_anti->Sumw2();
  TH1F* h1LT_w_anti = new TH1F ("h1LT_w_anti","h1LT_w_anti",binnum_mtt0,bins_mtt0); h1LT_w_anti->Sumw2();
  TH1F* h2LT_w_anti = new TH1F ("h2LT_w_anti","h2LT_w_anti",binnum_mtt0,bins_mtt0); h2LT_w_anti->Sumw2();
  TH1F* h0LT_tt_iso = new TH1F ("h0LT_tt_iso","h0LT_tt_iso",binnum_mtt0,bins_mtt0); h0LT_tt_iso->Sumw2();
  TH1F* h0LT_tt_anti = new TH1F ("h0LT_tt_anti","h0LT_tt_anti",binnum_mtt0,bins_mtt0); h0LT_tt_anti->Sumw2();

  TH1F* h0J_qcd_iso = new TH1F ("h0J_qcd_iso","h0J_qcd_iso",binnum_mtt0,bins_mtt0); h0J_qcd_iso->Sumw2();
  TH1F* h1J_qcd_iso = new TH1F ("h1J_qcd_iso","h1J_qcd_iso",binnum_mtt0,bins_mtt0); h1J_qcd_iso->Sumw2();
  TH1F* h2J_qcd_iso = new TH1F ("h2J_qcd_iso","h2J_qcd_iso",binnum_mtt0,bins_mtt0); h2J_qcd_iso->Sumw2();
  TH1F* h0J_qcd_anti = new TH1F ("h0J_qcd_anti","h0J_qcd_anti",binnum_mtt0,bins_mtt0); h0J_qcd_anti->Sumw2();
  TH1F* h1J_qcd_anti = new TH1F ("h1J_qcd_anti","h1J_qcd_anti",binnum_mtt0,bins_mtt0); h1J_qcd_anti->Sumw2();
  TH1F* h2J_qcd_anti = new TH1F ("h2J_qcd_anti","h2J_qcd_anti",binnum_mtt0,bins_mtt0); h2J_qcd_anti->Sumw2();
  TH1F* h0J_w_iso = new TH1F ("h0J_w_iso","h0J_w_iso",binnum_mtt0,bins_mtt0); h0J_w_iso->Sumw2();
  TH1F* h1J_w_iso = new TH1F ("h1J_w_iso","h1J_w_iso",binnum_mtt0,bins_mtt0); h1J_w_iso->Sumw2();
  TH1F* h2J_w_iso = new TH1F ("h2J_w_iso","h2J_w_iso",binnum_mtt0,bins_mtt0); h2J_w_iso->Sumw2();
  TH1F* h0J_w_anti = new TH1F ("h0J_w_anti","h0J_w_anti",binnum_mtt0,bins_mtt0); h0J_w_anti->Sumw2();
  TH1F* h1J_w_anti = new TH1F ("h1J_w_anti","h1J_w_anti",binnum_mtt0,bins_mtt0); h1J_w_anti->Sumw2();
  TH1F* h2J_w_anti = new TH1F ("h2J_w_anti","h2J_w_anti",binnum_mtt0,bins_mtt0); h2J_w_anti->Sumw2();
  TH1F* h0J_tt_iso = new TH1F ("h0J_tt_iso","h0J_tt_iso",binnum_mtt0,bins_mtt0); h0J_tt_iso->Sumw2();
  TH1F* h0J_tt_anti = new TH1F ("h0J_tt_anti","h0J_tt_anti",binnum_mtt0,bins_mtt0); h0J_tt_anti->Sumw2();

  TH1F* h0SSlooseLT_qcd_iso = new TH1F ("h0SSlooseLT_qcd_iso","h0SSlooseLT_qcd_iso",binnum_mtt0,bins_mtt0); h0SSlooseLT_qcd_iso->Sumw2();
  TH1F* h0SSlooseLT_qcd_anti = new TH1F ("h0SSlooseLT_qcd_anti","h0SSlooseLT_qcd_anti",binnum_mtt0,bins_mtt0); h0SSlooseLT_qcd_anti->Sumw2();
  TH1F* h0SSlooseJ_qcd_iso = new TH1F ("h0SSlooseJ_qcd_iso","h0SSlooseJ_qcd_iso",binnum_mtt0,bins_mtt0); h0SSlooseJ_qcd_iso->Sumw2();
  TH1F* h0SSlooseJ_qcd_anti = new TH1F ("h0SSlooseJ_qcd_anti","h0SSlooseJ_qcd_anti",binnum_mtt0,bins_mtt0); h0SSlooseJ_qcd_anti->Sumw2();
  TH1F* h1SSlooseLT_qcd_iso = new TH1F ("h1SSlooseLT_qcd_iso","h1SSlooseLT_qcd_iso",binnum_mtt0,bins_mtt0); h1SSlooseLT_qcd_iso->Sumw2();
  TH1F* h1SSlooseLT_qcd_anti = new TH1F ("h1SSlooseLT_qcd_anti","h1SSlooseLT_qcd_anti",binnum_mtt0,bins_mtt0); h1SSlooseLT_qcd_anti->Sumw2();
  TH1F* h1SSlooseJ_qcd_iso = new TH1F ("h1SSlooseJ_qcd_iso","h1SSlooseJ_qcd_iso",binnum_mtt0,bins_mtt0); h1SSlooseJ_qcd_iso->Sumw2();
  TH1F* h1SSlooseJ_qcd_anti = new TH1F ("h1SSlooseJ_qcd_anti","h1SSlooseJ_qcd_anti",binnum_mtt0,bins_mtt0); h1SSlooseJ_qcd_anti->Sumw2();
  TH1F* h2SSlooseLT_qcd_iso = new TH1F ("h2SSlooseLT_qcd_iso","h2SSlooseLT_qcd_iso",binnum_mtt0,bins_mtt0); h2SSlooseLT_qcd_iso->Sumw2();
  TH1F* h2SSlooseLT_qcd_anti = new TH1F ("h2SSlooseLT_qcd_anti","h2SSlooseLT_qcd_anti",binnum_mtt0,bins_mtt0); h2SSlooseLT_qcd_anti->Sumw2();
  TH1F* h2SSlooseJ_qcd_iso = new TH1F ("h2SSlooseJ_qcd_iso","h2SSlooseJ_qcd_iso",binnum_mtt0,bins_mtt0); h2SSlooseJ_qcd_iso->Sumw2();
  TH1F* h2SSlooseJ_qcd_anti = new TH1F ("h2SSlooseJ_qcd_anti","h2SSlooseJ_qcd_anti",binnum_mtt0,bins_mtt0); h2SSlooseJ_qcd_anti->Sumw2();

  string datapath = string(std::getenv("CMSSW_BASE"))+"/src/ComputeFF2018/FFcode/data/";

  reweight::LumiReWeighting* LumiWeights_12;
  LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2018.root").c_str(), (datapath+"pu_distributions_data_2018.root").c_str(), "pileup", "pileup"); //First parameter hard coded to data disk. Non-portable
   if (year=="2016")
     {     
       LumiWeights_12 = new reweight::LumiReWeighting((datapath+"MC_Moriond17_PU25ns_V1.root").c_str(), (datapath+"Data_Pileup_2016_271036-284044_80bins.root").c_str(), "pileup", "pileup");
     }
   else if (year=="2017")
     {
       LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       if (sample=="W1") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
       else if (sample=="W2") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5#MINIAODSIM", "pileup");
       else if (sample=="ST_t_antitop") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
       else if (sample=="W") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
       else if (sample=="DY") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="WW") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="WZ") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="ST_tW_top") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
       else if (sample=="WminusH125") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="ST_tW_antitop") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
       else if (sample=="W3") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
       else if (sample=="ZH125") LumiWeights_12 = new reweight::LumiReWeighting((datapath+"pu_distributions_mc_2017.root").c_str(), (datapath+"pu_distributions_data_2017.root").c_str(), "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
     }

   TFile fw((datapath+"htt_scalefactors_v18_2.root").c_str());
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc((datapath+"htt_scalefactors_legacy_2018.root").c_str());
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();
   if(year == "2017")
     {
       TFile fwmc((datapath+"htt_scalefactors_legacy_2017.root").c_str());
       wmc = (RooWorkspace*)fwmc.Get("w");
       fwmc.Close();
     }
   if(year == "2016")
     {
       TFile fwmc((datapath+"htt_scalefactors_legacy_2016.root").c_str());
       wmc = (RooWorkspace*)fwmc.Get("w");
       fwmc.Close();
     }

   TFile frawff("uncorrected_fakefactors_mt.root");
   TF1* ff_qcd_0jet=(TF1*) frawff.Get("rawFF_mt_qcd_0jetSSloose");
   TF1* ff_qcd_1jet=(TF1*) frawff.Get("rawFF_mt_qcd_1jetSSloose");

   TFile fmvisclosure ("FF_corrections_1.root");
   TF1* mvisclosure_qcdloose=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcdloose");

   ScaleFactor * myScaleFactor_trgMu2427 = new ScaleFactor();
   myScaleFactor_trgMu2427->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IsoMu24orIsoMu27.root");
     //myScaleFactor_trgMu2427->init_ScaleFactor("../LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IsoMu24orIsoMu27.root");
   ScaleFactor * myScaleFactor_trgMu20 = new ScaleFactor();
   myScaleFactor_trgMu20->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IsoMu20.root");
   ScaleFactor * myScaleFactor_IdIso = new ScaleFactor();
   myScaleFactor_IdIso->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IdIso.root");

   if (year=="2017")
     {
       myScaleFactor_trgMu2427->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2017/Muon_IsoMu24orIsoMu27.root");
       myScaleFactor_trgMu20->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2017/Muon_MuTau_IsoMu20.root");
       myScaleFactor_IdIso->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2017/Muon_IdIso_IsoLt0.15_eff_RerecoFall17.root");
     }

   TauTriggerSFs2017* mtsf=new TauTriggerSFs2017(string(std::getenv("CMSSW_BASE"))+"/src/TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2018.root","mutau", "2018", "tight", "MVAv2");
   if (year=="2017") mtsf = new TauTriggerSFs2017(string(std::getenv("CMSSW_BASE"))+"/src/TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2017.root","mutau", "2017", "tight", "MVAv2");
   if (year=="2016") mtsf = new TauTriggerSFs2017(string(std::getenv("CMSSW_BASE"))+"/src/TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2016.root","mutau", "2016", "tight", "MVAv2");

   TFile *fZ = new TFile((datapath+"zpt_weights_2016_BtoH.root").c_str());
   TH2F *histZ = (TH2F*) fZ->Get("zptmass_histo");
   ScaleFactor * myScaleFactor_trgMu22 = new ScaleFactor();
   ScaleFactor * myScaleFactor_trgMu19 = new ScaleFactor();
   myScaleFactor_trgMu22->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu22OR_eta2p1_eff.root");
   myScaleFactor_trgMu19->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu19leg_2016BtoH_eff.root");
   if(year=="2016") myScaleFactor_IdIso->init_ScaleFactor(string(std::getenv("CMSSW_BASE"))+"/src/LeptonEfficiencies/Muon/Run2016BtoH/Muon_IdIso_IsoLt0p15_2016BtoH_eff.root");

   TauIDSFTool * theSFTool;
   if (year == "2016") theSFTool = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSjet","Medium");
   else if (year == "2017") theSFTool = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSjet","Medium");
   else theSFTool = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSjet", "Medium");   

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.3) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;

        bool trigger24=(passMu24 && pt_1>25 && matchMu24_1 && filterMu24_1);
	bool trigger27=(passMu27 && pt_1>25 && matchMu27_1 && filterMu27_1);
	bool trigger2027=(passMu20Tau27 && matchMu20Tau27_1 && matchMu20Tau27_2 && pt_1 > 21 && pt_1 < 25 && pt_2 > 32 && fabs(eta_1) < 2.1 && fabs(eta_2) < 2.1 && filterMu20Tau27_1 && filterMu20Tau27_2);
	bool trigger2027HPS=(passMu20HPSTau27 && matchMu20HPSTau27_1 && matchMu20HPSTau27_2 && pt_1 > 21 && pt_1 < 25 && pt_2 > 32 && fabs(eta_1) < 2.1 && fabs(eta_2) < 2.1 && filterMu20HPSTau27_1 && filterMu20HPSTau27_2);
	bool trigger22 = false;
	bool trigger19 = false;

        if (year == "2018" && sample=="data_obs" && run<317509 && !trigger2027 && !trigger24 && !trigger27) continue;
        if (year == "2018" && sample=="data_obs" && run>=317509 && !trigger2027HPS && !trigger24 && !trigger27) continue;
        if (year == "2018" && sample!="data_obs" && !trigger24 && !trigger27 && !trigger2027HPS) continue;

	if(year=="2017")
	  {
	    trigger24=(pt_1 > 25.0 && passMu24 && matchMu24_1 && filterMu24_1);
	    trigger27=(pt_1 > 25.0 && passMu27 && matchMu27_1 && filterMu27_1);
	    trigger2027=(passMu20Tau27 && matchMu20Tau27_1 && matchMu20Tau27_2 && 
			 filterMu20Tau27_1 && filterMu20Tau27_2 && pt_1 > 21.0 && pt_2 > 32.0
			 && pt_1 < 25.0 && fabs(eta_1) < 2.1 && fabs(eta_2)<2.1);
	    if(!trigger24 && !trigger27 && !trigger2027) continue;
	  }
	else if(year=="2016")
	  {
	    trigger22 = (pt_1 > 23.0 && fabs(eta_1) < 2.1 &&
			 ((passMu22eta2p1 && matchMu22eta2p1_1 && filterMu22eta2p1_1) ||
			  (passTkMu22eta2p1 && matchTkMu22eta2p1_1 && filterTkMu22eta2p1_1)));
	    trigger19 = (pt_1 > 20.0 && pt_1 < 23.0 && pt_2 > 25.0 && fabs(eta_2)<2.1 && fabs(eta_1)<2.1 
			 &&((passMu19Tau20 && matchMu19Tau20_1 && matchMu19Tau20_2 && filterMu19Tau20_1 && filterMu19Tau20_2)||
			    (passMu19Tau20SingleL1 && matchMu19Tau20SingleL1_1 && matchMu19Tau20SingleL1_2 && filterMu19Tau20SingleL1_1 && filterMu19Tau20SingleL1_2)));

	    if (!trigger22 && !trigger19) continue;
	  }


	// Change here to change the ID!!
	// MVA Tight
	/*
	if (l2_decayMode!=0 && l2_decayMode!=1 && l2_decayMode!=10) continue;
	if (!againstElectronTightMVA6_2 or !againstMuonLoose3_2) continue;
        float signalRegion=(byTightIsolationMVArun2v2DBoldDMwLT_2);
        float antiisoRegion=(byVLooseIsolationMVArun2v2DBoldDMwLT_2 && !byTightIsolationMVArun2v2DBoldDMwLT_2);
	*/

	// Deep Tight
	/*
	if (!byTightDeepVSe_2 or !byVLooseDeepVSmu_2) continue;
        float signalRegion=(byTightDeepVSjet_2);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byTightDeepVSjet_2);
	*/

	// Deep Medium	
        if (!byVVVLooseDeepVSe_2 or !byTightDeepVSmu_2) continue;
        float signalRegion=(byMediumDeepVSjet_2);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2);
	

	// Deep VTight
	/*
        if (!byTightDeepVSe_2 or !byVLooseDeepVSmu_2) continue;
        float signalRegion=(byVTightDeepVSjet_2);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byVTightDeepVSjet_2);

	// Deep Loose
        if (!byTightDeepVSe_2 or !byVLooseDeepVSmu_2) continue;
        float signalRegion=(byLooseDeepVSjet_2);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byLooseDeepVSjet_2);*/

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

	if (mymu.DeltaR(mytau)<0.5) continue;
	
	if(year == "2018")
	  {
	    if (sample=="W"){
	      weight=51.7495;
	      if (numGenJets==1) weight=9.0816;
	      else if (numGenJets==2) weight=4.5197;
	      else if (numGenJets==3) weight=3.0775;
	      else if (numGenJets==4) weight=3.2113;
	    }

	    if (sample=="DY"){
	      weight=3.6235;
	      if (numGenJets==1) weight=0.62980;
	      else if (numGenJets==2) weight=0.55212;
	      else if (numGenJets==3) weight=0.5995;
	      else if (numGenJets==4) weight=0.8211;
	    }
	  }
	else if (year == "2017")
	  {
	    if(sample=="W")
	      {
		weight = 23.7227;
		if(numGenJets==1) weight = 3.1136;
		else if(numGenJets==2) weight = 3.0206;
		else if(numGenJets==3) weight = 2.2055;
		else if(numGenJets==4) weight = 2.1514;
	      }
	    if(sample=="DY")
	      {
		weight = 2.5805;
		if(numGenJets==1) weight=0.71000;
		else if(numGenJets == 2)weight=0.92113;
		else if(numGenJets == 3)weight=1.6508;
		else if(numGenJets == 4)weight=0.21935;
	      }
	  }
	else if(year == "2016")
	  {
	    if (sample=="W")
	      {
		weight = 25.4286;
		if(numGenJets == 1) weight = 5.7747;
		else if(numGenJets==2) weight = 1.7932;
		else if(numGenJets==3) weight = 0.68005;
		else if(numGenJets==4) weight = 1.85115;
	      }
	    if(sample=="DY")
	      {
		weight = 1.49237;
		if(numGenJets == 1) weight = 0.47595;
		else if(numGenJets == 2) weight = 0.49308;
		else if(numGenJets == 3) weight = 0.51132;
		else if(numGenJets == 4) weight = 0.42527;
	      }
	  }

        bool is_includedInEmbedded=false;
        //if ((name.find("125")>100 && sample!="data_obs" && sample!="embedded") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
        bool isT=(!is_includedInEmbedded && gen_match_2==5);
        bool isL=(!is_includedInEmbedded && gen_match_2<5);

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;
	if (year == "2018" && byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight = aweight*theSFTool->getSFvsPT(pt_2);
	if (year == "2017" && byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*theSFTool->getSFvsPT(pt_2);
	if (year == "2016" && byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*theSFTool->getSFvsPT(pt_2);
	
        if (sample=="embedded") aweight=aweight*0.97;
	//Muon rescaling tight
	/*if (gen_match_2==2 or gen_match_2==4){
	   if (fabs(mytau.Eta())<0.4) aweight=aweight*1.17;
           else if (fabs(mytau.Eta())<0.8) aweight=aweight*1.29;
           else if (fabs(mytau.Eta())<1.2) aweight=aweight*1.14;
           else if (fabs(mytau.Eta())<1.7) aweight=aweight*0.93;
           else if (fabs(mytau.Eta())<2.3) aweight=aweight*1.61;
	}
	//electron rescaling vloose
        if (gen_match_2==1 or gen_match_2==3){
           if (fabs(mytau.Eta())<1.460) aweight=aweight*1.09;
           else if (fabs(mytau.Eta())>1.558) aweight=aweight*1.19;
	}*/

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

	if (sample=="data_obs") aweight=1.0;
	
	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT"){
           float pttop1=pt_top1;
           if (pttop1>400) pttop1=400;
           float pttop2=pt_top2;
           if (pttop2>400) pttop2=400;
           topfactor=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
	if (sample!="embedded" && sample!="data_obs"){
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
	  zptweight=wmc->function("zptmass_weight_nom")->getVal();
	  if (sample=="DY") aweight=aweight*zptweight;
	  aweight=aweight*myScaleFactor_IdIso->get_ScaleFactor(pt_1,eta_1);
          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_1);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();

          int dm=l2_decayMode;
          if(dm>10) dm=10;
	  if (year=="2018" or year=="2017"){
            if (trigger24 or trigger27) aweight=aweight*myScaleFactor_trgMu2427->get_ScaleFactor(pt_1,eta_1);
            else aweight=aweight*myScaleFactor_trgMu20->get_ScaleFactor(pt_1,eta_1)*mtsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm);
	  }
	  if (year=="2016"){
             if (trigger22) aweight=aweight*myScaleFactor_trgMu22->get_ScaleFactor(pt_1,eta_1);
             else if (trigger19) aweight=aweight*(wmc->function("m_trgMu19leg_eta2p1_desy_data")->getVal()/wmc->function("m_trgMu19leg_eta2p1_desy_mc")->getVal())*mtsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm);
	  }

          aweight=aweight*bweight;
	  if (year=="2016" or year=="2017") aweight=aweight*prefiring_weight;
	}
	//TODO Add proper embedded weighting here.

	float mt=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());

	//************************* Fill histograms **********************
           if (mytau.Pt()<30) continue;
	   float weight2=1.0;
	   float myvar=mytau.Pt();

           if (!is_includedInEmbedded){
	     if (isL or isT){
          /*int dm=l2_decayMode;
          if(dm>10) dm=10;
if (trigger19 && signalRegion && njets==0 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0) cout<<aweight<<" "<<(wmc->function("m_trgMu19leg_eta2p1_desy_data")->getVal()/wmc->function("m_trgMu19leg_eta2p1_desy_mc")->getVal())<<" "<<mtsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm)<<endl;*/
	       if (signalRegion && njets==0 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
		  h0LT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0LT_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1LT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1LT_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2LT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2LT_qcd_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets==0 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0SSlooseLT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0SSlooseLT_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1SSlooseLT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1SSlooseLT_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2SSlooseLT_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2SSlooseLT_qcd_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets==0 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h0LT_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h0LT_w_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h1LT_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h1LT_w_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h2LT_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h2LT_w_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets>=0 && iso_1<0.15 && nbtag>0 && mt<50 && q_1*q_2<0)
                  h0LT_tt_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>=0 && iso_1<0.15 && nbtag>0 && mt<50 && q_1*q_2<0)
                  h0LT_tt_anti->Fill(myvar,aweight*weight2);
	    }
	   else{
               if (signalRegion && njets==0 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0J_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0J_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1J_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1J_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2J_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1>0.02 && iso_1<0.15 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2J_qcd_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets==0 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0SSlooseJ_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h0SSlooseJ_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1SSlooseJ_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h1SSlooseJ_qcd_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2SSlooseJ_qcd_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1>0.15 && iso_1<0.25 && nbtag==0 && mt<50 && q_1*q_2>0)
                  h2SSlooseJ_qcd_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets==0 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h0J_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==0 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h0J_w_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets==1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h1J_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets==1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h1J_w_anti->Fill(myvar,aweight*weight2);
               if (signalRegion && njets>1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h2J_w_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>1 && iso_1<0.15 && nbtag==0 && mt>70 && q_1*q_2<0)
                  h2J_w_anti->Fill(myvar,aweight*weight2);

               if (signalRegion && njets>=0 && iso_1<0.15 && nbtag>0 && mt<50 && q_1*q_2<0)
                  h0J_tt_iso->Fill(myvar,aweight*weight2);
               if (antiisoRegion && njets>=0 && iso_1<0.15 && nbtag>0 && mt<50 && q_1*q_2<0)
                  h0J_tt_anti->Fill(myvar,aweight*weight2);
            }

           }

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    TString postfixJ="J";
    TString postfixLT="LT";

    TDirectory *d0_qcd_iso =fout->mkdir("mt_0jet_qcd_iso");
    d0_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h0LT_qcd_iso->SetName(name.c_str());
      h0LT_qcd_iso->Add(h0J_qcd_iso);
      h0LT_qcd_iso->Write();
    }
    else{
      h0LT_qcd_iso->SetName(name.c_str()+postfixLT);
      h0LT_qcd_iso->Write();
      h0J_qcd_iso->SetName(name.c_str()+postfixJ);
      h0J_qcd_iso->Write();
    }

    TDirectory *d0_qcd_anti =fout->mkdir("mt_0jet_qcd_anti");
    d0_qcd_anti->cd();

    if (sample=="data_obs" or sample=="W"){
      h0LT_qcd_anti->SetName(name.c_str());
      h0LT_qcd_anti->Add(h0J_qcd_anti);
      h0LT_qcd_anti->Write();
    }
    else{
      h0LT_qcd_anti->SetName(name.c_str()+postfixLT);
      h0LT_qcd_anti->Write();
      h0J_qcd_anti->SetName(name.c_str()+postfixJ);
      h0J_qcd_anti->Write();
    }

    TDirectory *d1_qcd_iso =fout->mkdir("mt_1jet_qcd_iso");
    d1_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h1LT_qcd_iso->SetName(name.c_str());
      h1LT_qcd_iso->Add(h1J_qcd_iso);
      h1LT_qcd_iso->Write();
    }
    else{
      h1LT_qcd_iso->SetName(name.c_str()+postfixLT);
      h1LT_qcd_iso->Write();
      h1J_qcd_iso->SetName(name.c_str()+postfixJ);
      h1J_qcd_iso->Write();
    }
    TDirectory *d1_qcd_anti =fout->mkdir("mt_1jet_qcd_anti");
    d1_qcd_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h1LT_qcd_anti->SetName(name.c_str());
      h1LT_qcd_anti->Add(h1J_qcd_anti);
      h1LT_qcd_anti->Write();
    }
    else{
      h1LT_qcd_anti->SetName(name.c_str()+postfixLT);
      h1LT_qcd_anti->Write();
      h1J_qcd_anti->SetName(name.c_str()+postfixJ);
      h1J_qcd_anti->Write();
    }

    TDirectory *d2_qcd_iso =fout->mkdir("mt_2jet_qcd_iso");
    d2_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h2LT_qcd_iso->SetName(name.c_str());
      h2LT_qcd_iso->Add(h2J_qcd_iso);
      h2LT_qcd_iso->Write();
    }
    else{
      h2LT_qcd_iso->SetName(name.c_str()+postfixLT);
      h2LT_qcd_iso->Write();
      h2J_qcd_iso->SetName(name.c_str()+postfixJ);
      h2J_qcd_iso->Write();
    }
    TDirectory *d2_qcd_anti =fout->mkdir("mt_2jet_qcd_anti");
    d2_qcd_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h2LT_qcd_anti->SetName(name.c_str());
      h2LT_qcd_anti->Add(h2J_qcd_anti);
      h2LT_qcd_anti->Write();
    }
    else{
      h2LT_qcd_anti->SetName(name.c_str()+postfixLT);
      h2LT_qcd_anti->Write();
      h2J_qcd_anti->SetName(name.c_str()+postfixJ);
      h2J_qcd_anti->Write();
    }

    TDirectory *d0SSloose_qcd_iso =fout->mkdir("mt_0SSloose_qcd_iso");
    d0SSloose_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h0SSlooseLT_qcd_iso->SetName(name.c_str());
      h0SSlooseLT_qcd_iso->Add(h0SSlooseJ_qcd_iso);
      h0SSlooseLT_qcd_iso->Write();
    }
    else{
      h0SSlooseLT_qcd_iso->SetName(name.c_str()+postfixLT);
      h0SSlooseLT_qcd_iso->Write();
      h0SSlooseJ_qcd_iso->SetName(name.c_str()+postfixJ);
      h0SSlooseJ_qcd_iso->Write();
    }

    TDirectory *d0SSloose_qcd_anti =fout->mkdir("mt_0SSloose_qcd_anti");
    d0SSloose_qcd_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h0SSlooseLT_qcd_anti->SetName(name.c_str());
      h0SSlooseLT_qcd_anti->Add(h0SSlooseJ_qcd_anti);
      h0SSlooseLT_qcd_anti->Write();
    }
    else{
      h0SSlooseLT_qcd_anti->SetName(name.c_str()+postfixLT);
      h0SSlooseLT_qcd_anti->Write();
      h0SSlooseJ_qcd_anti->SetName(name.c_str()+postfixJ);
      h0SSlooseJ_qcd_anti->Write();
    }

    TDirectory *d1SSloose_qcd_iso =fout->mkdir("mt_1SSloose_qcd_iso");
    d1SSloose_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h1SSlooseLT_qcd_iso->SetName(name.c_str());
      h1SSlooseLT_qcd_iso->Add(h1SSlooseJ_qcd_iso);
      h1SSlooseLT_qcd_iso->Write();
    }
    else{
      h1SSlooseLT_qcd_iso->SetName(name.c_str()+postfixLT);
      h1SSlooseLT_qcd_iso->Write();
      h1SSlooseJ_qcd_iso->SetName(name.c_str()+postfixJ);
      h1SSlooseJ_qcd_iso->Write();
    }
    TDirectory *d1SSloose_qcd_anti =fout->mkdir("mt_1SSloose_qcd_anti");
    d1SSloose_qcd_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h1SSlooseLT_qcd_anti->SetName(name.c_str());
      h1SSlooseLT_qcd_anti->Add(h1SSlooseJ_qcd_anti);
      h1SSlooseLT_qcd_anti->Write();
    }
    else{
      h1SSlooseLT_qcd_anti->SetName(name.c_str()+postfixLT);
      h1SSlooseLT_qcd_anti->Write();
      h1SSlooseJ_qcd_anti->SetName(name.c_str()+postfixJ);
      h1SSlooseJ_qcd_anti->Write();
    }

    TDirectory *d2SSloose_qcd_iso =fout->mkdir("mt_2SSloose_qcd_iso");
    d2SSloose_qcd_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h2SSlooseLT_qcd_iso->SetName(name.c_str());
      h2SSlooseLT_qcd_iso->Add(h2SSlooseJ_qcd_iso);
      h2SSlooseLT_qcd_iso->Write();
    }
    else{
      h2SSlooseLT_qcd_iso->SetName(name.c_str()+postfixLT);
      h2SSlooseLT_qcd_iso->Write();
      h2SSlooseJ_qcd_iso->SetName(name.c_str()+postfixJ);
      h2SSlooseJ_qcd_iso->Write();
    }
    TDirectory *d2SSloose_qcd_anti =fout->mkdir("mt_2SSloose_qcd_anti");
    d2SSloose_qcd_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h2SSlooseLT_qcd_anti->SetName(name.c_str());
      h2SSlooseLT_qcd_anti->Add(h2SSlooseJ_qcd_anti);
      h2SSlooseLT_qcd_anti->Write();
    }
    else{
      h2SSlooseLT_qcd_anti->SetName(name.c_str()+postfixLT);
      h2SSlooseLT_qcd_anti->Write();
      h2SSlooseJ_qcd_anti->SetName(name.c_str()+postfixJ);
      h2SSlooseJ_qcd_anti->Write();
    }

    TDirectory *d0_w_iso =fout->mkdir("mt_0jet_w_iso");
    d0_w_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h0LT_w_iso->SetName(name.c_str());
      h0LT_w_iso->Add(h0J_w_iso);
      h0LT_w_iso->Write();
    }
    else{
      h0LT_w_iso->SetName(name.c_str()+postfixLT);
      h0LT_w_iso->Write();
      h0J_w_iso->SetName(name.c_str()+postfixJ);
      h0J_w_iso->Write();
    }

    TDirectory *d0_w_anti =fout->mkdir("mt_0jet_w_anti");
    d0_w_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h0LT_w_anti->SetName(name.c_str());
      h0LT_w_anti->Add(h0J_w_anti);
      h0LT_w_anti->Write();
    }
    else{
      h0LT_w_anti->SetName(name.c_str()+postfixLT);
      h0LT_w_anti->Write();
      h0J_w_anti->SetName(name.c_str()+postfixJ);
      h0J_w_anti->Write();
    }

    TDirectory *d1_w_iso =fout->mkdir("mt_1jet_w_iso");
    d1_w_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h1LT_w_iso->SetName(name.c_str());
      h1LT_w_iso->Add(h1J_w_iso);
      h1LT_w_iso->Write();
    }
    else{
      h1LT_w_iso->SetName(name.c_str()+postfixLT);
      h1LT_w_iso->Write();
      h1J_w_iso->SetName(name.c_str()+postfixJ);
      h1J_w_iso->Write();
    }
    TDirectory *d1_w_anti =fout->mkdir("mt_1jet_w_anti");
    d1_w_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h1LT_w_anti->SetName(name.c_str());
      h1LT_w_anti->Add(h1J_w_anti);
      h1LT_w_anti->Write();
    }
    else{
      h1LT_w_anti->SetName(name.c_str()+postfixLT);
      h1LT_w_anti->Write();
      h1J_w_anti->SetName(name.c_str()+postfixJ);
      h1J_w_anti->Write();
    }

    TDirectory *d2_w_iso =fout->mkdir("mt_2jet_w_iso");
    d2_w_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h2LT_w_iso->SetName(name.c_str());
      h2LT_w_iso->Add(h2J_w_iso);
      h2LT_w_iso->Write();
    }
    else{
      h2LT_w_iso->SetName(name.c_str()+postfixLT);
      h2LT_w_iso->Write();
      h2J_w_iso->SetName(name.c_str()+postfixJ);
      h2J_w_iso->Write();
    }
    TDirectory *d2_w_anti =fout->mkdir("mt_2jet_w_anti");
    d2_w_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h2LT_w_anti->SetName(name.c_str());
      h2LT_w_anti->Add(h2J_w_anti);
      h2LT_w_anti->Write();
    }
    else{
      h2LT_w_anti->SetName(name.c_str()+postfixLT);
      h2LT_w_anti->Write();
      h2J_w_anti->SetName(name.c_str()+postfixJ);
      h2J_w_anti->Write();
    }

    TDirectory *d0_tt_iso =fout->mkdir("mt_0jet_tt_iso");
    d0_tt_iso->cd();
    if (sample=="data_obs" or sample=="W"){
      h0LT_tt_iso->SetName(name.c_str());
      h0LT_tt_iso->Add(h0J_tt_iso);
      h0LT_tt_iso->Write();
    }
    else{
      h0LT_tt_iso->SetName(name.c_str()+postfixLT);
      h0LT_tt_iso->Write();
      h0J_tt_iso->SetName(name.c_str()+postfixJ);
      h0J_tt_iso->Write();
    }

    TDirectory *d0_tt_anti =fout->mkdir("mt_0jet_tt_anti");
    d0_tt_anti->cd();
    if (sample=="data_obs" or sample=="W"){
      h0LT_tt_anti->SetName(name.c_str());
      h0LT_tt_anti->Add(h0J_tt_anti);
      h0LT_tt_anti->Write();
    }
    else{
      h0LT_tt_anti->SetName(name.c_str()+postfixLT);
      h0LT_tt_anti->Write();
      h0J_tt_anti->SetName(name.c_str()+postfixJ);
      h0J_tt_anti->Write();
    }


    fout->Close();
    delete wmc;
} 


