#include "QuEST.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_RUNS 256


int main() {
    // Number of qubits
    int numQubits = 1;
    int time_steps = 20;

    double x_values[time_steps + 1];
    double y_values[time_steps + 1];
    for (size_t m = 0; m < time_steps + 1; m++) {
        x_values[m] = m;
    }

    for (size_t l = 0; l < time_steps + 1; l++) {
       	y_values[l] = 0.0;
    }
    
    QuESTEnv env = createQuESTEnv();
    Qureg qubits = createQureg(numQubits, env);


    for (int i = 0; i < time_steps+1; ++i) {
        int count_0 = 0;
        int count_1 = 0;


	for (int d = 0; d < NUM_RUNS; d++){

    	    double theta = M_PI/time_steps;
            initZeroState(qubits);
            
	    pauliX(qubits, 0);

	    for (int j = 0; j < i; ++j) {
		int outcome_measur = measure(qubits, 0);
                rotateX(qubits, 0, theta);
  
            }

	    int outcome1 = measure(qubits, 0);
        
            if (outcome1 == 0) {
                count_0++;
            } else {
                count_1++;
            }
 	    
    	}
	printf("1 count: %d\n", count_1);
    	y_values[i] = (float)count_1 / NUM_RUNS;
	printf("timestamp: %d\n", i);
	printf("y: %.4f\n", y_values[i]);

    }

    destroyQureg(qubits, env);
    destroyQuESTEnv(env);
    return EXIT_SUCCESS;

}

