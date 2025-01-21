#include <stdio.h>
#include <stdlib.h>

#define N 8

int to_1D(int i, int j)
{
    return i * N + j;
}

int main(int argc, char *argv[])
{

    int ITERATIONS = argv[1] ? atoi(argv[1]) : 10000;

    double m_0[8 * 8] = {
	7, 7, 7, 7, 7, 7, 7, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 13, 13, 11, 9, 7,
	7, 9, 11, 11, 11, 11, 9, 7,
	7, 9, 9, 9, 9, 9, 9, 7,
	7, 7, 7, 7, 7, 7, 7, 7
    };

    int bishop_moves[8] = { -1, -1, 1, -1, -1, 1, 1, 1 };

    double m_k[N * N];

    for (int idx = 0; idx < N * N; idx++) {
	m_k[idx] = m_0[idx];
    }

    for (int iter = 0; iter < ITERATIONS; iter++) {
	double temp[N * N];

	for (int idx = 0; idx < N * N; idx++) {
	    temp[idx] = m_k[idx];
	}

	for (int i = 0; i < N / 2; i++) {
	    for (int j = i; j < N / 2; j++) {
		double sum = 0;

		for (int k = 0; k < 4; k++) {
		    int ni = i, nj = j;
		    for (;;) {
			ni += bishop_moves[k * 2];
			nj += bishop_moves[k * 2 + 1];
			if (0 <= ni && ni < N && 0 <= nj && nj < N) {
			    sum += temp[to_1D(ni, nj)];
			} else {
			    break;
			}
		    }
		}

		double avg = sum / m_0[to_1D(i, j)];

		m_k[to_1D(i, j)] = avg;
		m_k[to_1D(j, i)] = avg;
		m_k[to_1D(N - i - 1, j)] = avg;
		m_k[to_1D(i, N - j - 1)] = avg;
		m_k[to_1D(N - i - 1, N - j - 1)] = avg;
		m_k[to_1D(j, N - i - 1)] = avg;
		m_k[to_1D(N - j - 1, i)] = avg;
		m_k[to_1D(N - j - 1, N - i - 1)] = avg;
	    }
	}
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    printf("%.10f ", m_k[to_1D(i, j)]);
	}
	printf("\n");
    }

    return 0;
}
