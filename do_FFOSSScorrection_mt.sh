./Andrew_Make.sh OSSScorrection_mt.cc
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DataA.root files_corrOSSSFF_mt/DataA.root data_obs data_obs 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DataB.root files_corrOSSSFF_mt/DataB.root data_obs data_obs 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DataC.root files_corrOSSSFF_mt/DataC.root data_obs data_obs 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DataD.root files_corrOSSSFF_mt/DataD.root data_obs data_obs 0
hadd -f files_corrOSSSFF_mt/Data.root files_corrOSSSFF_mt/DataA.root files_corrOSSSFF_mt/DataB.root files_corrOSSSFF_mt/DataC.root files_corrOSSSFF_mt/DataD.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DY.root files_corrOSSSFF_mt/DYincl.root DY DY 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DY1.root files_corrOSSSFF_mt/DY1.root DY DY 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DY2.root files_corrOSSSFF_mt/DY2.root DY DY 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DY3.root files_corrOSSSFF_mt/DY3.root DY DY 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/DY4.root files_corrOSSSFF_mt/DY4.root DY DY 0
hadd -f files_corrOSSSFF_mt/DY.root files_corrOSSSFF_mt/DYincl.root files_corrOSSSFF_mt/DY1.root files_corrOSSSFF_mt/DY2.root files_corrOSSSFF_mt/DY3.root files_corrOSSSFF_mt/DY4.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/Wall.root files_corrOSSSFF_mt/W.root W W 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/Wall.root files_corrOSSSFF_mt/WMC.root W WMC 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/TTToHadronic.root files_corrOSSSFF_mt/TTToHadronic.root TTToHadronic TT 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/TTTo2L2Nu.root files_corrOSSSFF_mt/TTTo2L2Nu.root TTTo2L2Nu TT 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/TTToSemiLeptonic.root files_corrOSSSFF_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_corrOSSSFF_mt/TT.root files_corrOSSSFF_mt/TTToHadronic.root files_corrOSSSFF_mt/TTTo2L2Nu.root files_corrOSSSFF_mt/TTToSemiLeptonic.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/WW.root files_corrOSSSFF_mt/WW.root WW VV 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/WZ.root files_corrOSSSFF_mt/WZ.root WZ VV 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/ZZ.root files_corrOSSSFF_mt/ZZ.root ZZ VV 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/ST_t_antitop.root files_corrOSSSFF_mt/ST_t_antitop.root ST_t_antitop ST 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/ST_t_top.root files_corrOSSSFF_mt/ST_t_top.root ST_t_top ST 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/ST_tW_antitop.root files_corrOSSSFF_mt/ST_tW_antitop.root ST_tW_antitop ST 0
./OSSScorrection_mt.exe /data/ccaillol/smhmt2018_svfitted_4aug/ST_tW_top.root files_corrOSSSFF_mt/ST_tW_top.root ST_tW_top ST 0
hadd -f files_corrOSSSFF_mt/VV.root files_corrOSSSFF_mt/WW.root files_corrOSSSFF_mt/WZ.root files_corrOSSSFF_mt/ZZ.root files_corrOSSSFF_mt/ST_t_antitop.root files_corrOSSSFF_mt/ST_t_top.root files_corrOSSSFF_mt/ST_tW_antitop.root files_corrOSSSFF_mt/ST_tW_top.root

python Subtract_prompt_mt.py --directory files_corrOSSSFF_mt
root -l -b -q Fit_FFOSSS_mt.cc

hadd -f OSSScorr_mt.root files_corrOSSSFF_mt/Data.root files_corrOSSSFF_mt/DY.root files_corrOSSSFF_mt/W.root files_corrOSSSFF_mt/TT.root files_corrOSSSFF_mt/VV.root 
