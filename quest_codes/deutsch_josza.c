#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QuEST.h"

int main() {
    // Define the number of qubits and the bit string
    int n = 3;
    char b_str[] = "101";

    // Initialize QuEST
    QuESTEnv env = createQuESTEnv();

    // Create a quantum register
    Qureg qubits = createQureg(n + 1, env);

    // Apply H-gates
    for (int qubit = 0; qubit < n; ++qubit) {
        hadamard(qubits, qubit);
    }

    // Put qubit in state |??
    pauliX(qubits, n);
    hadamard(qubits, n);

    // Apply balanced oracle
    // Apply X-gates for balanced oracle

    for (int qubit = 0; qubit < strlen(b_str); ++qubit) {
        if (b_str[qubit] == '1') {
            pauliX(qubits, qubit);
        }
    }

    // Apply a barrier for balanced oracle
    syncQuESTEnv(env);

    // Apply controlled-NOT gates for balanced oracle
    for (int qubit = 0; qubit < n; ++qubit) {
        controlledNot(qubits, qubit, n);
    }

    // Apply another barrier for balanced oracle
    syncQuESTEnv(env);

    // Apply X-gates again for balanced oracle
    for (int qubit = 0; qubit < strlen(b_str); ++qubit) {
        if (b_str[qubit] == '1') {
            pauliX(qubits, qubit);
        }
    }
    
    // End of balanced oracle

    // Repeat H-gates
    for (int qubit = 0; qubit < n; ++qubit) {
        hadamard(qubits, qubit);
    }

    // Apply a barrier
    syncQuESTEnv(env);

    // Measure
    int outcome[n];
    for (int i = 0; i < n; ++i) {
        outcome[i] = measure(qubits, i);
    }

    // Display the measurement results
    printf("Measurement Results:\n");
    for (int i = 0; i < n; ++i) {
        printf("Qubit %d: %d\n", i, outcome[i]);
    }
    // Clean up
    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return 0;
}
