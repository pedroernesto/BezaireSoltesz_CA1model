#!/bin/bash -l
#SBATCH --job-name="BezaireSoltesz"
#SBATCH --time=05:00:00
#SBATCH --nodes=45
#SBATCH --ntasks-per-core=2
#SBATCH --ntasks-per-node=136
#SBATCH --account=vsk25
#SBATCH --partition=booster
#SBATCH --output=BezaireSoltesz-%j.log
#SBATCH --error=BezaireSoltesz-%j.err

module --force purge all
module load Architecture/KNL
module use /usr/local/software/jurecabooster/OtherStages
module load Stages/2018b
module load Intel IntelMPI imkl
module load HDF5
export  MODULEPATH=/p/project/cvsk25/vsk2514/HBP/jureca-booster/install/latest:$MODULEPATH
module load neuron/2018-10

rm -rf x86_64/
nrnivmodl

Duration=20  # Biological time to be simulated, in ms
Scale=1
# StimType="IClampPosition"
StimType="SpikesTrainSingleSpike"
# StimType="SpikesTrainSingleSpikePosition"
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

for FrGABAa in $(seq 0 1 9)
  do
    for k in $(seq 0 1 9)
      do
        FractionGABAa=0.${FrGABAa}${k}
        for Stdev in $(seq 2 1 2)
          do
            StdevSyn_dir="./results/NoiseSynapsesFreq_${Stdev}_GABAa_${FrGABAa}${k}_Scale_${Scale}/${StimType}"
            mkdir -p ${StdevSyn_dir}
            StdevSyn=`echo 0.00001*${Stdev} | bc`

            Stimulation="CurrentShot_ca3cells_${StimType}"
            # for j in $(seq 400 -1 100)  # Scale=300, StimType="SpikesTrainVaryingFreq"
            # for j in $(seq 230 -1 10) # Scale=110, StimType="SpikesTrainVaryingFreq"
            # for j in $(seq 25 -1 10)  # Scale=110, StimType="SpikesTrainSingleSpike"
            for j in $(seq 20 -1 1)  # Scale=300, StimType="SpikesTrainSingleSpike"
              do
                for i in $(seq 8 -2 0)
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
                    srun --unbuffered ./x86_64/special -nobanner -nogui -mpi -c "strdef RunName" -c RunName="\"${result_dir}\"" \
            								-c "strdef Stimulation" -c Stimulation="\"${Stimulation}\"" \
            								-c "Scale=${Scale}" -c "SimDuration=${Duration}" -c "ComputeNpoleLFP=0" \
            								${cmd_str} -c "RandomSeedsCell=${RANDOM}" \
									-c "StdevSyn=${StdevSyn}" -c "FractionGABAa=${FractionGABAa}" \
									-c "JobHours=25" main.hoc

                    # Concatenate all spikeraster data
                    cd ./results/${result_dir}
                    # echo ${PWD}
                    cat spikeraster_*.dat | sort > spikeraster.dat
                    rm spikeraster_*.dat subconns_*.dat trace_*.dat
                    cd ../..

                    mv ./results/${result_dir} ${StdevSyn_dir}
                done
            done
        done
      done
  done
