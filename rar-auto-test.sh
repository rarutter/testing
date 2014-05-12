
#dvmdostem initial testing script
#Ruth Rutter, May 2014

#Todo:
#add SHA tag to directory?
#check for differences.patch before writing
#Add more runmodes? (Not until the rest is finished)

#set -x

#Change per run - should be argument
note="moretestingstuff"

#Different per person/machine.
output_vault_prefix="/home/ruth/development/output_holder/"
baseline_dir_prefix="/home/ruth/development/output_holder/20140505_baseline_nocalib_"
rscript_dir="/home/ruth/development/ddtv/ddtv/"
#csv_dir_extension
output_dir_extension="/output-extract-generated-files/"



today="$(date +'%Y%m%d')"


declare -a runmodes=(all eq) 

for run in ${runmodes[*]}; do

  #Set runmode in config/controlfile_site.txt
  #sed -i "/run stage/ s/^[a-z]*/$run/" /home/ruth/development/dvm-dos-tem/config/controlfile_site.txt

  #Call dvmdostem. Eventually need to add calimode change option
  #/home/ruth/development/dvm-dos-tem/dvmdostem --calibrationmode=off
  echo "Runmode: "$run

  #Archive output files
  output_dir=$output_vault_prefix$today"_"$note"_nocalib_"$run
  echo "Copying output to: "$output_dir
  #Create archive directory
  mkdir $output_dir
  #Copy output files
  cp ../dvm-dos-tem/DATA/test_single_site/output/*-$run.nc $output_dir

  #Extract output to CSV files
  echo "Extracting output to csv files"
  $rscript_dir"output-extract.R"\
    --nc-files-dir $output_dir --run-mode=$run >/dev/null

  #Plot outputs
  echo "Plotting outputs"
  ~/development/ddtv/ddtv/plotting-output.R\
    --generated-csv-dir $output_dir"/output-extract-generated-files"\
    --run-mode=$run --output-id="plots_nocalib_"$run >/dev/null

  #Move plot directory to output storage
  echo "Moving plot directory to output subdirectory"
  cp -r "./plots_nocalib_"$run"/" $output_dir"/"
  rm -rf "plots_nocalib_"$run

done

for run in ${runmodes[*]}; do

  #Baseline data to compare with
  baseline_output_dir=$baseline_dir_prefix$run$output_dir_extension
  echo "Baseline data: "$baseline_output_dir

  curr_csv_dir=$output_vault_prefix$today"_"$note"_nocalib_"$run$output_dir_extension
  echo "Output to diff: "$curr_csv_dir

  #Need to check for differences.patch existence

  cd $curr_csv_dir
  FILES=*

  for f in $FILES; do

    #Strip path and file extension
    filename=${f%.csv}

    git diff --word-diff-regex=[^[:space:],]+ --color-words\
      --no-index $f $baseline_output_dir$f >> differences.patch

    git diff --word-diff-regex=[^[:space:],]+ --color-words\
      --no-index $f $baseline_output_dir$f > $filename.patch
    

  done

  #Delete empty patch files. Not all files fail diff.
  find $curr_csv_dir -type f -size 0 -exec rm -f '{}' +

done

#profiling?









