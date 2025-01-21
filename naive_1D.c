#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char *argv[])
{
    const int ITERATIONS = argv[1] ? atoi(argv[1]) : 10000;

    double m_0[N * N] = {
	7, 7, 7, 7, 7, 7, 7, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 7, 7, 7, 7, 7, 7, 7
    };

    int bishop_moves[4][2] =
	{ { -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };

    double m_k[N * N];

    for (int idx = 0; idx < N * N; idx++) {
	m_k[idx] = m_0[idx];
    }

    for (int iter = 0; iter < ITERATIONS; iter++) {
	double temp[N * N];

	for (int idx = 0; idx < N * N; idx++) {
	    temp[idx] = m_k[idx];
	}

	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		double sum = 0;
		for (int k = 0; k < 4; k++) {
		    int ni = i, nj = j;
		    for (;;) {
			ni += bishop_moves[k][0];
			nj += bishop_moves[k][1];
			if (0 <= ni && ni < N && 0 <= nj && nj < N) {
			    sum += temp[ni * N + nj];
			} else {
			    break;
			}
		    }
		}
		m_k[i * N + j] = sum / m_0[i * N + j];
	    }
	}
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    printf("%.10f ", m_k[i * N + j]);
	}
	printf("\n");
    }

    return 0;
}
