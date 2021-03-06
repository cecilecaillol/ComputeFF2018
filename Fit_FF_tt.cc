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
    return par[0] + par[1]*(TMath::Exp(par[2] * (x[0]-par[3])));
    //return par[0] + par[1] *(x[0]-80);
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * (x[0]-40) ;//+ par[2] * x[0]* x[0] + par[3] * x[0]* x[0] *x[0];
    //return par[0] + par[1]*(TMath::Exp(par[2] * x[0]-par[3]));
    //return par[0] + par[1]*(TMath::Landau((x[0]-30),par[2],par[3],0));
}

Double_t fitFunc_Landau(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau((x[0]),par[2],par[3],0));
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, std::string name, TH2F * hist2D_lep, Double_t fMin, Double_t fMax, int year) {
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
    TF1 * theFit3 = new TF1("theFit3", fitFunc_Exp3Par, fMin, fMax, 4);

    theFit->SetParameter(0, 0.15);
    theFit->SetParameter(1, 0.3);
    theFit->SetParameter(2, 70);
    theFit->SetParameter(3, 21);

    if (year==2017 and name.find("0jet")<140){
      theFit->SetParameter(0, 0.20);
      theFit->SetParameter(1, 3.0);
      theFit->SetParameter(2, 11.0);
      theFit->SetParameter(3, 1.2);
    }

    if (year==2017 and name.find("1jet")<140){
      theFit->SetParameter(0, 0.15);
      theFit->SetParameter(1, 20.0);
      theFit->SetParameter(2, 10.0);
      theFit->SetParameter(3, 0.8);
    }

    if (year==2018 and name.find("1jet")<140){
      theFit->SetParameter(0, 0.184);
      theFit->SetParameter(1, -0.10);
      theFit->SetParameter(2, 1.0);
      theFit->SetParameter(3, 2.2);
    }

    /*if (year==2018 and name.find("1jet")<140){
      theFit->SetParameter(0, 0.184);
      theFit->SetParameter(1, -2.10);
      theFit->SetParameter(2, 10.0);
      theFit->SetParameter(3, 2.2);
    }*/

    theFit2->SetParameter(0, 0.20);
    theFit2->SetParameter(1, -0.00001);

    theFit3->SetParameter(0, 0.16);
    theFit3->SetParameter(1, 0.10);
    theFit3->SetParameter(2, -0.1);
    theFit3->SetParameter(3, 30.0);

    if (year==2016 and name.find("2jet")<140){
      theFit3->SetParameter(0, 0.124);
      theFit3->SetParameter(1, 0.16);
      theFit3->SetParameter(2, -0.08);
      theFit3->SetParameter(3, 24.0);
    }
    if (year==2016 and name.find("1jet")<140){
      theFit3->SetParameter(0, 0.144);
      theFit3->SetParameter(1, 0.16);
      theFit3->SetParameter(2, -0.08);
      theFit3->SetParameter(3, 24.0);
    }

    float xAxisMax = 500;
    if (type.find("Line2P") < 140)
      TGraph_FR->Fit("theFit2", "R0");
    else if (type.find("exp") < 140)
      TGraph_FR->Fit("theFit3", "R0");
    else{ 
      //TGraph_FR->Fit("theFit","","", 40,100);
      TGraph_FR->Fit("theFit", "R0");
    }

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00,0.50);
    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(40, 150);
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
    else if (year==2018) t.DrawLatex(0.55, .96, "59.7 fb^{-1} (2018, 13 TeV)");
    if (type.find("Line2P") < 140){
       theFit2->Draw("SAME");
       theFit2->SetLineColor(2);
    }
    else if (type.find("exp") < 140){
       theFit3->Draw("SAME");
       theFit3->SetLineColor(2);
    }
    else {
       theFit->Draw("SAME");
       theFit->SetLineColor(2);
    }

    Double_t TauLegParameters[4];
    theFit->GetParameters(TauLegParameters);

cout<<TauLegParameters[0]<<" "<<theFit->GetParError(0)<<" "<<TauLegParameters[1]<<endl;

