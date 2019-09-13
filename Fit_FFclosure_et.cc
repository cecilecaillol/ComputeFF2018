#include <TLatex.h>
#include <TGraph.h>

#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
//#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TMatrixD.h"
#include "TMinuit.h"
//#include "HttStyles.h"

double square(double x)
{
  return x*x;
}

void makeBinsInteger(TH1* histogram_pass, TH1* histogram_fail)
{
  assert(histogram_pass->GetNbinsX() == histogram_fail->GetNbinsX());
  int numBins = histogram_pass->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    if (histogram_pass->GetBinContent(iBin)<0){ histogram_pass->SetBinContent(iBin,0); histogram_pass->SetBinError(iBin,0);}
    if (histogram_fail->GetBinContent(iBin)<0){ histogram_fail->SetBinContent(iBin,0); histogram_fail->SetBinError(iBin,0);}
    double binContent_sum = histogram_pass->GetBinContent(iBin) + histogram_fail->GetBinContent(iBin);
    double binError2_sum = square(histogram_pass->GetBinError(iBin)) + square(histogram_fail->GetBinError(iBin));
    double binError_sum = TMath::Sqrt(binError2_sum);
    if ( binContent_sum > 0. && binError_sum > 0. ) {
      double nEff = square(binContent_sum/binError_sum);
      double avWeight = binContent_sum/nEff;
      double binContent_pass = TMath::Nint(histogram_pass->GetBinContent(iBin)/avWeight);
      double binError_pass = TMath::Sqrt(binContent_pass);
      histogram_pass->SetBinContent(iBin, binContent_pass);
      histogram_pass->SetBinError(iBin, binError_pass);
      double binContent_fail = TMath::Nint(histogram_fail->GetBinContent(iBin)/avWeight);
      double binError_fail = TMath::Sqrt(binContent_fail);
      histogram_fail->SetBinContent(iBin, binContent_fail);
      histogram_fail->SetBinError(iBin, binError_fail);
    }
  }
}

double fitFunction(double x, double par0, double par1) {
    return par0 + par1 *(x-40);
}

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    return par[0] + par[1]* (x[0]-40);
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    //return par[0] + par[1] * x[0] + par[2] * x[0]* x[0];// + par[3] * x[0]* x[0] *x[0];
    return par[0] + par[1]* (x[0]-80);
    //    return par[0] + par[1]*x[0] + par[2]*(TMath::Landau(x[0],par[3],par[4],0));
//return par[0] + par[1]*(TMath::Exp(par[2] * x[0]-par[3]));
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, std::string name, TH2F * hist2D_lep, Double_t fMin, Double_t fMax) {
    //SetStyle();
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);

    makeBinsInteger(histogram_pass, histogram_fail);

    TGraphAsymmErrors* TGraph_FR = new TGraphAsymmErrors(26);
    TGraph_FR->Divide(histogram_pass, histogram_fail, "pois");

    Double_t *yg = TGraph_FR->GetY();
    for (int i = 0; i<5; i++) printf("yg[%d] = %g\n", i,yg[i]);

    const int nPar = 2; // number of parameters in the fit

    TF1 * theFit = new TF1("theFit", fitFunc_Line2Par, fMin, fMax, nPar);

    theFit->SetParameter(0, 0.2);
    theFit->SetParameter(1, 0.01);
    theFit->SetParameter(2, 0.00001);
    theFit->SetParameter(3, 0.00000001);

    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    //TGraph_FR->GetYaxis()->SetRangeUser(0.00,1.5*yg[0]);
    TGraph_FR->GetYaxis()->SetRangeUser(0.0,2.00);
    TGraph_FR->GetYaxis()->SetTitle("Correction");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 300);
    TGraph_FR->GetXaxis()->SetTitle("m_{vis}(e,#tau_{h}) (GeV)");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "mvis_closure_fit_" + name + ".pdf";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    t.DrawLatex(0.55, .96, "59.5 fb^{-1} (2018, 13 TeV)");
    float aup; float adown; float bup; float bdown;
    theFit->Draw("SAME");
    theFit->SetLineColor(2);

    canvas->SaveAs(outNaming.c_str());

    if (denum.find("Eta") < 140 or denum.find("Pt") < 140){
       hist2D_lep->SetBinContent(WP, 5, aup);
       hist2D_lep->SetBinContent(WP, 7, bup);
       hist2D_lep->SetBinContent(WP, 9, adown);
       hist2D_lep->SetBinContent(WP, 11, bdown);
    }

    TFile *FR_H = new TFile("FitHistograms_FR.root", "UPDATE");
    FR_H->cd();
    TGraph_FR->SetName(TString(num) + "_" + TString(denum));
    TGraph_FR->Write();
    FR_H->Close();

    return theFit;
}

void Fit_FFclosure_et() {

    gStyle->SetOptFit(1111);

    TFile *FR_File = new TFile("FF_corrections_1.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 0;
    Double_t fMax = 300;

    TF1* m11 = M_FR(1, "Line2Par", "files_corr1FF_et/DataSub.root", "et_0jet_qcd_iso", "et_0jet_qcd_anti", "closure_mvis_et_qcd", Fit_Value_tau, fMin, fMax);
    TF1* m12 = M_FR(2, "Line2Par", "files_corr1FF_et/DataSub.root", "et_0SSloose_qcd_iso", "et_0SSloose_qcd_anti", "closure_mvis_et_qcdSSloose", Fit_Value_tau, fMin, fMax);
    TF1* m13 = M_FR(3, "Line2Par", "files_corr1FF_et/DataSub.root", "et_0jet_w_iso", "et_0jet_w_anti", "closure_mvis_et_w", Fit_Value_tau, fMin, fMax);
    TF1* m15 = M_FR(5, "Line2Par", "files_corr1FF_et/DataSub.root", "et_0jet_tt_iso", "et_0jet_tt_anti", "closure_mvis_et_tt", Fit_Value_tau, fMin, fMax);
    TF1* m17 = M_FR(7, "Line2Par", "files_corr1FF_et/WMC.root", "et_0jet_w_iso/WMC", "et_0jet_w_anti/WMC", "closure_mvis_et_wmc", Fit_Value_tau, fMin, fMax);
    TF1* m18 = M_FR(8, "Line2Par", "files_corr1FF_et/TTMC.root", "et_0jet_tt_iso/TTMCJ", "et_0jet_tt_anti/TTMCJ", "closure_mvis_et_ttmc", Fit_Value_tau, fMin, fMax);

    
    FR_File->Write();
    FR_File->cd();
    m11->SetName("closure_mvis_et_qcd"); m11->Write();
    m12->SetName("closure_mvis_et_qcdloose"); m12->Write();
    m13->SetName("closure_mvis_et_w"); m13->Write();
    m15->SetName("closure_mvis_et_tt"); m15->Write();
    m17->SetName("closure_mvis_et_wmc"); m17->Write();
    m18->SetName("closure_mvis_et_ttmc"); m17->Write();
    FR_File->Close();
}

