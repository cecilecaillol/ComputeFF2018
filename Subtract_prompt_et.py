import ROOT
import re
from array import array
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--directory', default="files_rawFF_et", help="Which TES?")
options = parser.parse_args()

fileData=ROOT.TFile(options.directory+"/Data.root","r") #Data histogram
fileVV=ROOT.TFile(options.directory+"/VV.root","r") #MC histogram with real leptons
fileDY=ROOT.TFile(options.directory+"/DY.root","r") #MC histogram with real leptons
fileTT=ROOT.TFile(options.directory+"/TT.root","r") #MC histogram with real leptons
fileW=ROOT.TFile(options.directory+"/W.root","r") #MC histogram with real leptons
fileDataSub=ROOT.TFile(options.directory+"/DataSub.root","recreate") #Data without real leptons

dir_qcd=["et_0jet_qcd_anti","et_0jet_qcd_iso","et_0SSloose_qcd_anti","et_0SSloose_qcd_iso","et_1jet_qcd_anti","et_1jet_qcd_iso","et_1SSloose_qcd_anti","et_1SSloose_qcd_iso"]
ncat_qcd=8

if "corr1" in options.directory:
  ncat_qcd=4

if "OSSSSF" in options.directory:
  ncat_qcd=2

for i in range (0,ncat_qcd):
   Data=fileData.Get(dir_qcd[i]).Get("data_obs")
   Data.Add(fileVV.Get(dir_qcd[i]).Get("VVLT"),-1.0)
   Data.Add(fileVV.Get(dir_qcd[i]).Get("VVJ"),-1.0)
   Data.Add(fileW.Get(dir_qcd[i]).Get("W"),-1.0)
   Data.Add(fileTT.Get(dir_qcd[i]).Get("TTJ"),-1.0)
   Data.Add(fileTT.Get(dir_qcd[i]).Get("TTLT"),-1.0)
   Data.Add(fileDY.Get(dir_qcd[i]).Get("DYJ"),-1.0)
   Data.Add(fileDY.Get(dir_qcd[i]).Get("DYLT"),-1.0)
   Data.SetName(dir_qcd[i])
   for k in range(1,Data.GetSize()-1):
     if Data.GetBinContent(k)<0:
	Data.SetBinContent(k,0)
   fileDataSub.cd()
   Data.Write()


dir_w=["et_0jet_w_anti","et_0jet_w_iso","et_1jet_w_anti","et_1jet_w_iso"]
ncat_w=4
if "corr1" in options.directory:
  ncat_w=2
if "OSSSSF" in options.directory:
  ncat_w=0

for i in range (0,ncat_w):
   Data=fileData.Get(dir_w[i]).Get("data_obs")
   Data.Add(fileVV.Get(dir_w[i]).Get("VVLT"),-1.0)
   Data.Add(fileVV.Get(dir_w[i]).Get("VVJ"),-1.0)
   Data.Add(fileTT.Get(dir_w[i]).Get("TTJ"),-1.0)
   Data.Add(fileTT.Get(dir_w[i]).Get("TTLT"),-1.0)
   Data.Add(fileDY.Get(dir_w[i]).Get("DYJ"),-1.0)
   Data.Add(fileDY.Get(dir_w[i]).Get("DYLT"),-1.0)
   Data.SetName(dir_w[i])
   for k in range(1,Data.GetSize()-1):
     if Data.GetBinContent(k)<0:
        Data.SetBinContent(k,0)
   fileDataSub.cd()
   Data.Write()

dir_tt=["et_0jet_tt_anti","et_0jet_tt_iso"]
ncat_tt=2
if "OSSSSF" in options.directory:
  ncat_tt=0
for i in range (0,ncat_tt):
   Data=fileData.Get(dir_tt[i]).Get("data_obs")
   Data.Add(fileVV.Get(dir_tt[i]).Get("VVLT"),-1.0)
   Data.Add(fileVV.Get(dir_tt[i]).Get("VVJ"),-1.0)
   Data.Add(fileW.Get(dir_tt[i]).Get("W"),-1.0)
   Data.Add(fileTT.Get(dir_tt[i]).Get("TTLT"),-1.0)
   Data.Add(fileDY.Get(dir_tt[i]).Get("DYJ"),-1.0)
   Data.Add(fileDY.Get(dir_tt[i]).Get("DYLT"),-1.0)
   Data.SetName(dir_tt[i])
   for k in range(1,Data.GetSize()-1):
     if Data.GetBinContent(k)<0:
        Data.SetBinContent(k,0)
   fileDataSub.cd()
   Data.Write()
