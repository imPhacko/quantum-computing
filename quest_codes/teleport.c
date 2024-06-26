#include "QuEST.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_RUNS 10000

int main() {
    // Number of qubits
    int numQubits = 3; //0 - a0, 1 - a1, 2 - b0 

    QuESTEnv env = createQuESTEnv();

    Qureg qubits = createQureg(numQubits, env);

    int count_000 = 0;
    int count_001 = 0;
    int count_010 = 0;
    int count_011 = 0;
    int count_100 = 0;
    int count_101 = 0;
    int count_110 = 0;
    int count_111 = 0;


    for (int i = 0; i < NUM_RUNS; ++i) {

	initZeroState(qubits);
	hadamard(qubits, 1);
	controlledNot(qubits, 1, 2);
	rotateX(qubits, 0, M_PI/4);

	controlledNot(qubits, 0, 1);
	hadamard(qubits, 0);

        int rez1 = measure(qubits, 0);
	int rez2 = measure(qubits, 1);

        if (rez1 == 1) {
	    pauliZ(qubits, 2);
	}

        if (rez2 == 1) {
	    pauliX(qubits, 2);
	}

	rotateX(qubits, 0, -M_PI/4);

	int rez3 = measure(qubits, 2);

	int rez = rez1 * 100 + rez2 * 10 + rez3;

	switch (rez) {
	    case 000:
		count_000++;
	        break;

	    case 001:
		count_001++;
	        break;

	    case 010:
		count_010++;
	        break;	

	    case 011:
		count_011++;
	        break;

	    case 100:
		count_100++;
	        break;

	    case 101:
		count_101++;
	        break;

	    case 110:
		count_110++;
	        break;

	    case 111:
		count_111++;
	        break;
	}
    }


    // Print rez
    printf("Galutiniu busenu kiekiai:.\n");
    printf("000 buvo: : %d\n", count_000);
    printf("001 buvo: : %d\n", count_001);
    printf("010 buvo: : %d\n", count_010);
    printf("011 buvo: : %d\n", count_011);
    printf("100 buvo: : %d\n", count_100);
    printf("101 buvo: : %d\n", count_101);
    printf("110 buvo: : %d\n", count_110);
    printf("111 buvo: : %d\n", count_111);

    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return EXIT_SUCCESS;
}
