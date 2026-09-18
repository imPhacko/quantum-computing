#!/bin/bash
#SBATCH -N 1
#SBATCH --ntasks-per-node=12
#SBATCH --exclusive 
#SBATCH -J pavadinimas
#SBATCH -p comp_12_96stud 

#LT:
#  - vykdomas kodas:
#EN:
#  - code:

module add soft p qiskit py3
python3  qft_n_inverse_qft.py


