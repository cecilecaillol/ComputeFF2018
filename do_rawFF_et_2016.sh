./Make.sh RawFF_et.cc
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataB.root files_rawFF_et/DataB.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataC.root files_rawFF_et/DataC.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataD.root files_rawFF_et/DataD.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataE.root files_rawFF_et/DataE.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataF.root files_rawFF_et/DataF.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataG.root files_rawFF_et/DataG.root data_obs data_obs 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DataH.root files_rawFF_et/DataH.root data_obs data_obs 2016
hadd -f files_rawFF_et/Data.root files_rawFF_et/DataB.root files_rawFF_et/DataC.root files_rawFF_et/DataD.root files_rawFF_et/DataE.root files_rawFF_et/DataF.root files_rawFF_et/DataG.root files_rawFF_et/DataH.root
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY.root files_rawFF_et/DYincl.root DY DY 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY1.root files_rawFF_et/DY1.root DY DY 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY2.root files_rawFF_et/DY2.root DY DY 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY3.root files_rawFF_et/DY3.root DY DY 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/DY4.root files_rawFF_et/DY4.root DY DY 2016
hadd -f files_rawFF_et/DY.root files_rawFF_et/DYincl.root files_rawFF_et/DY1.root files_rawFF_et/DY2.root files_rawFF_et/DY3.root files_rawFF_et/DY4.root
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W.root files_rawFF_et/Wincl.root W W 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W1.root files_rawFF_et/W1.root W W 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W2.root files_rawFF_et/W2.root W W 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W3.root files_rawFF_et/W3.root W W 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/W4.root files_rawFF_et/W4.root W W 2016
hadd -f files_rawFF_et/W.root files_rawFF_et/Wincl.root files_rawFF_et/W1.root files_rawFF_et/W2.root files_rawFF_et/W3.root files_rawFF_et/W4.root
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/TT.root files_rawFF_et/TT.root TT TT 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WW.root files_rawFF_et/WW.root WW VV 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/WZ.root files_rawFF_et/WZ.root WZ VV 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ZZ.root files_rawFF_et/ZZ.root ZZ VV 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_antitop.root files_rawFF_et/ST_t_antitop.root ST_t_antitop ST 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_t_top.root files_rawFF_et/ST_t_top.root ST_t_top ST 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_antitop.root files_rawFF_et/ST_tW_antitop.root ST_tW_antitop ST 2016
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ST_tW_top.root files_rawFF_et/ST_tW_top.root ST_tW_top ST 2016
hadd -f files_rawFF_et/VV.root files_rawFF_et/ST_t_antitop.root files_rawFF_et/ST_t_top.root files_rawFF_et/ST_tW_antitop.root files_rawFF_et/ST_tW_top.root files_rawFF_et/WW.root files_rawFF_et/WZ.root files_rawFF_et/ZZ.root
./RawFF_et.exe /data/ccaillol/smhet2016_svfitted_16aug/ggH125.root files_rawFF_et/ggH_htt125.root ggH_htt125 ggH_htt125 2016

python Subtract_prompt_et.py --directory files_rawFF_et
rm uncorrected_fakefactors_et.root
root -l -b -q 'Fit_FF_et.cc(2016)' 

hadd -f raw_FF_et.root files_rawFF_et/Data.root files_rawFF_et/DY.root files_rawFF_et/W.root files_rawFF_et/TT.root files_rawFF_et/VV.root 

