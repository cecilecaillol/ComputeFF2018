./Make.sh RawFF_et.cc

./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DataB.root files_rawFF_et/DataB.root data_obs data_obs 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DataC.root files_rawFF_et/DataC.root data_obs data_obs 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DataD.root files_rawFF_et/DataD.root data_obs data_obs 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DataE.root files_rawFF_et/DataE.root data_obs data_obs 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DataF.root files_rawFF_et/DataF.root data_obs data_obs 2017
hadd -f files_rawFF_et/Data.root files_rawFF_et/DataB.root files_rawFF_et/DataC.root files_rawFF_et/DataD.root files_rawFF_et/DataE.root files_rawFF_et/DataF.root
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DY.root files_rawFF_et/DYincl.root DY DY 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DY1.root files_rawFF_et/DY1.root DY DY 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DY2.root files_rawFF_et/DY2.root DY DY 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DY3.root files_rawFF_et/DY3.root DY DY 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/DY4.root files_rawFF_et/DY4.root DY DY 2017
hadd -f files_rawFF_et/DY.root files_rawFF_et/DYincl.root files_rawFF_et/DY1.root files_rawFF_et/DY2.root files_rawFF_et/DY3.root files_rawFF_et/DY4.root
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/Wall.root files_rawFF_et/W.root W W 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/TTToHadronic.root files_rawFF_et/TTToHadronic.root TTToHadronic TT 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/TTTo2L2Nu.root files_rawFF_et/TTTo2L2Nu.root TTTo2L2Nu TT 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/TTToSemiLeptonic.root files_rawFF_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 2017
hadd -f files_rawFF_et/TT.root files_rawFF_et/TTToHadronic.root files_rawFF_et/TTTo2L2Nu.root files_rawFF_et/TTToSemiLeptonic.root
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/WW.root files_rawFF_et/WW.root WW VV 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/WZ.root files_rawFF_et/WZ.root WZ VV 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/ZZ.root files_rawFF_et/ZZ.root ZZ VV 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/ST_t_antitop.root files_rawFF_et/ST_t_antitop.root ST_t_antitop ST 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/ST_t_top.root files_rawFF_et/ST_t_top.root ST_t_top ST 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/ST_tW_antitop.root files_rawFF_et/ST_tW_antitop.root ST_tW_antitop ST 2017
./RawFF_et.exe /data/ccaillol/smhet2017_svfitted_8jul/ST_tW_top.root files_rawFF_et/ST_tW_top.root ST_tW_top ST 2017
hadd -f files_rawFF_et/VV.root files_rawFF_et/WW.root files_rawFF_et/WZ.root files_rawFF_et/ZZ.root files_rawFF_et/ST_t_antitop.root files_rawFF_et/ST_t_top.root files_rawFF_et/ST_tW_antitop.root files_rawFF_et/ST_tW_top.root

python Subtract_prompt_et.py --directory files_rawFF_et
rm uncorrected_fakefactors_et.root
root -l -b -q 'Fit_FF_et.cc(2017)' 

hadd -f raw_FF_et.root files_rawFF_et/Data.root files_rawFF_et/DY.root files_rawFF_et/W.root files_rawFF_et/TT.root files_rawFF_et/VV.root 

