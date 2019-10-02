./Andrew_Make.sh RawFF_mt.cc
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataB.root files_rawFF_mt/DataB.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataC.root files_rawFF_mt/DataC.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataD.root files_rawFF_mt/DataD.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataE.root files_rawFF_mt/DataE.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataF.root files_rawFF_mt/DataF.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataG.root files_rawFF_mt/DataG.root data_obs data_obs 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DataH.root files_rawFF_mt/DataH.root data_obs data_obs 2016
hadd -f files_rawFF_mt/Data.root files_rawFF_mt/DataB.root files_rawFF_mt/DataC.root files_rawFF_mt/DataD.root files_rawFF_mt/DataE.root files_rawFF_mt/DataF.root files_rawFF_mt/DataG.root files_rawFF_mt/DataH.root
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DY.root files_rawFF_mt/DYincl.root DY DY 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DY1.root files_rawFF_mt/DY1.root DY DY 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/DY2.root files_rawFF_mt/DY2.root DY DY 2016
./RawFF_mt.exe /data/aloeliger/SMHTT/smhmt2016_svfitted_25aug/DY3.root files_rawFF_mt/DY3.root DY DY 2016
./RawFF_mt.exe /data/aloeliger/SMHTT/smhmt2016_svfitted_25aug/DY4.root files_rawFF_mt/DY4.root DY DY 2016
hadd -f files_rawFF_mt/DY.root files_rawFF_mt/DYincl.root files_rawFF_mt/DY1.root files_rawFF_mt/DY2.root files_rawFF_mt/DY3.root files_rawFF_mt/DY4.root
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/W.root files_rawFF_mt/Wincl.root W W 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/W1.root files_rawFF_mt/W1.root W W 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/W2.root files_rawFF_mt/W2.root W W 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/W3.root files_rawFF_mt/W3.root W W 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/W4.root files_rawFF_mt/W4.root W W 2016
hadd -f files_rawFF_mt/W.root files_rawFF_mt/Wincl.root files_rawFF_mt/W1.root files_rawFF_mt/W2.root files_rawFF_mt/W3.root files_rawFF_mt/W4.root
./RawFF_mt.exe /data/aloeliger/SMHTT/smhmt2016_svfitted_25aug/TT.root files_rawFF_mt/TT.root TT TT 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/WW.root files_rawFF_mt/WW.root WW VV 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/WZ.root files_rawFF_mt/WZ.root WZ VV 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ZZ.root files_rawFF_mt/ZZ.root ZZ VV 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ST_t_antitop.root files_rawFF_mt/ST_t_antitop.root ST_t_antitop ST 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ST_t_top.root files_rawFF_mt/ST_t_top.root ST_t_top ST 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ST_tW_antitop.root files_rawFF_mt/ST_tW_antitop.root ST_tW_antitop ST 2016
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ST_tW_top.root files_rawFF_mt/ST_tW_top.root ST_tW_top ST 2016
hadd -f files_rawFF_mt/VV.root files_rawFF_mt/ST_t_antitop.root files_rawFF_mt/ST_t_top.root files_rawFF_mt/ST_tW_antitop.root files_rawFF_mt/ST_tW_top.root files_rawFF_mt/WW.root files_rawFF_mt/WZ.root files_rawFF_mt/ZZ.root
./RawFF_mt.exe /data/ccaillol/smhmt2016_svfitted_16aug/ggH125.root files_rawFF_mt/ggH_htt125.root ggH_htt125 ggH_htt125 2016

python Subtract_prompt_mt.py --directory files_rawFF_mt
rm uncorrected_fakefactors_mt.root
root -l -b -q 'Fit_FF_mt.cc (2016)'

hadd -f raw_FF_mt.root files_rawFF_mt/Data.root files_rawFF_mt/DY.root files_rawFF_mt/W.root files_rawFF_mt/TT.root files_rawFF_mt/VV.root 
