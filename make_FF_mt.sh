mkdir -p plots
rm plots/*.pdf

mkdir -p files_corrOSSSFF_mt
mkdir -p files_rawFF_mt
mkdir -p files_corr1FF_mt

sh do_rawFF_mt.sh 

sh do_FFmvisclosure_mt.sh 

sh do_FFOSSScorrection_mt.sh 

python Draw_raw_mt.py --step raw
python Draw_raw_mt.py --step mvisclosure
python Draw_raw_mt.py --step osss

mkdir -p ff_files
cp uncorrected_fakefactors_mt.root ff_files/.
cp FF_corrections_1.root ff_files/.
cp FF_QCDcorrectionOSSS.root ff_files/.
cp raw_FF_mt.root ff_files/.
cp mvisclosure_mt.root ff_files/.
cp OSSScorr_mt.root ff_files/.
