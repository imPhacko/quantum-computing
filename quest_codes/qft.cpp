#include <iostream>
#include <cmath>
#include "QuEST.h"

int main() {
    // Initialize QuEST
    QuESTEnv env = createQuESTEnv();

    // Define the number of qubits
    int num_qubits = 5;

    // Create a quantum register
    Qureg qubits = createQureg(num_qubits, env);

    // Apply X gate on qubits 0, 2, and 4
    for (int i = 0; i < num_qubits; ++i) {
        if (i % 2 == 0) {
            pauliX(qubits, i);
        }
    }

    // Apply QFT to the entirety of the quantum register
    applyFullQFT(qubits);

    // Measure qubits
    int* measurements = new int[num_qubits];
    for (int i = 0; i < num_qubits; ++i) {
        measurements[i] = measure(qubits, i);
    }

    // Print measurement results
    std::cout << "QFT Output:" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < num_qubits; ++i) {
        std::cout << "q[" << i << "] = " << measurements[i] << std::endl;
    }

    // Apply inverse QFT to the entirety of the quantum register
    applyFullQFT(qubits);

    // Measure qubits again
    for (int i = 0; i < num_qubits; ++i) {
        measurements[i] = measure(qubits, i);
    }

    // Print measurement results after inverse QFT
    std::cout << "\nQFT with inverse QFT Output:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (int i = 0; i < num_qubits; ++i) {
        std::cout << "q[" << i << "] = " << measurements[i] << std::endl;
    }

    // Free allocated memory
    delete[] measurements;
    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return 0;
}
