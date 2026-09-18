#include "QuEST.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_RUNS 10000

int main() {
    int numQubits = 2;

    QuESTEnv env = createQuESTEnv();

    Qureg qubits = createQureg(numQubits, env);

    int count_00 = 0;
    int count_01 = 0;
    int count_10 = 0;
    int count_11 = 0;

    for (int i = 0; i < NUM_RUNS; ++i) {

	initZeroState(qubits);
        hadamard(qubits, 0);
	controlledNot(qubits, 0, 1);

        int outcome1 = measure(qubits, 0);
	int outcome2 = measure(qubits, 1);
        int outcome = outcome1 * 10 + outcome2;

        if (outcome == 0){
            count_00++;
        } else {
	    if (outcome == 1){
		count_01++; 
	    }else{
	       if (outcome == 10){
		   count_10++;
		    }else{count_11++;
		}
	    }
        }
    }

    // probabilities
    double prob_00 = (double)count_00 / NUM_RUNS;
    double prob_01 = (double)count_01 / NUM_RUNS;
    double prob_10 = (double)count_10 / NUM_RUNS;
    double prob_11 = (double)count_11 / NUM_RUNS;


    // Print rez
    printf("Results of 1st Bell State:\n");
    printf("00 Count - %d\n", count_00);
    printf("01 Count - %d\n", count_01);
    printf("10 Count - %d\n", count_10);
    printf("11 Count - %d\n", count_11);


    printf("Probability of 00 - %.2f\n", prob_00);
    printf("Probability of 01 - %.2f\n", prob_01);
    printf("Probability of 01 - %.2f\n", prob_10);
    printf("Probability of 11 - %.2f\n", prob_11);

    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return EXIT_SUCCESS;
}
