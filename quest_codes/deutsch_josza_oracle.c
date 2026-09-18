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

    // Apply X-gates
    for (int qubit = 0; qubit < strlen(b_str); ++qubit) {
        if (b_str[qubit] == '1') {
            pauliX(qubits, qubit);
        }
    }

    // Apply a barrier
    syncQuESTEnv(env);
    
    // Apply controlled-NOT gates
    for (int qubit = 0; qubit < n; ++qubit) {
        controlledNot(qubits, qubit, n);
    }

    // Apply another barrier
    syncQuESTEnv(env);
    
    // Apply X-gates again
    for (int qubit = 0; qubit < strlen(b_str); ++qubit) {
        if (b_str[qubit] == '1') {
            pauliX(qubits, qubit);
        }
    }

    // Print the state vector
    printf("State vector:\n");
    for (long long int i = 0; i < 1LL << (n + 1); ++i) {
        printf("%lld: %f + %fi\n", i, getRealAmp(qubits, i), getImagAmp(qubits, i));
    }

    // Clean up
    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return 0;
}
