mkdir -p plots_et_2016
rm plots_et_2016/*.pdf

mkdir -p files_corrOSSSFF_et
mkdir -p files_rawFF_et
mkdir -p files_corr1FF_et
rm -f files_corrOSSSFF_et/*.root
rm -f files_rawFF_et/*.root
rm -f files_corr1FF_et/*.root

# Compute raw fake factors in several regions: QCD, W, TT, W MC, SS loose electron iso
sh do_rawFF_et_2016.sh

# Compute mvis closures for all regions, and also MT correction for the W MC
sh do_FFmvisclosure_et_2016.sh

# Compute OS/SS correction for the QCD FF
sh do_FFOSSScorrection_et_2016.sh

# Draw control regions where the FF come from
python Draw_raw.py --step raw --year 2016
python Draw_raw.py --step mvisclosure --year 2016 
python Draw_raw.py --step osss --year 2016

mv *.pdf plots_et_2016/.

mkdir -p ff_files_et_2016
rm -f ff_files_et_2016/*.root
cp uncorrected_fakefactors_et.root ff_files_et_2016/.
cp FF_corrections_1.root ff_files_et_2016/.
cp FF_QCDcorrectionOSSS.root ff_files_et_2016/.
cp raw_FF_et.root ff_files_et_2016/.
cp mvisclosure_et.root ff_files_et_2016/.
cp OSSScorr_et.root ff_files_et_2016/.