//TGraph_FR->Fit("theFit2", "","",40,80);
//    theFit2->SetLineColor(kViolet+1);
//    theFit2->Draw("same");

    /*TF1 * theFitup1 = new TF1("theFitup1", fitFunc_Landau, fMin, fMax, 4);
    theFitup1->SetParameter(0, TauLegParameters[0]+0*theFit->GetParError(0));
    theFitup1->SetParameter(1, 0*TauLegParameters[1]+0*theFit->GetParError(1));
    theFitup1->SetParameter(2, TauLegParameters[2]+0*theFit->GetParError(2));
    theFitup1->SetParameter(3, 1*TauLegParameters[3]+0*theFit->GetParError(3));
    theFitup1->SetLineColor(kViolet+1);
    theFitup1->Draw("same");*/

    /*// Up and down fits
    Double_t TauLegParameters[2];
    theFit2->GetParameters(TauLegParameters);

    Double_t matrix[2][2];
    gMinuit->mnemat(&matrix[0][0],2);
    TMatrixD mat_D(2,2);
     for (int i=0; i<2; ++i){
        for (int j=0; j<2; ++j){
             mat_D[i][j]=matrix[i][j];
        }
    }
    float aup; float adown; float bup; float bdown;

    TMatrixDEigen mat_sym=TMatrixDEigen (mat_D);
    TMatrixD eigenValues=mat_sym.GetEigenValues();
    TMatrixD eigenVectors=mat_sym.GetEigenVectors();
    TMatrixD eigenVectorsInverted=mat_sym.GetEigenVectors();
    aup = TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    bup = TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    adown = TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    bdown = TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    float au1=TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bu1=TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float ad1=TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bd1=TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float au2=TauLegParameters[0]+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bu2=TauLegParameters[1]+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    float ad2=TauLegParameters[0]-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bd2=TauLegParameters[1]-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    TF1 * theFitup1 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    theFitup1->SetParameter(0, au1);
    theFitup1->SetParameter(1, bu1);
    theFitup1->SetLineColor(kViolet+1);
    theFitup1->Draw("same");
    TF1 * theFitup2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    theFitup2->SetParameter(0, au2);
    theFitup2->SetParameter(1, bu2);
    theFitup2->SetLineColor(kGreen-3);
    theFitup2->Draw("same");
    TF1 * theFitdown1 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    theFitdown1->SetParameter(0, ad1);
    theFitdown1->SetParameter(1, bd1);
    theFitdown1->SetLineColor(kViolet+1);
    theFitdown1->Draw("same");
    TF1 * theFitdown2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    theFitdown2->SetParameter(0, ad2);
    theFitdown2->SetParameter(1, bd2);
    theFitdown2->SetLineColor(kGreen-3);
    theFitdown2->Draw("same");
    TLegend *l = new TLegend(0.15, 0.74, 0.5, 0.89, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.03);
    l->SetFillColor(0);
    l->AddEntry(theFit2, "Best fit", "l");
    l->AddEntry(theFitup1, "1st uncertainty #pm 1#sigma", "l");
    l->AddEntry(theFitup2, "2nd uncertainty #pm 1#sigma", "l");
    l->Draw("same");*/

    canvas->SaveAs(outNaming.c_str());

    TFile *FR_H = new TFile("uncorrected_fakefactors_tt.root", "UPDATE");
    FR_H->cd();
    theFit->SetName(TString(name));
    theFit3->SetName(TString(name));
    if (type.find("exp") < 140) theFit3->Write();
    else theFit->Write();
    /*theFitup1->SetName(TString(name)+"_unc1_up");
    theFitup1->Write();
    theFitdown1->SetName(TString(name)+"_unc1_down");
    theFitdown1->Write();
    theFitup2->SetName(TString(name)+"_unc2_up");
    theFitup2->Write();
    theFitdown2->SetName(TString(name)+"_unc2_down");
    theFitdown2->Write();*/
    FR_H->Close();

   if (type.find("Line2P") < 140)  return theFit2;
   else return theFit;
}

void Fit_FF_tt(int year) {

    gStyle->SetOptFit(1111);

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 40;
    Double_t fMax = 1000;

    TF1* m11 = M_FR(1, "a", "files_rawFF_tt/DataSub.root", "tt_0jet_qcd_iso", "tt_0jet_qcd_anti", "rawFF_tt_qcd_0jet", Fit_Value_tau, fMin, fMax, year);
    TF1* m12 = M_FR(2, "exp", "files_rawFF_tt/DataSub.root", "tt_1jet_qcd_iso", "tt_1jet_qcd_anti", "rawFF_tt_qcd_1jet", Fit_Value_tau, fMin, fMax, year);
    TF1* m13 = M_FR(3, "exp", "files_rawFF_tt/DataSub.root", "tt_2jet_qcd_iso", "tt_2jet_qcd_anti", "rawFF_tt_qcd_2jet", Fit_Value_tau, fMin, fMax, year);

    if (year==2018){
      TF1* m17 = M_FR(7, "a", "files_rawFF_tt/DataSub.root", "tt_0SSloose_qcd_iso", "tt_0SSloose_qcd_anti", "rawFF_tt_qcd_0jetSSloose", Fit_Value_tau, fMin, fMax, year);
      TF1* m18 = M_FR(8, "a", "files_rawFF_tt/DataSub.root", "tt_1SSloose_qcd_iso", "tt_1SSloose_qcd_anti", "rawFF_tt_qcd_1jetSSloose", Fit_Value_tau, fMin, fMax, year);
    }
    else{
      TF1* m17 = M_FR(7, "exp", "files_rawFF_tt/DataSub.root", "tt_0SSloose_qcd_iso", "tt_0SSloose_qcd_anti", "rawFF_tt_qcd_0jetSSloose", Fit_Value_tau, fMin, fMax, year);
      TF1* m18 = M_FR(8, "exp", "files_rawFF_tt/DataSub.root", "tt_1SSloose_qcd_iso", "tt_1SSloose_qcd_anti", "rawFF_tt_qcd_1jetSSloose", Fit_Value_tau, fMin, fMax, year);
    }
    TF1* m19 = M_FR(9, "exp", "files_rawFF_tt/DataSub.root", "tt_2SSloose_qcd_iso", "tt_2SSloose_qcd_anti", "rawFF_tt_qcd_2jetSSloose", Fit_Value_tau, fMin, fMax, year);

    
}

