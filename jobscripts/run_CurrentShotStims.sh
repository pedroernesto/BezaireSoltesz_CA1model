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
Scale=170
StimType="IClampPosition"
# StimStype="SpikesTrainSingleSpike"
# StimStype="SpikesTrainVaryingFreq"
Stimulation="CurrentShot_ca3cells_${StimType}"
for j in $(seq 60 -10 15)
  do
    for i in $(seq 0 0)
      do
        RANDOM=$(date +%s)
        # PercentArtCells=${j}.${i}
        DegreeStim=${j}.${i}
        result_dir="run_Sasaki_Scale_${Scale}_CurrentShot_${StimType}_0${j}_${i}_SimDuration_${Duration}_Procs_8"
        mpiexec -n 8 x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
                                                          -c "strdef Stimulation" -c Stimulation="\"${Stimulation}\"" \
                                                          -c "Scale=${Scale}" -c "SimDuration=${Duration}" -c "ComputeNpoleLFP=0" \
                                                          -c "DegreeStim=${DegreeStim}" -c "TemporalResolution=0.025" \
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
