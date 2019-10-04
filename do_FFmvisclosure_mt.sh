#!/usr/bin/env bash
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DataA.root files_corr1FF_mt/DataA.root data_obs data_obs 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DataB.root files_corr1FF_mt/DataB.root data_obs data_obs 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DataC.root files_corr1FF_mt/DataC.root data_obs data_obs 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DataD.root files_corr1FF_mt/DataD.root data_obs data_obs 2018
hadd -f files_corr1FF_mt/Data.root files_corr1FF_mt/DataA.root files_corr1FF_mt/DataB.root files_corr1FF_mt/DataC.root files_corr1FF_mt/DataD.root
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DY.root files_corr1FF_mt/DYincl.root DY DY 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DY1.root files_corr1FF_mt/DY1.root DY DY 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DY2.root files_corr1FF_mt/DY2.root DY DY 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DY3.root files_corr1FF_mt/DY3.root DY DY 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/DY4.root files_corr1FF_mt/DY4.root DY DY 2018
hadd -f files_corr1FF_mt/DY.root files_corr1FF_mt/DYincl.root files_corr1FF_mt/DY1.root files_corr1FF_mt/DY2.root files_corr1FF_mt/DY3.root files_corr1FF_mt/DY4.root
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/Wall.root files_corr1FF_mt/W.root W W 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/Wall.root files_corr1FF_mt/WMC.root W WMC 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTToHadronic.root files_corr1FF_mt/TTToHadronic.root TTToHadronic TT 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTTo2L2Nu.root files_corr1FF_mt/TTTo2L2Nu.root TTTo2L2Nu TT 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTToSemiLeptonic.root files_corr1FF_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 2018
hadd -f files_corr1FF_mt/TT.root files_corr1FF_mt/TTToHadronic.root files_corr1FF_mt/TTTo2L2Nu.root files_corr1FF_mt/TTToSemiLeptonic.root
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTToHadronic.root files_corr1FF_mt/TTToHadronicMC.root TTToHadronic TTMC 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTTo2L2Nu.root files_corr1FF_mt/TTTo2L2NuMC.root TTTo2L2Nu TTMC 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/TTToSemiLeptonic.root files_corr1FF_mt/TTToSemiLeptonicMC.root TTToSemiLeptonic TTMC 2018
hadd -f files_corr1FF_mt/TTMC.root files_corr1FF_mt/TTToHadronicMC.root files_corr1FF_mt/TTTo2L2NuMC.root files_corr1FF_mt/TTToSemiLeptonicMC.root
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/WW.root files_corr1FF_mt/WW.root WW VV 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/WZ.root files_corr1FF_mt/WZ.root WZ VV 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/ZZ.root files_corr1FF_mt/ZZ.root ZZ VV 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/ST_t_antitop.root files_corr1FF_mt/ST_t_antitop.root ST_t_antitop ST 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/ST_t_top.root files_corr1FF_mt/ST_t_top.root ST_t_top ST 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/ST_tW_antitop.root files_corr1FF_mt/ST_tW_antitop.root ST_tW_antitop ST 2018
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/ST_tW_top.root files_corr1FF_mt/ST_tW_top.root ST_tW_top ST 2018
hadd -f files_corr1FF_mt/VV.root files_corr1FF_mt/WW.root files_corr1FF_mt/WZ.root files_corr1FF_mt/ZZ.root files_corr1FF_mt/ST_t_antitop.root files_corr1FF_mt/ST_t_top.root files_corr1FF_mt/ST_tW_antitop.root files_corr1FF_mt/ST_tW_top.root

Subtract_prompt_mt.py --directory files_corr1FF_mt
root -l -b -q 'Fit_FFclosure_mt.cc(2018)'

# Prepare mT histograms, fit the ratio later with the OS/SS correction
Set1_correction_mt /data/ccaillol/smhmt2018_svfitted_30sep/Wall.root files_corr1FF_mt/WMC2.root W WMC2 2018

hadd -f mvisclosure_mt.root files_corr1FF_mt/Data.root files_corr1FF_mt/DY.root files_corr1FF_mt/W.root files_corr1FF_mt/TT.root files_corr1FF_mt/VV.root 
