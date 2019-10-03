./Andrew_Make.sh RawFF_mt.cc
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DataA.root files_rawFF_mt/DataA.root data_obs data_obs 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DataB.root files_rawFF_mt/DataB.root data_obs data_obs 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DataC.root files_rawFF_mt/DataC.root data_obs data_obs 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DataD.root files_rawFF_mt/DataD.root data_obs data_obs 2018
hadd -f files_rawFF_mt/Data.root files_rawFF_mt/DataA.root files_rawFF_mt/DataB.root files_rawFF_mt/DataC.root files_rawFF_mt/DataD.root
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DY.root files_rawFF_mt/DYincl.root DY DY 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DY1.root files_rawFF_mt/DY1.root DY DY 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DY2.root files_rawFF_mt/DY2.root DY DY 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DY3.root files_rawFF_mt/DY3.root DY DY 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/DY4.root files_rawFF_mt/DY4.root DY DY 2018
hadd -f files_rawFF_mt/DY.root files_rawFF_mt/DYincl.root files_rawFF_mt/DY1.root files_rawFF_mt/DY2.root files_rawFF_mt/DY3.root files_rawFF_mt/DY4.root
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/Wall.root files_rawFF_mt/W.root W W 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/TTToHadronic.root files_rawFF_mt/TTToHadronic.root TTToHadronic TT 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/TTTo2L2Nu.root files_rawFF_mt/TTTo2L2Nu.root TTTo2L2Nu TT 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/TTToSemiLeptonic.root files_rawFF_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 2018
hadd -f files_rawFF_mt/TT.root files_rawFF_mt/TTToHadronic.root files_rawFF_mt/TTTo2L2Nu.root files_rawFF_mt/TTToSemiLeptonic.root
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/WW.root files_rawFF_mt/WW.root WW VV 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/WZ.root files_rawFF_mt/WZ.root WZ VV 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/ZZ.root files_rawFF_mt/ZZ.root ZZ VV 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/ST_t_antitop.root files_rawFF_mt/ST_t_antitop.root ST_t_antitop ST 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/ST_t_top.root files_rawFF_mt/ST_t_top.root ST_t_top ST 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/ST_tW_antitop.root files_rawFF_mt/ST_tW_antitop.root ST_tW_antitop ST 2018
./RawFF_mt.exe /data/ccaillol/smhmt2018_svfitted_30sep/ST_tW_top.root files_rawFF_mt/ST_tW_top.root ST_tW_top ST 2018
hadd -f files_rawFF_mt/VV.root files_rawFF_mt/WW.root files_rawFF_mt/WZ.root files_rawFF_mt/ZZ.root files_rawFF_mt/ST_t_antitop.root files_rawFF_mt/ST_t_top.root files_rawFF_mt/ST_tW_antitop.root files_rawFF_mt/ST_tW_top.root

python Subtract_prompt_mt.py --directory files_rawFF_mt
root -l -b -q 'Fit_FF_mt.cc(2018)'

hadd -f raw_FF_mt.root files_rawFF_mt/Data.root files_rawFF_mt/DY.root files_rawFF_mt/W.root files_rawFF_mt/TT.root files_rawFF_mt/VV.root 


