#!/bin/bash
# This file can not be launched with sh,
# since it contains random number generations.
#
# Instead, it should be run by using:
# source run_CurrentShotStims.sh
#
# or simply by using the source alias (.):
# . run_CurrentShotStims.sh

# Remotely:
# nohup bash -c "source ./jobscripts/run_CurrentShotStims.sh" > sim.log &

# Before launching a new parallel simulation, it may be useful
# to find the PIDs of 'nrniv' processes  still active and kill them:
# pids=$(echo $(/bin/ps r -o pid,cmd|grep "nrniv"| grep -v "grep"|awk '{print $1}'))
# kill -9 $pids
#
# A better option:
# killall -TERM mpiexec

Duration=20  # Biological time to be simulated, in ms
Scale=500
# StimType="IClampPosition"
StimType="SpikesTrainSingleSpike"
# StimType="SpikesTrainVaryingFreq"
# StimType="SpikesTrainVaryingFreqPosition"
# StimType="Spikes4TrainVaryingFreqPosition"

SUB='Freq'
if [[ "$StimType" == *"$SUB"* ]]
then
    sed -i 's/ppvec/ppspont/g' datasets/cellnumbers_115.dat
    cat datasets/cellnumbers_115.dat
else
    sed -i 's/ppspont/ppvec/g' datasets/cellnumbers_115.dat
    cat datasets/cellnumbers_115.dat
fi

# Stimulation="synapsespont"
Stimulation="CurrentShot_ca3cells_${StimType}"
for j in $(seq 25 1 25)
  do
    for i in $(seq 3 2 3)
      do
      	if [[ j -lt 10 ]]
      	then
          result_dir="Scale_${Scale}_${StimType}_000${j}_${i}_SimDuration_${Duration}"
        elif [[ j -ge 10 && j -lt 100 ]]
      	then
          result_dir="Scale_${Scale}_${StimType}_00${j}_${i}_SimDuration_${Duration}"
        else
          result_dir="Scale_${Scale}_${StimType}_0${j}_${i}_SimDuration_${Duration}"
      	fi

        RANDOM=$(date +%s)
      	if [[ "$StimType" == *"$SUB"* ]]
        then
  	       DegreeStim=${j}.${i}
  	       cmd_str="-c DegreeStim=${DegreeStim} -c TemporalResolution=0.1 "
        else
  	       PercentArtCells=${j}.${i}
  	       cmd_str="-c PercentArtActive=${PercentArtCells} "
        fi
        # mpiexec --use-hwthread-cpus --map-by ppr:32:node:pe=1 ./x86_64/special ......
        mpiexec  -n 8 ./x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
								-c "strdef Stimulation" -c Stimulation="\"${Stimulation}\"" \
								-c "Scale=${Scale}" -c "SimDuration=${Duration}" -c "ComputeNpoleLFP=0" \
								${cmd_str} -c "RandomSeedsCell=${RANDOM}" -c "JobHours=25" main.hoc

        # Concatenate all spikeraster data
        cd ./results/${result_dir}
        # echo ${PWD}
        cat spikeraster_*.dat | sort > spikeraster.dat
        rm spikeraster_*.dat subconns_*.dat trace_*.dat
        cd ../..

      done
  done
