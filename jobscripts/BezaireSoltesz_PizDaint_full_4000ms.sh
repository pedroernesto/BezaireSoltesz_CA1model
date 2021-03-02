#!/bin/bash -l
#SBATCH --job-name="BezaireSoltesz"
#SBATCH --time=07:00:00
#SBATCH --nodes=100
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=36
#SBATCH --cpus-per-task=1
#SBATCH --partition=normal
#SBATCH --constraint=mc
#SBATCH --output=BezaireSoltesz-%j.log
#SBATCH --error=BezaireSoltesz-%j.err
#SBATCH --account=ich008

module purge
module load PrgEnv-intel
module load daint-mc cray-python/3.8.2.1 PyExtensions/python3-CrayGNU-20.08
module load intel/19.0.1.144
module use /apps/hbp/ich002/hbp-spack-deployments/softwares/12-02-2021/install/modules/tcl/cray-cnl7-haswell

# load only relevant modules needed for your job
module load neuron/8.0a

# Avoid warnings during execution
export PMI_NO_FORK=1
export PMI_NO_PREINITIALIZE=1
export PMI_MMAP_SYNC_WAIT_TIME=300
export HDF5_USE_FILE_LOCKING=FALSE
export NEURON_INIT_MPI=1

rm -rf x86_64/
nrnivmodl
srun --unbuffered ./x86_64/special -nobanner -nogui -mpi -c "SimDuration=4000" -c "Scale=1"  main.hoc 
