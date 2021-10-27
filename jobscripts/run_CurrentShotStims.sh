#!/bin/bash

for j in $(seq 10 20)
  do
    for i in $(seq 0 9)
      do
        PercentArtCells=${j}.${i}
        Duration=20
        result_dir="run_Sasaki_Scale_100_CurrentShotStim_0${j}_${i}_SimDuration_${Duration}_Procs_8"
        mpiexec -n 8 x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
                                                          -c "Scale=100" -c "SimDuration=${Duration}" \
                                                          -c "PercentArtActive=${PercentArtCells}" -c "JobHours=25" main.hoc
      done
  done
