./Make.sh Set1_correction_et.cc
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataB.root files_corr1FF_et/DataB.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataC.root files_corr1FF_et/DataC.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataD.root files_corr1FF_et/DataD.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataE.root files_corr1FF_et/DataE.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataF.root files_corr1FF_et/DataF.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataG.root files_corr1FF_et/DataG.root data_obs data_obs 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataH.root files_corr1FF_et/DataH.root data_obs data_obs 2016
hadd -f files_corr1FF_et/Data.root files_corr1FF_et/DataB.root files_corr1FF_et/DataC.root files_corr1FF_et/DataD.root files_corr1FF_et/DataE.root files_corr1FF_et/DataF.root files_corr1FF_et/DataG.root files_corr1FF_et/DataH.root
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY.root files_corr1FF_et/DYincl.root DY DY 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY1.root files_corr1FF_et/DY1.root DY DY 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY2.root files_corr1FF_et/DY2.root DY DY 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY3.root files_corr1FF_et/DY3.root DY DY 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY4.root files_corr1FF_et/DY4.root DY DY 2016
hadd -f files_corr1FF_et/DY.root files_corr1FF_et/DYincl.root files_corr1FF_et/DY1.root files_corr1FF_et/DY2.root files_corr1FF_et/DY3.root files_corr1FF_et/DY4.root
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W.root files_corr1FF_et/Wincl.root W W 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W1.root files_corr1FF_et/W1.root W W 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W2.root files_corr1FF_et/W2.root W W 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W3.root files_corr1FF_et/W3.root W W 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W4.root files_corr1FF_et/W4.root W W 2016
hadd -f files_corr1FF_et/W.root files_corr1FF_et/Wincl.root files_corr1FF_et/W1.root files_corr1FF_et/W2.root files_corr1FF_et/W3.root files_corr1FF_et/W4.root
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/TT.root files_corr1FF_et/TT.root TT TT 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WW.root files_corr1FF_et/WW.root WW VV 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WZ.root files_corr1FF_et/WZ.root WZ VV 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ZZ.root files_corr1FF_et/ZZ.root ZZ VV 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_antitop.root files_corr1FF_et/ST_t_antitop.root ST_t_antitop ST 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_top.root files_corr1FF_et/ST_t_top.root ST_t_top ST 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_antitop.root files_corr1FF_et/ST_tW_antitop.root ST_tW_antitop ST 2016
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_top.root files_corr1FF_et/ST_tW_top.root ST_tW_top ST 2016
hadd -f files_corr1FF_et/VV.root files_corr1FF_et/ST_t_antitop.root files_corr1FF_et/ST_t_top.root files_corr1FF_et/ST_tW_antitop.root files_corr1FF_et/ST_tW_top.root files_corr1FF_et/WW.root files_corr1FF_et/WZ.root files_corr1FF_et/ZZ.root
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ggH125.root files_corr1FF_et/ggH_htt125.root ggH_htt125 ggH_htt125 2016

python Subtract_prompt_et.py --directory files_corr1FF_et
rm -f FF_corrections_1.root
root -l -b -q Fit_FFclosure_et.cc

# Prepare mT histograms, fit the ratio later with the OS/SS correction
./Set1_correction_et.exe /data/ccaillol/smhet2016_svfitted_16aug/Wall.root files_corr1FF_et/WMC2.root W WMC2 2016

hadd -f mvisclosure_et.root files_corr1FF_et/Data.root files_corr1FF_et/DY.root files_corr1FF_et/W.root files_corr1FF_et/TT.root files_corr1FF_et/VV.root 

