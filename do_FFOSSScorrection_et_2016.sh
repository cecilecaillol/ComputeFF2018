./Make.sh OSSScorrection_et.cc
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataB.root files_corrOSSSFF_et/DataB.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataC.root files_corrOSSSFF_et/DataC.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataD.root files_corrOSSSFF_et/DataD.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataE.root files_corrOSSSFF_et/DataE.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataF.root files_corrOSSSFF_et/DataF.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataG.root files_corrOSSSFF_et/DataG.root data_obs data_obs 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataH.root files_corrOSSSFF_et/DataH.root data_obs data_obs 2016
hadd -f files_corrOSSSFF_et/Data.root files_corrOSSSFF_et/DataB.root files_corrOSSSFF_et/DataC.root files_corrOSSSFF_et/DataD.root files_corrOSSSFF_et/DataE.root files_corrOSSSFF_et/DataF.root files_corrOSSSFF_et/DataG.root files_corrOSSSFF_et/DataH.root
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY.root files_corrOSSSFF_et/DYincl.root DY DY 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY1.root files_corrOSSSFF_et/DY1.root DY DY 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY2.root files_corrOSSSFF_et/DY2.root DY DY 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY3.root files_corrOSSSFF_et/DY3.root DY DY 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY4.root files_corrOSSSFF_et/DY4.root DY DY 2016
hadd -f files_corrOSSSFF_et/DY.root files_corrOSSSFF_et/DYincl.root files_corrOSSSFF_et/DY1.root files_corrOSSSFF_et/DY2.root files_corrOSSSFF_et/DY3.root files_corrOSSSFF_et/DY4.root
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W.root files_corrOSSSFF_et/Wincl.root W W 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W1.root files_corrOSSSFF_et/W1.root W W 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W2.root files_corrOSSSFF_et/W2.root W W 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W3.root files_corrOSSSFF_et/W3.root W W 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W4.root files_corrOSSSFF_et/W4.root W W 2016
hadd -f files_corrOSSSFF_et/W.root files_corrOSSSFF_et/Wincl.root files_corrOSSSFF_et/W1.root files_corrOSSSFF_et/W2.root files_corrOSSSFF_et/W3.root files_corrOSSSFF_et/W4.root
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/TT.root files_corrOSSSFF_et/TT.root TT TT 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WW.root files_corrOSSSFF_et/WW.root WW VV 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WZ.root files_corrOSSSFF_et/WZ.root WZ VV 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ZZ.root files_corrOSSSFF_et/ZZ.root ZZ VV 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_antitop.root files_corrOSSSFF_et/ST_t_antitop.root ST_t_antitop ST 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_top.root files_corrOSSSFF_et/ST_t_top.root ST_t_top ST 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_antitop.root files_corrOSSSFF_et/ST_tW_antitop.root ST_tW_antitop ST 2016
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_top.root files_corrOSSSFF_et/ST_tW_top.root ST_tW_top ST 2016
hadd -f files_corrOSSSFF_et/VV.root files_corrOSSSFF_et/ST_t_antitop.root files_corrOSSSFF_et/ST_t_top.root files_corrOSSSFF_et/ST_tW_antitop.root files_corrOSSSFF_et/ST_tW_top.root files_corrOSSSFF_et/WW.root files_corrOSSSFF_et/WZ.root files_corrOSSSFF_et/ZZ.root
./OSSScorrection_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ggH125.root files_corrOSSSFF_et/ggH_htt125.root ggH_htt125 ggH_htt125 2016

python Subtract_prompt_et.py --directory files_corrOSSSFF_et
rm -f FF_QCDcorrectionOSSS.root
root -l -b -q Fit_FFOSSS_et.cc

hadd -f OSSScorr_et.root files_corrOSSSFF_et/Data.root files_corrOSSSFF_et/DY.root files_corrOSSSFF_et/W.root files_corrOSSSFF_et/TT.root files_corrOSSSFF_et/VV.root 

