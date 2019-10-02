./Andrew_Make.sh Set1_correction_mt.cc
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataB.root files_corr1FF_mt/DataB.root data_obs data_obs 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataC.root files_corr1FF_mt/DataC.root data_obs data_obs 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataD.root files_corr1FF_mt/DataD.root data_obs data_obs 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataE.root files_corr1FF_mt/DataE.root data_obs data_obs 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataF.root files_corr1FF_mt/DataF.root data_obs data_obs 2017
hadd -f files_corr1FF_mt/Data.root files_corr1FF_mt/DataB.root files_corr1FF_mt/DataC.root files_corr1FF_mt/DataD.root files_corr1FF_mt/DataE.root files_corr1FF_mt/DataF.root
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY.root files_corr1FF_mt/DYincl.root DY DY 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY1.root files_corr1FF_mt/DY1.root DY DY 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY2.root files_corr1FF_mt/DY2.root DY DY 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY3.root files_corr1FF_mt/DY3.root DY DY 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY4.root files_corr1FF_mt/DY4.root DY DY 2017
hadd -f files_corr1FF_mt/DY.root files_corr1FF_mt/DYincl.root files_corr1FF_mt/DY1.root files_corr1FF_mt/DY2.root files_corr1FF_mt/DY3.root files_corr1FF_mt/DY4.root
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/Wall.root files_corr1FF_mt/W.root W W 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/Wall.root files_corr1FF_mt/WMC.root W WMC 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToHadronic.root files_corr1FF_mt/TTToHadronic.root TTToHadronic TT 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTTo2L2Nu.root files_corr1FF_mt/TTTo2L2Nu.root TTTo2L2Nu TT 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToSemiLeptonic.root files_corr1FF_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 2017
hadd -f files_corr1FF_mt/TT.root files_corr1FF_mt/TTToHadronic.root files_corr1FF_mt/TTTo2L2Nu.root files_corr1FF_mt/TTToSemiLeptonic.root
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToHadronic.root files_corr1FF_mt/TTToHadronicMC.root TTToHadronic TTMC 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTTo2L2Nu.root files_corr1FF_mt/TTTo2L2NuMC.root TTTo2L2Nu TTMC 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToSemiLeptonic.root files_corr1FF_mt/TTToSemiLeptonicMC.root TTToSemiLeptonic TTMC 2017
hadd -f files_corr1FF_mt/TTMC.root files_corr1FF_mt/TTToHadronicMC.root files_corr1FF_mt/TTTo2L2NuMC.root files_corr1FF_mt/TTToSemiLeptonicMC.root
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/WW.root files_corr1FF_mt/WW.root WW VV 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/WZ.root files_corr1FF_mt/WZ.root WZ VV 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ZZ.root files_corr1FF_mt/ZZ.root ZZ VV 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_t_antitop.root files_corr1FF_mt/ST_t_antitop.root ST_t_antitop ST 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_t_top.root files_corr1FF_mt/ST_t_top.root ST_t_top ST 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_tW_antitop.root files_corr1FF_mt/ST_tW_antitop.root ST_tW_antitop ST 2017
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_tW_top.root files_corr1FF_mt/ST_tW_top.root ST_tW_top ST 2017
hadd -f files_corr1FF_mt/VV.root files_corr1FF_mt/WW.root files_corr1FF_mt/WZ.root files_corr1FF_mt/ZZ.root files_corr1FF_mt/ST_t_antitop.root files_corr1FF_mt/ST_t_top.root files_corr1FF_mt/ST_tW_antitop.root files_corr1FF_mt/ST_tW_top.root

python Subtract_prompt_mt.py --directory files_corr1FF_mt
rm -f FF_corrections_1.root
root -l -b -q 'Fit_FFclosure_mt.cc(2017)'

# Prepare mT histograms, fit the ratio later with the OS/SS correction
./Set1_correction_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/Wall.root files_corr1FF_mt/WMC2.root W WMC2 2017

hadd -f mvisclosure_mt.root files_corr1FF_mt/Data.root files_corr1FF_mt/DY.root files_corr1FF_mt/W.root files_corr1FF_mt/TT.root files_corr1FF_mt/VV.root 
