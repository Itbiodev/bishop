#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char *argv[])
{
    const int ITERATIONS = argv[1] ? atoi(argv[1]) : 10000;

    double initial_state[64] = {
	7, 7, 7, 7, 7, 7, 7, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 7, 7, 7, 7, 7, 7, 7
    };

    double current_state[64], transition_matrix[64][64];

    for (int i = 0; i < 64; i++) {
	for (int j = 0; j < 64; j++) {
	    transition_matrix[i][j] = 0;
	}
    }

    int bishop_moves[4][2] = {
	{ -1, -1 },
	{ 1, -1 },
	{ -1, 1 },
	{ 1, 1 }
    };

    //    for (int pos = 0; pos < 64; pos++) {
    // int i = (int) (pos / 8);
    // int j = pos % 8;
    //
    // for (int k = 0; k < 4; k++) {
    //     int ni = i + bishop_moves[k][0], nj = j + bishop_moves[k][1];
    //     while (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
    //      int new_pos = ni * 8 + nj;
    //      transition_matrix[new_pos][pos] = 1;
    //      ni += bishop_moves[k][0];
    //      nj += bishop_moves[k][1];
    //     }
    // }
    // current_state[pos] = initial_state[pos];
    //    }

    for (int pos = 0; pos < 64; pos++) {
	int i = pos / 8, j = pos % 8;

	for (int k = 0; k < 4; k++) {
	    int ni = i, nj = j;
	    for (;;) {
		ni += bishop_moves[k][0], nj += bishop_moves[k][1];
		if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
		    int new_pos = ni * 8 + nj;
		    transition_matrix[new_pos][pos] = 1;
		} else {
		    break;
		}
	    }
	}
	current_state[pos] = initial_state[pos];
    }

    double next_state[64];
    for (int iter = 0; iter < ITERATIONS; iter++) {
	for (int i = 0; i < 64; i++) {
	    next_state[i] = 0;
	}

	for (int i = 0; i < 64; i++) {
	    for (int j = 0; j < 64; j++) {
		next_state[i] +=
		    transition_matrix[i][j] * current_state[j];
	    }
	}

	// multiply by inverse of diagonal matrix formed 
	// by the vector representing the initial state
	for (int i = 0; i < 64; i++) {
	    next_state[i] /= initial_state[i];
	}

	for (int i = 0; i < 64; i++) {
	    current_state[i] = next_state[i];
	}
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    printf("%.10f ", current_state[i * 8 + j]);
	}
	printf("\n");
    }

    return 0;
}
