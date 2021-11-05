#!/bin/bash
# This file can not be launched with sh,
# since it contains directory changes.
#
# Instead, it should be run by using:
# source cat_spikerasters.sh
#
# or simply by using the source alias (.):
# . cat_spikerasters.sh

Duration=3
for j in $(seq 11 11)
  do
    for i in $(seq 0 0)
      do
        PercentArtCells=${j}.${i}
        result_dir="run_Sasaki_Scale_100_CurrentShotStim_0${j}_${i}_SimDuration_${Duration}_Procs_8"
        cd ./results/${result_dir}
        echo ${PWD}
        cat spikeraster_{0..7}.dat | sort > spikeraster.dat
        # rm spikeraster.dat
        cd ../..
      done
  done
