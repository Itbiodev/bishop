#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const int ITERATIONS = argv[1] ? atoi(argv[1]) : 10000;

    int counts[64];
    // the maximum number of moves a bishop can make is 13
    int non_zero_pos[64][13];
    double next_state[64], current_state[64];

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

    //    double transition_matrix[64][64];
    //
    //    for (int i = 0; i < 64; i++) {
    // for (int j = 0; j < 64; j++) {
    //     transition_matrix[i][j] = 0;
    // }
    //    }

    int bishop_moves[4][2] = {
	{ -1, -1 },
	{ 1, -1 },
	{ -1, 1 },
	{ 1, 1 }
    };


    for (int i = 0; i < 64; i++) {
	for (int j = 0; j < 13; j++) {
	    non_zero_pos[i][j] = 0;
	}
    }

    // if we don't "cache" the counts for each row (of the vector state), 
    // we have to make a lot of repeated work
    // in one of the loops below

    for (int i = 0; i < 64; i++) {
	counts[i] = 0;
    }

    for (int pos = 0; pos < 64; pos++) {
	int i = pos / 8, j = pos % 8;

	for (int k = 0; k < 4; k++) {
	    int ni = i, nj = j;
	    for (;;) {
		ni += bishop_moves[k][0], nj += bishop_moves[k][1];
		if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
		    int new_pos = ni * 8 + nj;
		    // instead of computing the transition matrix, 
		    // we can compute the non-zero positions and their counts in one go
		    // transition_matrix[new_pos][pos] = 1;
		    non_zero_pos[new_pos][counts[new_pos]] = pos;
		    counts[new_pos]++;
		} else {
		    break;
		}
	    }
	}
	current_state[pos] = initial_state[pos];
    }

    //    for (int i = 0; i < 64; i++) {
    // for (int j = 0; j < 64; j++) {
    //     if (transition_matrix[i][j]) {
    //      non_zero_pos[i][counts[i]] = i * 64 + j;
    //      counts[i]++;
    //     }
    // }
    //    }


    for (int iter = 0; iter < ITERATIONS; iter++) {
	for (int i = 0; i < 64; i++) {
	    double sum = 0;
	    // for (int j = 0; non_zero_pos[i][j] != 0 && j < 13; j++) {
	    for (int j = 0; j < counts[i]; j++) {
		sum += current_state[non_zero_pos[i][j]];
	    }
	    next_state[i] = sum / initial_state[i];
	}

	for (int i = 0; i < 64; i++) {
	    current_state[i] = next_state[i];
	}
    }


    for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++) {
	    printf("%.10f ", current_state[i * 8 + j]);
	}
	printf("\n");
    }

    return 0;
}
