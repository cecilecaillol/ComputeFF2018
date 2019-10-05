#!/usr/bin/env python

import argparse
import os
import ComputeFF2018.FFcode.RawFF as RawFF
import ComputeFF2018.FFcode.FFmvisclosure as FFmvisclosure
import ComputeFF2018.FFcode.FFOSSScorrection as FFOSSScorrection
import ComputeFF2018.FFcode.Draw_raw as Draw_raw

parser = argparse.ArgumentParser(description="Master fake factor making script")
parser.add_argument('--channel','-c',nargs="?",choices=['mt','et'],help="Which channel?",required=True)
parser.add_argument('--year','-y',nargs="?",choices=["2016","2017","2018"],help="Which year?",required=True)

args = parser.parse_args()

if not os.path.isdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/plots_"+args.channel+"_"+args.year):
    os.mkdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/plots_"+args.channel+"_"+args.year)

if not os.path.isdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_corrOSSSFF_"+args.channel):
    os.mkdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_corrOSSSFF_"+args.channel)
if not os.path.isdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_rawFF_"+args.channel):
    os.mkdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_rawFF_"+args.channel)
if not os.path.isdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_corr1FF_"+args.channel):
    os.mkdir(os.environ['CMSSW_BASE']+"/src/ComputeFF2018/files_corr1FF_"+args.channel)

RawFF.RawFF(args)
FFmvisclosure.FFmvisclosure(args)
FFOSSScorrection.FFOSSScorrection(args)

Draw_raw.Draw_raw("raw",args.year,args.channel)
Draw_raw.Draw_raw("mvisclosure",args.year,args.channel)
Draw_raw.Draw_raw("osss",args.year,args.channel)

os.system("mv *.pdf plots_"+args.channel+"_"+args.year)

finalPath = os.environ['CMSSW_BASE']+"/src/ComputeFF2018/ff_files_"+args.channel+"_"+args.year
if not os.path.isdir(finalPath):
    os.mkdir(finalPath)
os.system("cp uncorrected_fakefactors_"+args.channel+".root "+finalPath)
os.system("cp FF_corrections_1.root "+finalPath)
os.system("cp FF_QCDcorrectionOSSS.root "+finalPath)
os.system("cp raw_FF_"+args.channel+".root "+finalPath)
os.system("cp mvisclosure_"+args.channel+".root "+finalPath)
os.system("cp OSSScorr_"+args.channel+".root "+finalPath)
