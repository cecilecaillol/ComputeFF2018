#!/usr/bin/env python
import ROOT
import re
from array import array
import argparse


def Make_2Dmaps(directory,channel):
  fileData=ROOT.TFile(directory+"/Data.root","r") #Data histogram
  fileVV=ROOT.TFile(directory+"/VV.root","r") #MC histogram with real leptons
  fileDY=ROOT.TFile(directory+"/DY.root","r") #MC histogram with real leptons
  fileTT=ROOT.TFile(directory+"/TT.root","r") #MC histogram with real leptons
  fileW=ROOT.TFile(directory+"/W.root","r") #MC histogram with real leptons
  fileDataSub=ROOT.TFile("FFmap.root","recreate") #Data without real leptons

  dir_qcd=[channel+"_cat1_qcd",channel+"_cat2_qcd"]
  ncat_qcd=2

  for i in range (0,ncat_qcd):    
    Data_iso=fileData.Get(dir_qcd[i]+"_iso").Get("data_obs")
    Data_iso.Add(fileVV.Get(dir_qcd[i]+"_iso").Get("VVLT"),-1.0)
    Data_iso.Add(fileVV.Get(dir_qcd[i]+"_iso").Get("VVJ"),-1.0)
    W_iso=fileW.Get(dir_qcd[i]+"_iso").Get("W").Clone()
    for j in range(1,W_iso.GetSize()):
      W_iso.SetBinError(j,(W_iso.GetBinError(j)*W_iso.GetBinError(j)+0.20*0.20*W_iso.GetBinContent(j)*W_iso.GetBinContent(j))**0.5)
    Data_iso.Add(W_iso,-1.0)
    Data_iso.Add(fileTT.Get(dir_qcd[i]+"_iso").Get("TTJ"),-1.0)
    Data_iso.Add(fileTT.Get(dir_qcd[i]+"_iso").Get("TTLT"),-1.0)
    Data_iso.Add(fileDY.Get(dir_qcd[i]+"_iso").Get("DYJ"),-1.0)
    DYLT_iso=fileDY.Get(dir_qcd[i]+"_iso").Get("DYLT").Clone()
    for j in range(1,DYLT_iso.GetSize()):
      DYLT_iso.SetBinError(j,(DYLT_iso.GetBinError(j)*DYLT_iso.GetBinError(j)+0.10*0.10*DYLT_iso.GetBinContent(j)*DYLT_iso.GetBinContent(j))**0.5)
    Data_iso.Add(DYLT_iso,-1.0)
    Data_iso.SetName(dir_qcd[i])
    for k in range(1,Data_iso.GetSize()-1):
      if Data_iso.GetBinContent(k)<0:
        Data_iso.SetBinContent(k,0)

    Data_anti=fileData.Get(dir_qcd[i]+"_anti").Get("data_obs")
    Data_anti.Add(fileVV.Get(dir_qcd[i]+"_anti").Get("VVLT"),-1.0)
    Data_anti.Add(fileVV.Get(dir_qcd[i]+"_anti").Get("VVJ"),-1.0)
    W_anti=fileW.Get(dir_qcd[i]+"_anti").Get("W").Clone()
    for j in range(1,W_anti.GetSize()):
      W_anti.SetBinError(j,(W_anti.GetBinError(j)*W_anti.GetBinError(j)+0.20*0.20*W_anti.GetBinContent(j)*W_anti.GetBinContent(j))**0.5)
    Data_anti.Add(W_anti,-1.0)
    Data_anti.Add(fileTT.Get(dir_qcd[i]+"_anti").Get("TTJ"),-1.0)
    Data_anti.Add(fileTT.Get(dir_qcd[i]+"_anti").Get("TTLT"),-1.0)
    Data_anti.Add(fileDY.Get(dir_qcd[i]+"_anti").Get("DYJ"),-1.0)
    DYLT_anti=fileDY.Get(dir_qcd[i]+"_anti").Get("DYLT").Clone()
    for j in range(1,DYLT_anti.GetSize()):
      DYLT_anti.SetBinError(j,(DYLT_anti.GetBinError(j)*DYLT_anti.GetBinError(j)+0.10*0.10*DYLT_anti.GetBinContent(j)*DYLT_anti.GetBinContent(j))**0.5)
    Data_anti.Add(DYLT_anti,-1.0)
    for k in range(1,Data_anti.GetSize()-1):
      if Data_anti.GetBinContent(k)<0:
        Data_anti.SetBinContent(k,0)

    fileDataSub.cd()
    Data_iso.Divide(Data_anti)
    Data_iso.Write()


  dir_w=[channel+"_cat1_w",channel+"_cat2_w"]
  ncat_w=2

  for i in range (0,ncat_w):
    Data_iso=fileData.Get(dir_w[i]+"_iso").Get("data_obs")
    Data_iso.Add(fileVV.Get(dir_w[i]+"_iso").Get("VVLT"),-1.0)
    Data_iso.Add(fileVV.Get(dir_w[i]+"_iso").Get("VVJ"),-1.0)
    Data_iso.Add(fileTT.Get(dir_w[i]+"_iso").Get("TTJ"),-1.0)
    Data_iso.Add(fileTT.Get(dir_w[i]+"_iso").Get("TTLT"),-1.0)
    Data_iso.Add(fileDY.Get(dir_w[i]+"_iso").Get("DYJ"),-1.0)
    DYLT_iso=fileDY.Get(dir_w[i]+"_iso").Get("DYLT").Clone()
    for j in range(1,DYLT_iso.GetSize()):
      DYLT_iso.SetBinError(j,(DYLT_iso.GetBinError(j)*DYLT_iso.GetBinError(j)+0.10*0.10*DYLT_iso.GetBinContent(j)*DYLT_iso.GetBinContent(j))**0.5)
    Data_iso.Add(DYLT_iso,-1.0)
    Data_iso.SetName(dir_w[i])
    for k in range(1,Data_iso.GetSize()-1):
      if Data_iso.GetBinContent(k)<0:
        Data_iso.SetBinContent(k,0)

    Data_anti=fileData.Get(dir_w[i]+"_anti").Get("data_obs")
    Data_anti.Add(fileVV.Get(dir_w[i]+"_anti").Get("VVLT"),-1.0)
    Data_anti.Add(fileVV.Get(dir_w[i]+"_anti").Get("VVJ"),-1.0)
    Data_anti.Add(fileTT.Get(dir_w[i]+"_anti").Get("TTJ"),-1.0)
    Data_anti.Add(fileTT.Get(dir_w[i]+"_anti").Get("TTLT"),-1.0)
    Data_anti.Add(fileDY.Get(dir_w[i]+"_anti").Get("DYJ"),-1.0)
    DYLT_anti=fileDY.Get(dir_w[i]+"_anti").Get("DYLT").Clone()
    for j in range(1,DYLT_anti.GetSize()):
      DYLT_anti.SetBinError(j,(DYLT_anti.GetBinError(j)*DYLT_anti.GetBinError(j)+0.10*0.10*DYLT_anti.GetBinContent(j)*DYLT_anti.GetBinContent(j))**0.5)
    Data_anti.Add(DYLT_anti,-1.0)
    for k in range(1,Data_anti.GetSize()-1):
      if Data_anti.GetBinContent(k)<0:
        Data_anti.SetBinContent(k,0)


    fileDataSub.cd()
    Data_iso.Divide(Data_anti)
    Data_iso.Write()

