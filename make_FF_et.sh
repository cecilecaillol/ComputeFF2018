mkdir -p plots
rm plots/*.pdf

mkdir -p files_corrOSSSFF_et
mkdir -p files_rawFF_et
mkdir -p files_corr1FF_et

rm files_corrOSSSFF_et/*.root
rm files_rawFF_et/*.root
rm files_corr1FF_et/*.root

# Compute raw fake factors in several regions: QCD, W, TT, W MC, SS loose electron iso
sh do_rawFF_et.sh

# Compute mvis closures for all regions, and also MT correction for the W MC
sh do_FFmvisclosure.sh

# Compute OS/SS correction for the QCD FF
sh do_FFOSSScorrection.sh

# Move all the fit results to a directory
mv *.pdf plots/.

# Draw control regions where the FF come from
python Draw_raw.py --step raw
python Draw_raw.py --step mvisclosure
python Draw_raw.py --step osss

mkdir -p ff_files
cp uncorrected_fakefactors_et.root ff_files/.
cp FF_corrections_1.root ff_files/.
cp FF_QCDcorrectionOSSS.root ff_files/.
cp raw_FF_et.root ff_files/.
cp mvisclosure_et.root ff_files/.
cp OSSScorr_et.root ff_files/.


