mkdir -p plots_mt_2017
rm plots_mt_2017/*.pdf

mkdir -p files_corrOSSSFF_mt
mkdir -p files_rawFF_mt
mkdir -p files_corr1FF_mt
rm -f files_corrOSSSFF_mt/*.root
rm -f files_rawFF_mt/*.root
rm -f files_corr1FF_mt/*.root

# Compute raw fake factors in several regions: QCD, W, TT, W MC, SS loose electron iso
sh do_rawFF_mt_2017.sh

# Compute mvis closures for all regions, and also MT correction for the W MC
sh do_FFmvisclosure_mt_2017.sh

# Compute OS/SS correction for the QCD FF
sh do_FFOSSScorrection_mt_2017.sh

# Draw control regions where the FF come from
python Draw_raw_mt.py --step raw --year 2017
python Draw_raw_mt.py --step mvisclosure --year 2017
python Draw_raw_mt.py --step osss --year 2017

mv *.pdf plots_mt_2017/.

mkdir -p ff_files_mt_2017
rm -f ff_files_mt_2017/*.root
cp uncorrected_fakefactors_mt.root ff_files_mt_2017/.
cp FF_corrections_1.root ff_files_mt_2017/.
cp FF_QCDcorrectionOSSS.root ff_files_mt_2017/.
cp raw_FF_mt.root ff_files_mt_2017/.
cp mvisclosure_mt.root ff_files_mt_2017/.
cp OSSScorr_mt.root ff_files_mt_2017/.