#!/bin/bash -l
#PBS -N myjobname
#PBS -l nodes=1:ppn=32
#PBS -q siwir
#PBS -l walltime=0:05:00
#PBS -M nils.kohl@studium.uni-erlangen.de -m abe
#PBS -o $PBS_JOBNAME.out -e $PBS_JOBNAME.err
#PBS -q siwir

. /etc/profile.d/modules.sh

module load openmpi/1.6.5-ib
module load gcc/4.8.2

cd /home/stud/me31kove/Documents/siwir_git/siwir_ex03/
make clean
make

mpirun -np 32 ./asdf
