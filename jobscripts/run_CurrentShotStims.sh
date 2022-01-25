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

Duration=20  # Biological time to be simulated, in ms
Scale=110
# StimType="IClampPosition"
# StimType="SpikesTrainSingleSpike"
# StimType="SpikesTrainVaryingFreq"
StimType="SpikesTrainVaryingFreqPosition"
Stimulation="CurrentShot_ca3cells_${StimType}"
for j in $(seq 53 1 115)
  do
    for i in $(seq 0 0)
      do
        RANDOM=$(date +%s)
        # PercentArtCells=${j}.${i}
        DegreeStim=${j}.${i}
        result_dir="Scale_${Scale}_${StimType}_0${j}_${i}_SimDuration_${Duration}"
        mpiexec -n 8 x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
                                                          -c "strdef Stimulation" -c Stimulation="\"${Stimulation}\"" \
                                                          -c "Scale=${Scale}" -c "SimDuration=${Duration}" -c "ComputeNpoleLFP=0" \
                                                          -c "DegreeStim=${DegreeStim}" -c "TemporalResolution=0.1" \
                                                          -c "RandomSeedsCell=${RANDOM}" -c "JobHours=25" main.hoc
                                                          # -c "PercentArtActive=${PercentArtCells}" \

        # Concatenate all spikeraster data
        cd ./results/${result_dir}
        # echo ${PWD}
        cat spikeraster_{0..7}.dat | sort > spikeraster.dat
        # rm spikeraster.dat
        cd ../..

      done
  done
