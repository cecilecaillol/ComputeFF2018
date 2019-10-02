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
    return par[0] + par[1] * x[0] ;//+ par[2] * x[0]* x[0] + par[3] * x[0]* x[0] *x[0];
    //return par[0] + par[1]*(TMath::Exp(par[2] * x[0]-par[3]));
    //return par[0] + par[1]*(TMath::Landau((x[0]-30),par[2],par[3],0));
}

Double_t fitFunc_Landau(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau((x[0]-30),par[2],par[3],0));
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, std::string name, TH2F * hist2D_lep, Double_t fMin, Double_t fMax, int year) {
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

    int nPar = 4; // number of parameters in the fit

    TF1 * theFit = new TF1("theFit", fitFunc_Landau, fMin, fMax, nPar);
    TF1 * theFit2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);

    theFit->SetParameter(0, 0.05);
    theFit->SetParameter(1, 0.5);
    theFit->SetParameter(2, 8);
    theFit->SetParameter(3, 5);

    theFit2->SetParameter(0, 0.09);
    theFit2->SetParameter(1, 0.0);

    float xAxisMax = 500;
    if (type.find("Line2P") < 140)
      TGraph_FR->Fit("theFit2", "R0");
    else 
      TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    //TGraph_FR->GetYaxis()->SetRangeUser(0.00,1.5*yg[0]);
    TGraph_FR->GetYaxis()->SetRangeUser(0.00,0.30);
    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(30, 100);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "fit_" + name + ".pdf";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    if (year==2016) t.DrawLatex(0.55, .96, "35.9 fb^{-1} (2016, 13 TeV)");
    else if (year==2017) t.DrawLatex(0.55, .96, "41.5 fb^{-1} (2017, 13 TeV)");
    else if (year==2018) t.DrawLatex(0.55, .96, "59.5 fb^{-1} (2018, 13 TeV)");
    float aup; float adown; float bup; float bdown;
    if (type.find("Line2P") < 140){
       theFit2->Draw("SAME");
       theFit2->SetLineColor(2);
    }
    else {
       theFit->Draw("SAME");
       theFit->SetLineColor(2);
    }

 /*      std::string lepName="";
       TLatex t3 = TLatex();
       t3.SetNDC();
       t3.SetTextFont(42);
       t3.SetTextAlign(12);
       t3.SetTextSize(0.040);
       std::string region;

       Double_t TauLegParameters[nPar];
       theFit->GetParameters(TauLegParameters);

       for (int i = 0; i < nPar; i++) {
           hist2D_lep->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
           hist2D_lep->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
       }

       Double_t matrix[2][2];
       gMinuit->mnemat(&matrix[0][0],2);
       TMatrixD mat_D(2,2);
        for (int i=0; i<2; ++i){
           for (int j=0; j<2; ++j){
           	mat_D[i][j]=matrix[i][j];
           }
       }*/

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

   if (type.find("Line2P") < 140)  return theFit2;
   else return theFit;
}

void Fit_FF_mt(int year) {

    gStyle->SetOptFit(1111);

    TFile *FR_File = new TFile("uncorrected_fakefactors_mt.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 0;
    Double_t fMax = 300;

    TF1* m11 = M_FR(1, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_0jet_qcd_iso", "mt_0jet_qcd_anti", "mt_0jet_qcd_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m12 = M_FR(2, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_1jet_qcd_iso", "mt_1jet_qcd_anti", "mt_1jet_qcd_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m13 = M_FR(3, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_0jet_w_iso", "mt_0jet_w_anti", "mt_0jet_w_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m14 = M_FR(4, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_1jet_w_iso", "mt_1jet_w_anti", "mt_1jet_w_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m15 = M_FR(5, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_0jet_tt_iso", "mt_0jet_tt_anti", "mt_0jet_tt_iso", Fit_Value_tau, fMin, fMax, year);

    TF1* m16 = M_FR(6, "Line2Par", "files_rawFF_mt/W.root", "mt_0jet_w_iso/W", "mt_0jet_w_anti/W", "W_mc_mt_0jet_w_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m17 = M_FR(7, "Line2Par", "files_rawFF_mt/W.root", "mt_1jet_w_iso/W", "mt_1jet_w_anti/W", "W_mc_mt_1jet_w_iso", Fit_Value_tau, fMin, fMax, year);


    TF1* m18 = M_FR(8, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_0SSloose_qcd_iso", "mt_0SSloose_qcd_anti", "mt_0jetSSloose_qcd_iso", Fit_Value_tau, fMin, fMax, year);
    TF1* m19 = M_FR(9, "Line2Par", "files_rawFF_mt/DataSub.root", "mt_1SSloose_qcd_iso", "mt_1SSloose_qcd_anti", "mt_1jetSSloose_qcd_iso", Fit_Value_tau, fMin, fMax, year);

    TF1* m20 = M_FR(11, "Line2Par", "files_rawFF_mt/TT.root", "mt_0jet_tt_iso/TTJ", "mt_0jet_tt_anti/TTJ", "TT_mc_mt_0jet_tt_iso", Fit_Value_tau, fMin, fMax, year);
    
    FR_File->Write();
    FR_File->cd();
    m11->SetName("rawFF_mt_qcd_0jet"); m11->Write();
    m12->SetName("rawFF_mt_qcd_1jet"); m12->Write();
    m13->SetName("rawFF_mt_w_0jet"); m13->Write();
    m14->SetName("rawFF_mt_w_1jet"); m14->Write();
    m15->SetName("rawFF_mt_tt"); m15->Write();
    m16->SetName("mc_rawFF_mt_w_0jet"); m16->Write();
    m17->SetName("mc_rawFF_mt_w_1jet"); m17->Write();
    m18->SetName("rawFF_mt_qcd_0jetSSloose"); m18->Write();
    m19->SetName("rawFF_mt_qcd_1jetSSloose"); m19->Write();
    m20->SetName("mc_rawFF_mt_tt"); m20->Write();
    FR_File->Close();
}

