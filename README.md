# Quantum Computing Algorithms

**Built:** June 2024

Small, self-contained implementations of foundational quantum algorithms and quantum-mechanical effects, split across two toolchains: [Qiskit](https://qiskit.org/) (Python, gate-model circuits) and [QuEST](https://quest.qtechtheory.org/) (C, high-performance statevector simulation).

## Qiskit (`qiskit_codes/`)

| Project | Description |
|---|---|
| [`QFT/`](qiskit_codes/QFT) | Quantum Fourier Transform circuit — encodes a basis state and applies QFT to inspect the resulting phase/frequency representation |
| [`deutsch_josza_algorithm/`](qiskit_codes/deutsch_josza_algorithm) | Deutsch–Jozsa algorithm — determines whether a black-box function is constant or balanced in a single query, the canonical example of quantum query advantage |
| [`pigeon_hole_problem/`](qiskit_codes/pigeon_hole_problem) | Quantum pigeonhole paradox — demonstrates a counterintuitive interference effect where naive "which pigeon is in which hole" reasoning breaks down under superposition |

## QuEST (`quest_codes/`)

C simulations using QuEST for larger/faster statevector experiments:

- **Quantum teleportation** (`teleport.c`, `teleportacija_real.c`) — transmits a qubit's state using entanglement and classical communication, verified over repeated runs
- **Quantum Zeno effect** (`zeno.c`, `zeno_efffect_KS.c`, `zeno_effect_nan_KS.c`, `no_zeno.c`) — simulates how frequent measurement suppresses the evolution of a quantum state, comparing measured vs. unmeasured trajectories
- **Bell states** (`bell_state_1st.c`, `bell_state_4th.c`) — prepares two of the four maximally-entangled Bell states via Hadamard + CNOT and verifies the expected 50/50 correlated measurement statistics over 10,000 runs
- **Deutsch–Jozsa** (`deutsch_josza.c`, `deutsch_josza_oracle.c`) — a QuEST/C implementation of the same algorithm as the Qiskit notebook above, for comparing the two toolchains
- **Quantum Fourier Transform** (`qft.cpp`) — QuEST/C++ implementation of the QFT, complementing the Qiskit version

## Cluster (`cluster/`)

`qft.slurm` — SLURM batch script for running the Qiskit QFT circuit on a shared HPC cluster partition.

## Running

**Qiskit notebooks**: `pip install qiskit qiskit-aer` then open the `.ipynb` files.

**QuEST**: requires the [QuEST library](https://github.com/QuEST-Kit/QuEST) built and linked; compile with:
```bash
gcc -o sim teleport.c -lQuEST -lm
```
