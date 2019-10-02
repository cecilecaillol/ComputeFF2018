./Andrew_Make.sh OSSScorrection_mt.cc
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataB.root files_corrOSSSFF_mt/DataB.root data_obs data_obs 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataC.root files_corrOSSSFF_mt/DataC.root data_obs data_obs 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataD.root files_corrOSSSFF_mt/DataD.root data_obs data_obs 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataE.root files_corrOSSSFF_mt/DataE.root data_obs data_obs 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DataF.root files_corrOSSSFF_mt/DataF.root data_obs data_obs 2017
hadd -f files_corrOSSSFF_mt/Data.root files_corrOSSSFF_mt/DataB.root files_corrOSSSFF_mt/DataC.root files_corrOSSSFF_mt/DataD.root files_corrOSSSFF_mt/DataE.root files_corrOSSSFF_mt/DataF.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY.root files_corrOSSSFF_mt/DYincl.root DY DY 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY1.root files_corrOSSSFF_mt/DY1.root DY DY 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY2.root files_corrOSSSFF_mt/DY2.root DY DY 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY3.root files_corrOSSSFF_mt/DY3.root DY DY 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/DY4.root files_corrOSSSFF_mt/DY4.root DY DY 2017
hadd -f files_corrOSSSFF_mt/DY.root files_corrOSSSFF_mt/DYincl.root files_corrOSSSFF_mt/DY1.root files_corrOSSSFF_mt/DY2.root files_corrOSSSFF_mt/DY3.root files_corrOSSSFF_mt/DY4.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/Wall.root files_corrOSSSFF_mt/W.root W W 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToHadronic.root files_corrOSSSFF_mt/TTToHadronic.root TTToHadronic TT 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTTo2L2Nu.root files_corrOSSSFF_mt/TTTo2L2Nu.root TTTo2L2Nu TT 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/TTToSemiLeptonic.root files_corrOSSSFF_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 2017
hadd -f files_corrOSSSFF_mt/TT.root files_corrOSSSFF_mt/TTToHadronic.root files_corrOSSSFF_mt/TTTo2L2Nu.root files_corrOSSSFF_mt/TTToSemiLeptonic.root
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/WW.root files_corrOSSSFF_mt/WW.root WW VV 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/WZ.root files_corrOSSSFF_mt/WZ.root WZ VV 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ZZ.root files_corrOSSSFF_mt/ZZ.root ZZ VV 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_t_antitop.root files_corrOSSSFF_mt/ST_t_antitop.root ST_t_antitop ST 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_t_top.root files_corrOSSSFF_mt/ST_t_top.root ST_t_top ST 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_tW_antitop.root files_corrOSSSFF_mt/ST_tW_antitop.root ST_tW_antitop ST 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_tW_top.root files_corrOSSSFF_mt/ST_tW_top.root ST_tW_top ST 2017
./OSSScorrection_mt.exe /data/ccaillol/smhmt2017_svfitted_13jun/ST_tW_top.root files_corrOSSSFF_mt/ST_tW_top.root ST_tW_top ST 2017
hadd -f files_corrOSSSFF_mt/VV.root files_corrOSSSFF_mt/WW.root files_corrOSSSFF_mt/WZ.root files_corrOSSSFF_mt/ZZ.root files_corrOSSSFF_mt/ST_t_antitop.root files_corrOSSSFF_mt/ST_t_top.root files_corrOSSSFF_mt/ST_tW_antitop.root files_corrOSSSFF_mt/ST_tW_top.root


python Subtract_prompt_mt.py --directory files_corrOSSSFF_mt
rm -f FF_QCDcorrectionOSSS.root
root -l -b -q 'Fit_FFOSSS_mt.cc(2017)'

hadd -f OSSScorr_mt.root files_corrOSSSFF_mt/Data.root files_corrOSSSFF_mt/DY.root files_corrOSSSFF_mt/W.root files_corrOSSSFF_mt/TT.root files_corrOSSSFF_mt/VV.root 