#!/usr/bin/env bash
mkdir -p plots_mt_2018
rm plots_mt_2018/*.pdf

mkdir -p files_corrOSSSFF_mt
mkdir -p files_rawFF_mt
mkdir -p files_corr1FF_mt

rm files_corrOSSSFF_mt/*.root
rm files_rawFF_mt/*.root
rm files_corr1FF_mt/*.root 

sh do_rawFF_mt.sh 

sh do_FFmvisclosure_mt.sh 

sh do_FFOSSScorrection_mt.sh 

Draw_raw_mt.py --step raw --year 2018
Draw_raw_mt.py --step mvisclosure --year 2018
Draw_raw_mt.py --step osss --year 2018

mv *.pdf plots_mt_2018

mkdir -p ff_files_mt_2018
cp uncorrected_fakefactors_mt.root ff_files_mt_2018/.
cp FF_corrections_1.root ff_files_mt_2018/.
cp FF_QCDcorrectionOSSS.root ff_files_mt_2018/.
cp raw_FF_mt.root ff_files_mt_2018/.
cp mvisclosure_mt.root ff_files_mt_2018/.
cp OSSScorr_mt.root ff_files_mt_2018/.
