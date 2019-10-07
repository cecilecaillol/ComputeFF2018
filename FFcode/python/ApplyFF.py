import ROOT

class FFApplicationTool():
    def __init__(self,theFFDirectory,channel):
        self.theFFDirectory = theFFDirectory
        
        self.theRawFile = ROOT.TFile(theFFDirectory+"uncorrected_fakefactors_"+channel+".root")
        if self.theRawFile.IsZombie():            
            raise RuntimeError("Problem loading the files!")
        self.ff_qcd_0jet = theRawFile.Get("rawFF_"+channel+"_qcd_0jet")
        self.ff_qcd_1jet = theRawFile.Get("rawFF_"+channel+"_qcd_1jet")
        self.ff_w_0jet = theRawFile.Get("rawFF_"+channel+"_w_0jet")
        self.ff_w_1jet = theRawFile.Get("rawFF_"+channel+"_w_1jet")
        self.ff_tt_0jet = theRawFile.Get("mc_rawFF_"+channel+"_tt")

        self.theFMvisFile = ROOT.TFile(theFFDirectory+"FF_corrections_1.root")
        if self.theFMvisFile.IsZombie():
            raise RuntimeError("Problem loading the files!")
        self.mVisClosure_QCD = theFMvisFile.Get("closure_mvis_"+channel+"_qcd")
        self.mVisClosure_W = theFMvisFile.Get("closure_mvis_"+channel+"_w")
        self.mVisClosure_TT = theFMvisFile.Get("closure_mvis_"+channel+"_ttmc")

        self.theFOSSSClosureFile = ROOT.TFile("FF_QCDcorrectionOSSS.root")
        if self.theFOSSSClosureFile.IsZombie():
            raise RuntimeError("Problem loading the files!")
        self.OSSSClosure_QCD = theFOSSSClosureFile.Get("closure_mvis_"+channel+"_qcd")
        self.MTClosure_W = theFOSSSClosureFile.Get("closure_mt_"+channel+"_w")

    def get_raw_FF(self,pt,fct):
        ff=1.0
        ff=fct.Eval(pt)    
        #if(pt>80):
        #    ff=fct.Eval(80)
        return ff

    def get_mvis_closure(self,mvis,fct):
        corr = 1.0
        corr = fct.Eval(mvis)
        if(mvis>350):
            corr=fct.Eval(350)
        #if (mvis<50):
        #    corr=fct.Eval(50)
        return corr

    def get_mt_closure(self,mt, fct):
        corr=1.0
        corr=fct.Eval(mt)
        #if (mt>120):
        #    corr=fct.Eval(120)
        return corr

    def get_ff(self, pt, mt, mvis, njets, frac_tt, frac_qcd, frac_w):
        ff_qcd = 1.0
        ff_w = 0
        ff_tt = 1.0
    
        #Raw ff
        if(njets==0):
            ff_qcd=get_raw_FF(pt,self.ff_qcd_0jet)
            ff_w=get_raw_FF(pt,self.ff_w_0jet)
        else:
            ff_qcd=get_raw_FF(pt,self.ff_qcd_1jet)
            ff_w=get_raw_FF(pt,self.ff_w_1jet)
        ff_tt=get_raw_FF(pt,self.ff_tt_0jet)

        #mvis closure
        ff_qcd = ff_qcd*get_mvis_closure(mvis,self.mVisClosure_QCD)
        ff_w = ff_w*get_mvis_closure(mvis,self.mVisClosure_W)
        ff_tt = ff_tt*get_mvis_closure(mvis,self.mVisClosure_TT)
        
        #MT and OSSS corrections
        ff_w = ff_w*get_mt_closure(mt,self.MTClosure_W)
        ff_qcd = ff_qcd*get_mvis_closure(mvis,self.OSSSClosure_QCD)
        
        ff_cmb = frac_tt*ff_tt + frac_qcd*ff_qcd + frac_w*ff_w
        return ff_cmb
