#!/usr/bin/env python
import argparse
import os
import ComputeFF2018.FFcode.Subtract_prompt as Subtract_prompt

def FFOSSScorrection(args):
    if args.year == "2016":
        pass
    elif args.year == "2017":
        pass
    elif args.year == "2018":
        if args.channel == "mt":
            path = '/data/ccaillol/smhmt2018_svfitted_30sep/'
        if args.channel == "et":
            pass

    if args.channel == "mt":
        executable = "OSSScorrection_mt"
        outputPath = os.environ['CMSSW_BASE']+'/src/ComputeFF2018/files_corrOSSSFF_mt/'
    elif args.channel == 'et':
        executable = "Set1_correction_et"
        outputPath = os.environ['CMSSW_BASE']+'/src/ComputeFF2018/files_corrOSSSFF_et/'

    if args.year == '2018':
        commandParams = [
            [executable,path+'DataA.root',outputPath+'DataA.root','data_obs','data_obs',args.year],
            [executable,path+'DataB.root',outputPath+'DataB.root','data_obs','data_obs',args.year],
            [executable,path+'DataC.root',outputPath+'DataC.root','data_obs','data_obs',args.year],
            [executable,path+'DataD.root',outputPath+'DataD.root','data_obs','data_obs',args.year],
            [executable,path+'DY.root',outputPath+'DYincl.root','DY','DY',args.year],
            [executable,path+'DY1.root',outputPath+'DY1.root','DY','DY',args.year],
            [executable,path+'DY2.root',outputPath+'DY2.root','DY','DY',args.year],
            [executable,path+'DY3.root',outputPath+'DY3.root','DY','DY',args.year],
            [executable,path+'DY4.root',outputPath+'DY4.root','DY','DY',args.year],
            [executable,path+'Wall.root',outputPath+'W.root','W','W',args.year],
            [executable,path+'Wall.root',outputPath+'WMC.root','W','WMC',args.year],
            [executable,path+'TTToHadronic.root',outputPath+'TTToHadronic.root','TTToHadronic','TT',args.year],
            [executable,path+'TTTo2L2Nu.root',outputPath+'TTTo2L2Nu.root',' TTTo2L2Nu','TT',args.year],
            [executable,path+'TTToSemiLeptonic.root',outputPath+'TTToSemiLeptonic.root','TTToSemiLeptonic','TT',args.year],            
            [executable,path+'WW.root',outputPath+'WW.root','WW','VV',args.year],
            [executable,path+'WZ.root',outputPath+'WZ.root','WZ','VV',args.year],
            [executable,path+'ZZ.root',outputPath+'ZZ.root','ZZ','VV',args.year],
            [executable,path+'ST_t_antitop.root',outputPath+'ST_t_antitop.root','ST_t_antitop','ST',args.year],
            [executable,path+'ST_t_top.root',outputPath+'ST_t_top.root','ST_t_top','ST',args.year],
            [executable,path+'ST_tW_antitop.root',outputPath+'ST_tW_antitop.root','ST_tW_antitop','ST',args.year],
            [executable,path+'ST_tW_top.root',outputPath+'ST_tW_top.root','ST_tW_top','ST',args.year],
            [executable,path+'Wall.root',outputPath+'WMC2.root','W','WMC',args.year],
        ]
        haddFiles = {
            "Data.root": [outputPath+"DataA.root",outputPath+"DataB.root",outputPath+"DataC.root",outputPath+"DataD.root"],
            "DY.root": [outputPath+"DY.root",outputPath+"DY1.root",outputPath+"DY2.root",outputPath+"DY3.root",outputPath+"DY4.root"],
            "TT.root": [outputPath+"TTToHadronic.root",outputPath+"TTToSemiLeptonic.root",outputPath+"TTTo2L2Nu.root"],            
            "VV.root": [outputPath+"WW.root",outputPath+"WZ.root",outputPath+"ZZ.root",outputPath+"ST_t_antitop.root",outputPath+"ST_t_top.root",outputPath+"ST_tW_antitop.root",outputPath+"ST_tW_top.root"]
        }
    #Run all sets
    for command in commandParams:
        commandString = ''
        for element in command:
            commandString+=element+' '
        os.system(commandString)
    #hadd them
    for haddedFile in haddFiles:
        haddCommand = "hadd -f "+outputPath+haddedFile+' '
        for inputFile in haddFiles[haddedFile]:
            haddCommand+=inputFile+' '
        os.system(haddCommand)
    #do our subtractions, and our fitting.
    Subtract_prompt.Subtract_prompt(outputPath,args.channel)
    os.system("root -l -b -q \'Fit_FFOSSS_"+args.channel+".cc("+args.year+")\'")
    #make the final mvisclosure file
    finalMvisClosureCommand = "hadd -f OSSScorr_"+args.channel+".root "
    finalMvisClosureCommand+=outputPath+"Data.root "
    finalMvisClosureCommand+=outputPath+"DY.root "
    finalMvisClosureCommand+=outputPath+"W.root "
    finalMvisClosureCommand+=outputPath+"TT.root "
    finalMvisClosureCommand+=outputPath+"VV.root "
    os.system(finalMvisClosureCommand)

if __name__=="__main__":
    parser = argparse.ArgumentParser(description="Master fake factor making script")
    parser.add_argument('--channel','-c',nargs="?",choices=['mt','et'],help="Which channel?",required=True)
    parser.add_argument('--year','-y',nargs="?",choices=["2016","2017","2018"],help="Which year?",required=True)

    args=parser.parse_args()
    FFOSSScorrection(args)
