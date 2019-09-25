./Make.sh RawFF_et.cc
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataA.root files_rawFF_et/DataA.root data_obs data_obs 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataB.root files_rawFF_et/DataB.root data_obs data_obs 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataC.root files_rawFF_et/DataC.root data_obs data_obs 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DataD.root files_rawFF_et/DataD.root data_obs data_obs 2018
hadd -f files_rawFF_et/Data.root files_rawFF_et/DataA.root files_rawFF_et/DataB.root files_rawFF_et/DataC.root files_rawFF_et/DataD.root
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY.root files_rawFF_et/DYincl.root DY DY 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY1.root files_rawFF_et/DY1.root DY DY 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY2.root files_rawFF_et/DY2.root DY DY 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY3.root files_rawFF_et/DY3.root DY DY 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/DY4.root files_rawFF_et/DY4.root DY DY 2018
hadd -f files_rawFF_et/DY.root files_rawFF_et/DYincl.root files_rawFF_et/DY1.root files_rawFF_et/DY2.root files_rawFF_et/DY3.root files_rawFF_et/DY4.root
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/Wall.root files_rawFF_et/W.root W W 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToHadronic.root files_rawFF_et/TTToHadronic.root TTToHadronic TT 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTTo2L2Nu.root files_rawFF_et/TTTo2L2Nu.root TTTo2L2Nu TT 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/TTToSemiLeptonic.root files_rawFF_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 2018
hadd -f files_rawFF_et/TT.root files_rawFF_et/TTToHadronic.root files_rawFF_et/TTTo2L2Nu.root files_rawFF_et/TTToSemiLeptonic.root
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/WW.root files_rawFF_et/WW.root WW VV 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/WZ.root files_rawFF_et/WZ.root WZ VV 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ZZ.root files_rawFF_et/ZZ.root ZZ VV 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_t_antitop.root files_rawFF_et/ST_t_antitop.root ST_t_antitop ST 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_t_top.root files_rawFF_et/ST_t_top.root ST_t_top ST 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_tW_antitop.root files_rawFF_et/ST_tW_antitop.root ST_tW_antitop ST 2018
./RawFF_et.exe /data/ccaillol/smhet2018_svfitted_4aug/ST_tW_top.root files_rawFF_et/ST_tW_top.root ST_tW_top ST 2018
hadd -f files_rawFF_et/VV.root files_rawFF_et/WW.root files_rawFF_et/WZ.root files_rawFF_et/ZZ.root files_rawFF_et/ST_t_antitop.root files_rawFF_et/ST_t_top.root files_rawFF_et/ST_tW_antitop.root files_rawFF_et/ST_tW_top.root

python Subtract_prompt_et.py --directory files_rawFF_et
rm uncorrected_fakefactors_et.root
root -l -b -q Fit_FF_et.cc 

hadd -f raw_FF_et.root files_rawFF_et/Data.root files_rawFF_et/DY.root files_rawFF_et/W.root files_rawFF_et/TT.root files_rawFF_et/VV.root 

