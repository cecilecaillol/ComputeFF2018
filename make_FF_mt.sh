mkdir -p plots
rm plots/*.pdf

mkdir -p files_corrOSSSFF_mt
mkdir -p files_rawFF_mt
mkdir -p files_corr1FF_mt

sh do_rawFF_mt.sh 

sh do_FFmvisclosure_mt.sh 
