#!/bin/bash
# This file can not be launched with sh,
# since it contains random number generations.
#
# Instead, it should be run by using:
# source run_CurrentShotStims.sh
#
# or simply by using the source alias (.):
# . run_CurrentShotStims.sh

Duration=20
RANDOM=$(date +%s)
for j in $(seq 12 12)
  do
    for i in $(seq 7 9)
      do
        PercentArtCells=${j}.${i}
        result_dir="run_Sasaki_Scale_100_CurrentShotStim_0${j}_${i}_SimDuration_${Duration}_Procs_8"
        mpiexec -n 8 x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
                                                          -c "Scale=100" -c "SimDuration=${Duration}" \
                                                          -c "PercentArtActive=${PercentArtCells}" \
                                                          -c "RandomSeedsCell=${RANDOM}" -c "JobHours=25" main.hoc
        # Concatenate all spikeraster data
        cd ./results/${result_dir}
        echo ${PWD}
        cat spikeraster_{0..7}.dat | sort > spikeraster.dat
        # rm spikeraster.dat
        cd ../..

      done
  done
