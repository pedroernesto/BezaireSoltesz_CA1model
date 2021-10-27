#!/bin/bash
# This file can not be launched with sh,
# since it contatins directory changes.
#
# Instead, it should be run by using:
# source cat_spikerasters.sh
#
# or simply by using the source alias (.):
# . cat_spikerasters.sh

for j in $(seq 15 15)
  do
    for i in $(seq 0 6)
      do
        PercentArtCells=${j}_${i}
        result_dir="run_Sasaki_Scale_100_CurrentShotStim_0${PercentArtCells}_SimDuration_20_Procs_8"
        cd ./results/${result_dir}
        echo ${PWD}
        cat spikeraster_{0..7}.dat | sort > spikeraster.dat
        # rm spikeraster.dat
        cd ../..
      done
  done
