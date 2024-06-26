#include "QuEST.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SIMULATIONS 256 // number of runs define here

int main() {
    // number of qubits and time steps
    int num_qubits = 1;
    int num_time_steps = 20;

    // store x and y values for every time step
    double x_coords[num_time_steps + 1];
    double y_coords[num_time_steps + 1];
    
    // x vals
    for (size_t step = 0; step < num_time_steps + 1; step++) {
        x_coords[step] = step;
    }

    //  y vals
    for (size_t step = 0; step < num_time_steps + 1; step++) {
        y_coords[step] = 0.0;
    }
    
    // quantum circuit start
    QuESTEnv quantum_env = createQuESTEnv();
    Qureg quantum_register = createQureg(num_qubits, quantum_env);

    // t
    for (int current_step = 0; current_step < num_time_steps + 1; ++current_step) {
        int zero_count = 0;
        int one_count = 0;

        // loop
        for (int sim_run = 0; sim_run < NUM_SIMULATIONS; sim_run++) {
            double rotation_angle = M_PI / num_time_steps;
            initZeroState(quantum_register);
            
            pauliX(quantum_register, 0);

            // Apply rotation for the current time step
            for (int rotation_step = 0; rotation_step < current_step; ++rotation_step) {
                rotateX(quantum_register, 0, rotation_angle);
            }

            // Measure the qubit
            int measurement_outcome = measure(quantum_register, 0);
        
            if (measurement_outcome == 0) {
                zero_count++;
            } else {
                one_count++;
            }
        }

        // Print the count of '1' outcomes
        printf("Count of 1s: %d\n", one_count);
        
        // Calculate the probability of measuring '1' and store in y_coords
        y_coords[current_step] = (double)one_count / NUM_SIMULATIONS;

        // Print the current time step and corresponding y value
        printf("Time step: %d\n", current_step);
        printf("y value: %.4f\n", y_coords[current_step]);
    }

    destroyQureg(quantum_register, quantum_env);
    destroyQuESTEnv(quantum_env);

    return EXIT_SUCCESS;
}