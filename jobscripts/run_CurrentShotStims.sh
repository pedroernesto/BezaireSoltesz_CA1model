#!/bin/bash
# This file can not be launched with sh,
# since it contains random number generations.
#
# Instead, it should be run by using:
# source run_CurrentShotStims.sh
#
# or simply by using the source alias (.):
# . run_CurrentShotStims.sh

# Before launching a new parallel simulation, it may be useful
# to find the PIDs of 'nrniv' processes  still active and kill them:
# pids=$(echo $(/bin/ps r -o pid,cmd|grep "nrniv"| grep -v "grep"|awk '{print $1}'))
# kill -9 $pids

Duration=20
for j in $(seq 10 20)
  do
    for i in $(seq 0 0)
      do
        RANDOM=$(date +%s)
        PercentArtCells=${j}.${i}
        result_dir="run_Sasaki_Scale_100_CurrentShotStim_0${j}_${i}_SimDuration_${Duration}_Procs_8_test"
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
