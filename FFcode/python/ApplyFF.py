import ROOT

class FFApplicationTool():
    def __init__(self,theFFDirectory,channel,isDifferential=False,attempt0JetMETCorrection=False):
        self.theFFDirectory = theFFDirectory
        self.isDifferential = isDifferential
        self.attempt0JetMETCorrection = attempt0JetMETCorrection
        
        self.theRawFile = ROOT.TFile(theFFDirectory+"uncorrected_fakefactors_"+channel+".root")
        if self.theRawFile.IsZombie():            
            raise RuntimeError("Problem loading the files!")
        self.ff_qcd_0jet = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet")
        self.ff_qcd_0jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_unc1_up")
        self.ff_qcd_0jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_unc1_down")
        self.ff_qcd_0jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_unc2_up")
        self.ff_qcd_0jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_unc2_down")

        #barrel
        self.ff_qcd_0jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_barrel")
        self.ff_qcd_0jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_barrel_unc1_up")
        self.ff_qcd_0jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_barrel_unc1_down")
        self.ff_qcd_0jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_barrel_unc2_up")
        self.ff_qcd_0jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_barrel_unc2_down")

        #endcap
        self.ff_qcd_0jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_endcaps")
        self.ff_qcd_0jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_endcaps_unc1_up")
        self.ff_qcd_0jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_endcaps_unc1_down")
        self.ff_qcd_0jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_endcaps_unc2_up")
        self.ff_qcd_0jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_0jet_endcaps_unc2_down")

        self.ff_qcd_1jet = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet")
        self.ff_qcd_1jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_unc1_up")
        self.ff_qcd_1jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_unc1_down")
        self.ff_qcd_1jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_unc2_up")
        self.ff_qcd_1jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_unc2_down")

        #barrel
        self.ff_qcd_1jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_barrel")
        self.ff_qcd_1jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_barrel_unc1_up")
        self.ff_qcd_1jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_barrel_unc1_down")
        self.ff_qcd_1jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_barrel_unc2_up")
        self.ff_qcd_1jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_barrel_unc2_down")

        #endcap
        self.ff_qcd_1jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_endcaps")
        self.ff_qcd_1jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_endcaps_unc1_up")
        self.ff_qcd_1jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_endcaps_unc1_down")
        self.ff_qcd_1jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_endcaps_unc2_up")
        self.ff_qcd_1jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_1jet_endcaps_unc2_down")

        self.ff_qcd_2jet = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet")
        self.ff_qcd_2jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_unc1_up")
        self.ff_qcd_2jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_unc1_down")
        self.ff_qcd_2jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_unc2_up")
        self.ff_qcd_2jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_unc2_down")
 
        #barrel
        self.ff_qcd_2jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_barrel")
        self.ff_qcd_2jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_barrel_unc1_up")
        self.ff_qcd_2jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_barrel_unc1_down")
        self.ff_qcd_2jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_barrel_unc2_up")
        self.ff_qcd_2jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_barrel_unc2_down")

        #endcap
        self.ff_qcd_2jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_endcaps")
        self.ff_qcd_2jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_endcaps_unc1_up")
        self.ff_qcd_2jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_endcaps_unc1_down")
        self.ff_qcd_2jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_endcaps_unc2_up")
        self.ff_qcd_2jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_qcd_2jet_endcaps_unc2_down")

        self.ff_w_0jet = self.theRawFile.Get("rawFF_"+channel+"_w_0jet")
        self.ff_w_0jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_unc1_up")
        self.ff_w_0jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_unc1_down")
        self.ff_w_0jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_unc2_up")
        self.ff_w_0jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_unc2_down")

        #barrel
        self.ff_w_0jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_barrel")
        self.ff_w_0jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_barrel_unc1_up")
        self.ff_w_0jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_barrel_unc1_down")
        self.ff_w_0jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_barrel_unc2_up")
        self.ff_w_0jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_barrel_unc2_down")

        #endcap
        self.ff_w_0jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_endcaps")
        self.ff_w_0jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_endcaps_unc1_up")
        self.ff_w_0jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_endcaps_unc1_down")
        self.ff_w_0jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_endcaps_unc2_up")
        self.ff_w_0jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_0jet_endcaps_unc2_down")

        self.ff_w_1jet = self.theRawFile.Get("rawFF_"+channel+"_w_1jet")
        self.ff_w_1jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_unc1_up")
        self.ff_w_1jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_unc1_down")
        self.ff_w_1jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_unc2_up")
        self.ff_w_1jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_unc2_down")

        #barrel
        self.ff_w_1jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_barrel")
        self.ff_w_1jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_barrel_unc1_up")
        self.ff_w_1jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_barrel_unc1_down")
        self.ff_w_1jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_barrel_unc2_up")
        self.ff_w_1jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_barrel_unc2_down")

        #endcap
        self.ff_w_1jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_endcaps")
        self.ff_w_1jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_endcaps_unc1_up")
        self.ff_w_1jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_endcaps_unc1_down")
        self.ff_w_1jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_endcaps_unc2_up")
        self.ff_w_1jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_1jet_endcaps_unc2_down")
        
        self.ff_w_2jet = self.theRawFile.Get("rawFF_"+channel+"_w_2jet")
        self.ff_w_2jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_unc1_up")
        self.ff_w_2jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_unc1_down")
        self.ff_w_2jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_unc2_up")
        self.ff_w_2jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_unc2_down")

        #barrel
        self.ff_w_2jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_barrel")
        self.ff_w_2jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_barrel_unc1_up")
        self.ff_w_2jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_barrel_unc1_down")
        self.ff_w_2jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_barrel_unc2_up")
        self.ff_w_2jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_barrel_unc2_down")

        #endcap
        self.ff_w_2jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_endcaps")
        self.ff_w_2jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_endcaps_unc1_up")
        self.ff_w_2jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_endcaps_unc1_down")
        self.ff_w_2jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_endcaps_unc2_up")
        self.ff_w_2jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_2jet_endcaps_unc2_down")

        self.ff_w_3jet = self.theRawFile.Get("rawFF_"+channel+"_w_3jet")
        self.ff_w_3jet_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_unc1_up")
        self.ff_w_3jet_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_unc1_down")
        self.ff_w_3jet_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_unc2_up")
        self.ff_w_3jet_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_unc2_down")

        #barrel
        self.ff_w_3jet_barrel = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_barrel")
        self.ff_w_3jet_barrel_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_barrel_unc1_up")
        self.ff_w_3jet_barrel_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_barrel_unc1_down")
        self.ff_w_3jet_barrel_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_barrel_unc2_up")
        self.ff_w_3jet_barrel_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_barrel_unc2_down")

        #endcap
        self.ff_w_3jet_endcaps = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_endcaps")
        self.ff_w_3jet_endcaps_unc1_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_endcaps_unc1_up")
        self.ff_w_3jet_endcaps_unc1_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_endcaps_unc1_down")
        self.ff_w_3jet_endcaps_unc2_up = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_endcaps_unc2_up")
        self.ff_w_3jet_endcaps_unc2_down = self.theRawFile.Get("rawFF_"+channel+"_w_3jet_endcaps_unc2_down")

        self.ff_tt_0jet = self.theRawFile.Get("mc_rawFF_"+channel+"_tt")
        self.ff_tt_0jet_unc1_up = self.theRawFile.Get("mc_rawFF_"+channel+"_tt_unc1_up")
        self.ff_tt_0jet_unc1_down = self.theRawFile.Get("mc_rawFF_"+channel+"_tt_unc1_down")
        self.ff_tt_0jet_unc2_up = self.theRawFile.Get("mc_rawFF_"+channel+"_tt_unc2_up")
        self.ff_tt_0jet_unc2_down = self.theRawFile.Get("mc_rawFF_"+channel+"_tt_unc2_down")
        
        #FIXME
        self.theFMvisFile = ROOT.TFile(theFFDirectory+"FF_corrections_1.root")
        if self.theFMvisFile.IsZombie():
            raise RuntimeError("Problem loading the files!")
        
        #MVis closure
        self.mVisClosure_QCD_0jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_0jet_qcd")
        self.mVisClosure_QCD_1jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_1jet_qcd")
        self.mVisClosure_QCD_2jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_2jet_qcd")
        self.mVisClosure_W_0jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_0jet_w")
        self.mVisClosure_W_1jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_1jet_w")
        self.mVisClosure_W_2jet = self.theFMvisFile.Get("closure_mvis_"+channel+"_2jet_w")
        self.mVisClosure_TT = self.theFMvisFile.Get("closure_mvis_"+channel+"_ttmc")        
        #lptclosure
        if self.isDifferential:
            self.lptClosure_W_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_"+channel+"_w")
            self.lptClosure_W_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_"+channel+"_w")
            self.lptClosure_W_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_"+channel+"_w")
            self.lptClosure_QCD_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_"+channel+"_qcd")
            self.lptClosure_QCD_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_"+channel+"_qcd")
            self.lptClosure_QCD_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_"+channel+"_qcd")
            self.lptClosure_TT_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_"+channel+"_ttmc")
            self.lptClosure_TT_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_"+channel+"_ttmc")
            self.lptClosure_TT_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_"+channel+"_ttmc")
            
            self.lptClosure_W_xtrg_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_xtrg_"+channel+"_w")
            self.lptClosure_W_xtrg_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_xtrg_"+channel+"_w")
            self.lptClosure_W_xtrg_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_xtrg_"+channel+"_w")
            self.lptClosure_QCD_xtrg_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_xtrg_"+channel+"_qcd")
            self.lptClosure_QCD_xtrg_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_xtrg_"+channel+"_qcd")
            self.lptClosure_QCD_xtrg_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_xtrg_"+channel+"_qcd")
            self.lptClosure_TT_xtrg_taupt30to50 = self.theFMvisFile.Get("closure_lpt_taupt30to50_xtrg_"+channel+"_ttmc")
            self.lptClosure_TT_xtrg_taupt50to70 = self.theFMvisFile.Get("closure_lpt_taupt50to70_xtrg_"+channel+"_ttmc")
            self.lptClosure_TT_xtrg_tauptgt70 = self.theFMvisFile.Get("closure_lpt_tauptgt70_xtrg_"+channel+"_ttmc")        
        else:
            self.lptClosure_W_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_"+channel+"_w")
            self.lptClosure_W_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_"+channel+"_w")
            self.lptClosure_W_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_"+channel+"_w")
            self.lptClosure_QCD_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_"+channel+"_qcd")
            self.lptClosure_QCD_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_"+channel+"_qcd")
            self.lptClosure_QCD_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_"+channel+"_qcd")
            self.lptClosure_TT_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_"+channel+"_ttmc")
            self.lptClosure_TT_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_"+channel+"_ttmc")
            self.lptClosure_TT_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_"+channel+"_ttmc")
            
            self.lptClosure_W_xtrg_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_xtrg_"+channel+"_w")
            self.lptClosure_W_xtrg_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_xtrg_"+channel+"_w")
            self.lptClosure_W_xtrg_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_xtrg_"+channel+"_w")
            self.lptClosure_QCD_xtrg_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_xtrg_"+channel+"_qcd")
            self.lptClosure_QCD_xtrg_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_xtrg_"+channel+"_qcd")
            self.lptClosure_QCD_xtrg_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_xtrg_"+channel+"_qcd")
            self.lptClosure_TT_xtrg_taupt30to40 = self.theFMvisFile.Get("closure_lpt_taupt30to40_xtrg_"+channel+"_ttmc")
            self.lptClosure_TT_xtrg_taupt40to50 = self.theFMvisFile.Get("closure_lpt_taupt40to50_xtrg_"+channel+"_ttmc")
            self.lptClosure_TT_xtrg_tauptgt50 = self.theFMvisFile.Get("closure_lpt_tauptgt50_xtrg_"+channel+"_ttmc")        
        
        #MET closure? may be in other file?
        self.metClosure_W_0jet = self.theFMvisFile.Get("closure_met_"+channel+"_0jet_w")

        #MT and OSSS closure
        self.theFOSSSClosureFile = ROOT.TFile(theFFDirectory+"FF_QCDcorrectionOSSS.root")
        if self.theFOSSSClosureFile.IsZombie():
            raise RuntimeError("Problem loading the files!")
        
        #self.OSSSClosure_QCD = self.theFOSSSClosureFile.Get("closure_OSSS_mvis_"+channel+"_qcd")
        self.OSSSClosure_QCD = self.theFOSSSClosureFile.Get("closure_OSSS_dr_flat_"+channel+"_qcd")
        self.OSSSClosure_QCD_unc1_up = self.theFOSSSClosureFile.Get("closure_OSSS_mvis_"+channel+"_qcd_unc1_up")
        self.OSSSClosure_QCD_unc1_down = self.theFOSSSClosureFile.Get("closure_OSSS_mvis_"+channel+"_qcd_unc1_down")
        self.OSSSClosure_QCD_unc2_up = self.theFOSSSClosureFile.Get("closure_OSSS_mvis_"+channel+"_qcd_unc2_up")
        self.OSSSClosure_QCD_unc2_down = self.theFOSSSClosureFile.Get("closure_OSSS_mvis_"+channel+"_qcd_unc2_down")

        self.MTClosure_W = self.theFOSSSClosureFile.Get("closure_mt_"+channel+"_w")
        self.MTClosure_W_unc1_up = self.theFOSSSClosureFile.Get("closure_mt_"+channel+"_w_unc1_up")
        self.MTClosure_W_unc1_down = self.theFOSSSClosureFile.Get("closure_mt_"+channel+"_w_unc1_down")
        self.MTClosure_W_unc2_up = self.theFOSSSClosureFile.Get("closure_mt_"+channel+"_w_unc2_up")
        self.MTClosure_W_unc2_down = self.theFOSSSClosureFile.Get("closure_mt_"+channel+"_w_unc2_down")
        
        #this is now superseded
        self.PTHClosure_W = self.theFOSSSClosureFile.Get("closure_mt_"+channel+'pth_w')

        #New MT corrections for checking
        self.NJets0_MT = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtpth_0jet_w")
        self.NJetsGT0_MT_LJPT_LT_45 = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtljpt_pth0to45_w")
        self.NJetsGT0_MT_LJPT_45_80 = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtljpt_pth45to80_w")
        self.NJetsGT0_MT_LJPT_80_120 = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtljpt_pth80to120_w")
        self.NJetsGT0_MT_LJPT_120_200 = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtljpt_pth120to200_w")
        self.NJetsGT0_MT_LJPT_GT_200 = self.theFOSSSClosureFile.Get("closure_"+channel+"_mtljpt_pthgt200_w")

        #Tau pt corrections
        self.tauPtFile =  ROOT.TFile(theFFDirectory+"tauptcorrection_"+channel+".root")
        self.tauPtCorrection_qcd = self.tauPtFile.Get("mt_0jet_qcd_taupt_iso")
        self.tauPtCorrection_w = self.tauPtFile.Get("mt_0jet_w_taupt_iso")

        #test 0 jet met correction stuff
        if self.attempt0JetMETCorrection:
            self.closure_met_0jet_qcd = self.theFMvisFile.Get('closure_met_'+channel+'_0jet_qcd')

    def get_raw_FF(self,pt,fct):
        ff=1.0
        ff=fct.Eval(pt)    
        if(pt>100):
            ff=fct.Eval(100)
        return ff

    def get_mvis_closure(self,mvis,fct):
        corr = 1.0
        corr = fct.Eval(mvis)
        if(mvis>250):
            corr=fct.Eval(250)
        #if (mvis<50):
        #    corr=fct.Eval(50)
        return corr

    def get_mt_closure(self,mt, fct):
        corr=1.0
        corr=fct.Eval(mt)
        if (mt>175):
            corr=fct.Eval(175)
        return corr

    def get_mt_pth_closure(self,pth,fct):
        corr = 1.0
        corr = fct.Eval(pth)
        if (pth>175):
            corr = fct.Eval(175)
        return corr

    def get_mt_pth_ljpt_closure(self, j1pt, fct):
        corr = 1.0
        corr = fct.Eval(j1pt)
        if (j1pt>500):
            corr = fct.Eval(500)
        return corr

    def get_lpt_closure(self,lpt,fct):
        corr = 1.0
        #print("Lepton pt: "+str(lpt))
        #print(fct)
        corr = fct.Eval(lpt)
        #print("Correction: "+str(corr))
        #print("")
        if (lpt>150):
            corr = fct.Eval(150)
        return corr

    def get_dr_closure(self,dr,fct):
        corr = 1.0
        corr = fct.Eval(dr)
        return corr

    def get_MET_closure(self,met,fct):
        corr = 1.0
        corr = fct.Eval(met)
        if corr < 0:
            corr = 0
        return corr

    def get_PTH_closure(self,pth,fct):
        corr = 1.0
        if pth > 200:
            pth = 200
        corr = fct.Eval(pth)
        return corr

    def get_ff(self, pt, eta, mt, mvis, lpt, dr, met, njets, j1pt, pth, xtrg, frac_tt, frac_qcd, frac_w, unc='',upOrDown=''):
        
        #print('Uncertainty: '+unc)
        #print('upOrDown: '+upOrDown)
        #print('njets: '+str(njets))

        ff_qcd = 1.0
        ff_w = 1.0
        ff_tt = 1.0    
    
        #Raw ff
        if(njets==0):
            if abs(eta) < 1.4:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_0jet_barrel)
                if unc == 'ff_qcd_0jet_barrel_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_barrel_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_barrel_unc1_down)
                elif unc == 'ff_qcd_0jet_barrel_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_barrel_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_barrel_unc2_down)
                ff_w=self.get_raw_FF(pt,self.ff_w_0jet_barrel)
                if unc == 'ff_w_0jet_barrel_unc1':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_barrel_unc1_up)
                    elif upOrDown == 'down':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_barrel_unc1_down)
                elif unc == 'ff_w_0jet_barrel_unc2':                
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_barrel_unc2_up)
                    elif upOrDown == 'down':
                        ff_w = self.get_raw_FF(pt,self.ff_w_0jet_barrel_unc2_down)                    
            else:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_0jet_endcaps)
                if unc == 'ff_qcd_0jet_endcaps_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_endcaps_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_endcaps_unc1_down)
                elif unc == 'ff_qcd_0jet_endcaps_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_endcaps_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_0jet_endcaps_unc2_down)
                ff_w=self.get_raw_FF(pt,self.ff_w_0jet_endcaps)
                if unc == 'ff_w_0jet_endcaps_unc1':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_endcaps_unc1_up)
                    elif upOrDown == 'down':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_endcaps_unc1_down)
                elif unc == 'ff_w_0jet_endcaps_unc2':                
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_0jet_endcaps_unc2_up)
                    elif upOrDown == 'down':
                        ff_w = self.get_raw_FF(pt,self.ff_w_0jet_endcaps_unc2_down)                    
        elif(njets==1):
            if abs(eta) < 1.4:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_1jet_barrel)
                if unc == 'ff_qcd_1jet_barrel_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_barrel_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_barrel_unc1_down)
                elif unc == 'ff_qcd_1jet_barrel_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_barrel_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_barrel_unc2_down)
                ff_w=self.get_raw_FF(pt,self.ff_w_1jet_barrel)
                if unc == 'ff_w_1jet_barrel_unc1':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_barrel_unc1_up)
                    elif upOrDown == 'down':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_barrel_unc1_down)
                elif unc == 'ff_w_1jet_unc2':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_barrel_unc2_up)
                    elif upOrDown == 'down':
                        ff_w = self.get_raw_FF(pt,self.ff_w_1jet_barrel_unc2_down)
            else:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_1jet_endcaps)
                if unc == 'ff_qcd_1jet_endcaps_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_endcaps_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_endcaps_unc1_down)
                elif unc == 'ff_qcd_1jet_endcaps_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_endcaps_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_1jet_endcaps_unc2_down)
                ff_w=self.get_raw_FF(pt,self.ff_w_1jet_endcaps)
                if unc == 'ff_w_1jet_endcaps_unc1':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_endcaps_unc1_up)
                    elif upOrDown == 'down':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_endcaps_unc1_down)
                elif unc == 'ff_w_1jet_unc2':
                    if upOrDown == 'up':
                        ff_w=self.get_raw_FF(pt,self.ff_w_1jet_endcaps_unc2_up)
                    elif upOrDown == 'down':
                        ff_w = self.get_raw_FF(pt,self.ff_w_1jet_endcaps_unc2_down)
                
        else:
            if abs(eta) < 1.4:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_2jet_barrel)
                if unc == 'ff_qcd_2jet_barrel_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_barrel_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_barrel_unc1_down)
                elif unc == 'ff_qcd_2jet_barrel_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_barrel_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_barrel_unc2_down)
            else:
                ff_qcd=self.get_raw_FF(pt,self.ff_qcd_2jet_endcaps)
                if unc == 'ff_qcd_2jet_endcaps_unc1':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_endcaps_unc1_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_endcaps_unc1_down)
                elif unc == 'ff_qcd_2jet_endcaps_unc2':
                    if upOrDown == 'up':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_endcaps_unc2_up)
                    elif upOrDown == 'down':
                        ff_qcd = self.get_raw_FF(pt,self.ff_qcd_2jet_endcaps_unc2_down)
            if njets == 2:
                if abs(eta) < 1.4:
                    ff_w=self.get_raw_FF(pt,self.ff_w_2jet_barrel)
                    if unc == 'ff_w_2jet_barrel_unc1':
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_barrel_unc1_up)
                        elif upOrDown == 'down':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_barrel_unc1_down)
                    elif unc == 'ff_w_2jet_barrel_unc2':                
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_barrel_unc2_up)
                        elif upOrDown == 'down':
                            ff_w = self.get_raw_FF(pt,self.ff_w_2jet_barrel_unc2_down)
                else:
                    ff_w=self.get_raw_FF(pt,self.ff_w_2jet_endcaps)
                    if unc == 'ff_w_2jet_endcaps_unc1':
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_endcaps_unc1_up)
                        elif upOrDown == 'down':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_endcaps_unc1_down)
                    elif unc == 'ff_w_2jet_endcaps_unc2':                
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_2jet_endcaps_unc2_up)
                        elif upOrDown == 'down':
                            ff_w = self.get_raw_FF(pt,self.ff_w_2jet_endcaps_unc2_down)
                    
            else:
                if abs(eta) < 1.4:
                    ff_w=self.get_raw_FF(pt,self.ff_w_3jet_barrel)
                    if unc == 'ff_w_3jet_barrel_unc1':
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_barrel_unc1_up)
                        elif upOrDown == 'down':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_barrel_unc1_down)
                    elif unc == 'ff_w_3jet_barrel_unc2':                
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_barrel_unc2_up)
                        elif upOrDown == 'down':
                            ff_w = self.get_raw_FF(pt,self.ff_w_3jet_barrel_unc2_down)
                else:
                    ff_w=self.get_raw_FF(pt,self.ff_w_3jet_endcaps)
                    if unc == 'ff_w_3jet_endcaps_unc1':
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_endcaps_unc1_up)
                        elif upOrDown == 'down':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_endcaps_unc1_down)
                    elif unc == 'ff_w_3jet_endcaps_unc2':                
                        if upOrDown == 'up':
                            ff_w=self.get_raw_FF(pt,self.ff_w_3jet_endcaps_unc2_up)
                        elif upOrDown == 'down':
                            ff_w = self.get_raw_FF(pt,self.ff_w_3jet_endcaps_unc2_down)
        ff_tt=self.get_raw_FF(pt,self.ff_tt_0jet)
        if unc == 'ff_tt_0jet_unc1':
            if upOrDown == 'up':
                ff_tt=self.get_raw_FF(pt,self.ff_tt_0jet_unc1_up)
            elif upOrDown == 'down':
                ff_tt=self.get_raw_FF(pt,self.ff_tt_0jet_unc1_down)
        elif unc == 'ff_tt_0jet_unc2':
            if upOrDown == 'up':
                ff_tt=self.get_raw_FF(pt,self.ff_tt_0jet_unc2_up)
            elif upOrDown == 'down':
                ff_tt=self.get_raw_FF(pt,self.ff_tt_0jet_unc2_down)

        #MET closure
        """
        if njets == 0:                        
            #print("MET closure")
            #print(self.get_MET_closure(met,self.metClosure_W_0jet))
            ff_w = ff_w*self.get_MET_closure(met,self.metClosure_W_0jet)
        """
        
        #lpt closures
        if self.isDifferential:
            if (xtrg):            
                if unc == 'lptclosure_xtrg_qcd':
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt50to70)
                    elif pt > 70:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt70)
                if unc == 'lptclosure_xtrg_w':
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt50to70)
                    elif pt > 70:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt70)
                if unc == 'lptclosure_xtrg_tt':                
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt50to70)
                    elif pt > 70:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt70)
            else:
                if unc == 'lptclosure_qcd':
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt50to70)
                    elif pt > 70:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt70)
                if unc == 'lptclosure_w':
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt50to70)
                    elif pt > 70:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt70)
                if unc == 'lptclosure_tt':
                    if pt > 30 and pt <= 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to50)*0.9
                    elif pt > 50 and pt <= 70:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt50to70)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt50to70)*0.9
                    elif pt > 70:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt70)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt70)*0.9
                else:
                    if pt > 30 and pt <= 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to50)
                    elif pt > 50 and pt <= 70:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt50to70)
                    elif pt > 70:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt70)
                    #REMOVE ME
                    #if njets == 0 and unc == '':
                        #print('Lepton pt: '+str(lpt))
                        #if pt > 30 and pt <= 50:
                        #    print("30-50 W mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to50)))
                        #    print("30-50 QCD mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to50)))
                        #    print("30-50 TT mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to50)))
                        #elif pt > 50 and pt <= 70:
                        #    print("50-70 W mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_W_taupt50to70)))
                        #    print("50-70 QCD mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt50to70)))
                        #    print("50-70 TT mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_TT_taupt50to70)))
                        #elif pt > 70:
                        #    print(">70 W mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt70)))
                        #    print(">70 QCD mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt70)))
                        #    print(">70 TT mu pt correction: "+str(self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt70)))
                        #print('')
        else:
            if (xtrg):            
                if unc == 'lptclosure_xtrg_qcd':
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_taupt40to50)
                    elif pt > 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_xtrg_tauptgt50)
                if unc == 'lptclosure_xtrg_w':
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_taupt40to50)
                    elif pt > 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_xtrg_tauptgt50)
                if unc == 'lptclosure_xtrg_tt':                
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_taupt40to50)
                    elif pt > 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_xtrg_tauptgt50)
            else:
                if unc == 'lptclosure_qcd':
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_taupt40to50)
                    elif pt > 50:
                        ff_qcd = ff_qcd*self.get_lpt_closure(lpt, self.lptClosure_QCD_tauptgt50)
                if unc == 'lptclosure_w':
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_taupt40to50)
                    elif pt > 50:
                        ff_w = ff_w*self.get_lpt_closure(lpt, self.lptClosure_W_tauptgt50)
                if unc == 'lptclosure_tt':
                    if pt > 30 and pt <= 40:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to40)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to40)*0.9
                    elif pt > 40 and pt <= 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt40to50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt40to50)*0.9
                    elif pt > 50:
                        if upOrDown == "up":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt50)*1.1
                        elif upOrDown == "down":
                            ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt50)*0.9
                else:
                    if pt > 30 and pt <= 40:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt30to40)
                    elif pt > 40 and pt <= 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_taupt40to50)
                    elif pt > 50:
                        ff_tt = ff_tt*self.get_lpt_closure(lpt, self.lptClosure_TT_tauptgt50)
        
        #MT and OSSS corrections
        #MT closure now superseded by pth closure.
        if unc == 'mtclosure_w_unc1':
            if upOrDown == 'up':
                ff_w = ff_w*self.get_mt_closure(mt,self.MTClosure_W_unc1_up)
            elif upOrDown == 'down':
                ff_w = ff_w*self.get_mt_closure(mt,self.MTClosure_W_unc1_down)
        elif unc == 'mtclosure_w_unc2':            
            if upOrDown == 'up':
                ff_w = ff_w*self.get_mt_closure(mt,self.MTClosure_W_unc2_up)
            elif upOrDown == 'down':
                ff_w = ff_w*self.get_mt_closure(mt,self.MTClosure_W_unc2_down)
        else:
            ff_w = ff_w*self.get_mt_closure(mt,self.MTClosure_W)

        #print(self.get_PTH_closure(pth,self.PTHClosure_W))
        """
        if unc == 'pthclosure_w':
            if upOrDown == 'up':
                ff_w = ff_w * (2*self.get_PTH_closure(pth,self.PTHClosure_W)-1.0)
            elif upOrDown == 'down':
                ff_w = ff_w * 1
        else:
            ff_w = ff_w*self.get_PTH_closure(pth,self.PTHClosure_W)
        """        
        if (njets == 0):
            if unc == 'njets0_pth_closure':
                if upOrDown == 'up':
                    ff_w = ff_w * (2*self.get_mt_pth_closure(pth, self.NJets0_MT)-1.0)
                elif upOrDown == 'down':
                    ff_w = ff_w * 1
            else:
                ff_w = ff_w*self.get_mt_pth_closure(pth, self.NJets0_MT)
        else:
            if pth < 45:
                if unc == 'njets_pth0to45_ljpt_closure':
                    if upOrDown == 'up':
                        ff_w = ff_w * (2*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_LT_45)-1.0)
                    elif upOrDown == 'down':
                        ff_w = ff_w * 1
                else:
                    ff_w = ff_w*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_LT_45)
            elif pth > 45 and pth < 80:
                if unc == 'njets_pth45to80_ljpt_closure':
                    if upOrDown == 'up':
                        ff_w = ff_w * (2*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_45_80)-1.0)
                    elif upOrDown == 'down':
                        ff_w = ff_w * 1
                else:
                    ff_w = ff_w*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_45_80)
            elif pth > 80 and pth < 120:
                if unc == 'njets_pth80to120_ljpt_closure':
                    if upOrDown == 'up':
                        ff_w = ff_w * (2*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_80_120)-1.0)
                    elif upOrDown == 'down':
                        ff_w = ff_w * 1
                else:
                    ff_w = ff_w*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_80_120)
            elif pth > 120 and pth < 200:
                if unc == 'njets_pth120to200_ljpt_closure':
                    if upOrDown == 'up':
                        ff_w = ff_w * (2*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_120_200)-1.0)
                    elif upOrDown == 'down':
                        ff_w = ff_w * 1
                else:
                    ff_w = ff_w*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_120_200)
            elif pth > 200:
                if unc == 'njets_pthgt200_ljpt_closure':
                    if upOrDown == 'up':
                        ff_w = ff_w * (2*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_GT_200)-1.0)
                    elif upOrDown == 'down':
                        ff_w = ff_w * 1
                else:
                    ff_w = ff_w*self.get_mt_pth_ljpt_closure(j1pt, self.NJetsGT0_MT_LJPT_GT_200)
        
        if unc == 'osssclosure_qcd':            
            if upOrDown == 'up':                
                ff_qcd = ff_qcd * self.get_dr_closure(dr,self.OSSSClosure_QCD)*1.1
            elif upOrDown == 'down':
                ff_qcd = ff_qcd * self.get_dr_closure(dr,self.OSSSClosure_QCD)*0.9                       
        else:                        
            ff_qcd = ff_qcd * self.get_dr_closure(dr,self.OSSSClosure_QCD)
 
        #put in this test correction
        #if self.attempt0JetMETCorrection:
            #ff_qcd = ff_qcd * self.get_MET_closure(met,self.closure_met_0jet_qcd)
            #if met <70:
                #ff_w = ff_w * 1.05
            #elif met > 70 and met < 100:
                #ff_w = ff_w * 0.95
            #else:
                #ff_w = ff_w * 0.85
        
        ff_cmb = frac_tt*ff_tt + frac_qcd*ff_qcd + frac_w*ff_w
        return ff_cmb
