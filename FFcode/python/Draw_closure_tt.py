#!/usr/bin/env python
import ROOT
import re
from array import array
import argparse

def add_lumi(datayear):
    lowX=0.58
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    if datayear=="2018":
       lumi.AddText("2018, 59.5 fb^{-1} (13 TeV)")
    elif datayear=="2017":
       lumi.AddText("2017, 41.5 fb^{-1} (13 TeV)")
    elif datayear=="2016":
       lumi.AddText("2016, 35.9 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.05)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS Preliminary")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.45, 0.64, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

def Draw_closure_tt(year):

   ROOT.gStyle.SetFrameLineWidth(3)
   ROOT.gStyle.SetLineWidth(3)
   ROOT.gStyle.SetOptStat(0)
   
   c=ROOT.TCanvas("canvas","",0,0,600,600)
   c.cd()
   
   
   adapt=ROOT.gROOT.GetColor(12)
   new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
   trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)
   
   
   categories=["tt_0jet_qcd_mvis_iso","tt_0jet_qcd_mvis_anti","tt_0jet_qcd_tau1pt_iso","tt_0jet_qcd_tau1pt_anti","tt_0jet_qcd_tau2pt_iso","tt_0jet_qcd_tau2pt_anti","tt_0jet_qcd_met_iso","tt_0jet_qcd_met_anti","tt_0SSloose_qcd_mvis_iso","tt_0SSloose_qcd_mvis_anti","tt_0SSloose_qcd_tau1pt_iso","tt_0SSloose_qcd_tau1pt_anti","tt_0SSloose_qcd_tau2pt_iso","tt_0SSloose_qcd_tau2pt_anti","tt_0SSloose_qcd_met_iso","tt_0SSloose_qcd_met_anti"]
   ncat=16
   file=ROOT.TFile("mvisclosure_tt.root","r")
   
   for i in range (0,ncat/2):
      Data=file.Get(categories[2*i]).Get("data_obs")
      TT=file.Get(categories[2*i]).Get("TTLT")
      VV=file.Get(categories[2*i]).Get("STLT")
      DY=file.Get(categories[2*i]).Get("DYLT")
      TTJ=file.Get(categories[2*i]).Get("TTJ")
      VVJ=file.Get(categories[2*i]).Get("STJ")
      DYJ=file.Get(categories[2*i]).Get("DYJ")
   
      DataA=file.Get(categories[2*i+1]).Get("data_obs")
      TTA=file.Get(categories[2*i+1]).Get("TTLT")
      VVA=file.Get(categories[2*i+1]).Get("STLT")
      DYA=file.Get(categories[2*i+1]).Get("DYLT")
      TTJA=file.Get(categories[2*i+1]).Get("TTJ")
      VVJA=file.Get(categories[2*i+1]).Get("STJ")
      DYJA=file.Get(categories[2*i+1]).Get("DYJ")
   
      Data.Add(TT,-1)
      Data.Add(TTJ,-1)
      Data.Add(VV,-1)
      Data.Add(VVJ,-1)
      Data.Add(DY,-1)
      Data.Add(DYJ,-1)
   
      DataA.Add(TTA,-1)
      DataA.Add(TTJA,-1)
      DataA.Add(VVA,-1)
      DataA.Add(VVJA,-1)
      DataA.Add(DYA,-1)
      DataA.Add(DYJA,-1)
   
      Data.GetXaxis().SetTitle("")
      Data.GetXaxis().SetTitleSize(0)
      Data.GetXaxis().SetNdivisions(505)
      Data.GetYaxis().SetLabelFont(42)
      Data.GetYaxis().SetLabelOffset(0.01)
      Data.GetYaxis().SetLabelSize(0.06)
      Data.GetYaxis().SetTitleSize(0.075)
      Data.GetYaxis().SetTitleOffset(1.18)
      Data.SetTitle("")
      Data.GetYaxis().SetTitle("Events/bin")
   
      DataA.SetFillColor(ROOT.TColor.GetColor("#12cadd"))
   
      Data.SetMarkerStyle(20)
      Data.SetMarkerSize(1)
      Data.SetLineColor(1)
      Data.SetLineWidth(2)
   
      errorBand = DataA.Clone()
      errorBand.SetMarkerSize(0)
      errorBand.SetFillColor(new_idx)
      errorBand.SetFillStyle(3001)
      errorBand.SetLineWidth(1)
   
      pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
      pad1.Draw()
      pad1.cd()
      pad1.SetFillColor(0)
      pad1.SetBorderMode(0)
      pad1.SetBorderSize(10)
      pad1.SetTickx(1)
      pad1.SetTicky(1)
      pad1.SetLeftMargin(0.18)
      pad1.SetRightMargin(0.05)
      pad1.SetTopMargin(0.122)
      pad1.SetBottomMargin(0.026)
      pad1.SetFrameFillStyle(0)
      pad1.SetFrameLineStyle(0)
      pad1.SetFrameLineWidth(3)
      pad1.SetFrameBorderMode(0)
      pad1.SetFrameBorderSize(10)
   
      Data.GetXaxis().SetLabelSize(0)
      Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
      Data.SetMinimum(0.1)
      Data.Draw("e")
      DataA.Draw("histsame")
      errorBand.Draw("e2same")
      Data.Draw("esame")
   
      legende=make_legend()
      legende.AddEntry(Data,"Observed","elp")
      legende.AddEntry(DataA,"Predicted","f")
      legende.AddEntry(errorBand,"Stat. unc.","f")
      legende.Draw()
   
      l1=add_lumi(year)
      l1.Draw("same")
      l2=add_CMS()
      l2.Draw("same")
      l3=add_Preliminary()
    
      pad1.RedrawAxis()
   
      c.cd()
      pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
      pad2.SetTopMargin(0.05);
      pad2.SetBottomMargin(0.35);
      pad2.SetLeftMargin(0.18);
      pad2.SetRightMargin(0.05);
      pad2.SetTickx(1)
      pad2.SetTicky(1)
      pad2.SetFrameLineWidth(3)
      pad2.SetGridx()
      pad2.SetGridy()
      pad2.Draw()
      pad2.cd()
      h1=Data.Clone()
      h1.SetMaximum(2.0)#FIXME(1.5)
      h1.SetMinimum(0.0)#FIXME(0.5)
      h1.SetMarkerStyle(20)
      h3=errorBand.Clone()
      hwoE=errorBand.Clone()
      for iii in range (1,hwoE.GetSize()-2):
        hwoE.SetBinError(iii,0)
      h3.Sumw2()
      h1.Sumw2()
      h1.SetStats(0)
      h1.Divide(hwoE)
      h3.Divide(hwoE)
      h1.GetXaxis().SetTitle("Bin number")
      h1.GetXaxis().SetTitle("#tau_{h} p_{T} (GeV)")
      h1.GetXaxis().SetLabelSize(0.08)
      h1.GetYaxis().SetLabelSize(0.08)
      h1.GetYaxis().SetTitle("Obs./Exp.")
      h1.GetXaxis().SetNdivisions(505)
      h1.GetYaxis().SetNdivisions(5)
   
      h1.GetXaxis().SetTitleSize(0.15)
      h1.GetYaxis().SetTitleSize(0.15)
      h1.GetYaxis().SetTitleOffset(0.56)
      h1.GetXaxis().SetTitleOffset(1.04)
      h1.GetXaxis().SetLabelSize(0.11)
      h1.GetYaxis().SetLabelSize(0.11)
      h1.GetXaxis().SetTitleFont(42)
      h1.GetYaxis().SetTitleFont(42)
   
      h1.Draw("e0p")
      h3.Draw("e2same")
   
      c.cd()
      pad1.Draw()
   
      ROOT.gPad.RedrawAxis()
   
      c.Modified()
      c.SaveAs("closure_compa_"+categories[2*i]+".pdf")
   
