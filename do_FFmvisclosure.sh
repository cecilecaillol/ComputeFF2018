./Make.sh Set1_correction_et.cc
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataA.root files_corr1FF_et/DataA.root data_obs data_obs 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataB.root files_corr1FF_et/DataB.root data_obs data_obs 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataC.root files_corr1FF_et/DataC.root data_obs data_obs 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataD.root files_corr1FF_et/DataD.root data_obs data_obs 0
hadd -f files_corr1FF_et/Data.root files_corr1FF_et/DataA.root files_corr1FF_et/DataB.root files_corr1FF_et/DataC.root files_corr1FF_et/DataD.root
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY.root files_corr1FF_et/DYincl.root DY DY 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY1.root files_corr1FF_et/DY1.root DY DY 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY2.root files_corr1FF_et/DY2.root DY DY 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY3.root files_corr1FF_et/DY3.root DY DY 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY4.root files_corr1FF_et/DY4.root DY DY 0
hadd -f files_corr1FF_et/DY.root files_corr1FF_et/DYincl.root files_corr1FF_et/DY1.root files_corr1FF_et/DY2.root files_corr1FF_et/DY3.root files_corr1FF_et/DY4.root
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/Wall.root files_corr1FF_et/W.root W W 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/Wall.root files_corr1FF_et/WMC.root W WMC 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToHadronic.root files_corr1FF_et/TTToHadronic.root TTToHadronic TT 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTTo2L2Nu.root files_corr1FF_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToSemiLeptonic.root files_corr1FF_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_corr1FF_et/TT.root files_corr1FF_et/TTToHadronic.root files_corr1FF_et/TTTo2L2Nu.root files_corr1FF_et/TTToSemiLeptonic.root
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToHadronic.root files_corr1FF_et/TTToHadronicMC.root TTToHadronic TTMC 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTTo2L2Nu.root files_corr1FF_et/TTTo2L2NuMC.root TTTo2L2Nu TTMC 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToSemiLeptonic.root files_corr1FF_et/TTToSemiLeptonicMC.root TTToSemiLeptonic TTMC 0
hadd -f files_corr1FF_et/TTMC.root files_corr1FF_et/TTToHadronicMC.root files_corr1FF_et/TTTo2L2NuMC.root files_corr1FF_et/TTToSemiLeptonicMC.root
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/WW.root files_corr1FF_et/WW.root WW VV 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/WZ.root files_corr1FF_et/WZ.root WZ VV 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ZZ.root files_corr1FF_et/ZZ.root ZZ VV 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_t_antitop.root files_corr1FF_et/ST_t_antitop.root ST_t_antitop ST 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_t_top.root files_corr1FF_et/ST_t_top.root ST_t_top ST 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_tW_antitop.root files_corr1FF_et/ST_tW_antitop.root ST_tW_antitop ST 0
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_tW_top.root files_corr1FF_et/ST_tW_top.root ST_tW_top ST 0
hadd -f files_corr1FF_et/VV.root files_corr1FF_et/WW.root files_corr1FF_et/WZ.root files_corr1FF_et/ZZ.root files_corr1FF_et/ST_t_antitop.root files_corr1FF_et/ST_t_top.root files_corr1FF_et/ST_tW_antitop.root files_corr1FF_et/ST_tW_top.root

python Subtract_prompt_et.py --directory files_corr1FF_et
rm -f FF_corrections_1.root
root -l -b -q Fit_FFclosure_et.cc

# Prepare mT histograms, fit the ratio later with the OS/SS correction
./Set1_correction_et.exe /data/ccaillol/smhet2018_svfitted_4aug/Wall.root files_corr1FF_et/WMC2.root W WMC2 0

hadd -f mvisclosure_et.root files_corr1FF_et/Data.root files_corr1FF_et/DY.root files_corr1FF_et/W.root files_corr1FF_et/TT.root files_corr1FF_et/VV.root 

