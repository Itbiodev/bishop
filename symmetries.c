#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char *argv[])
{
    const int ITERATIONS = argv[1] ? atoi(argv[1]) : 10000;

    double m_0[N][N] = {
	{ 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 9, 9, 9, 9, 9, 9, 7 },
	{ 7, 9, 11, 11, 11, 11, 9, 7 },
	{ 7, 9, 11, 13, 13, 11, 9, 7 },
	{ 7, 9, 11, 13, 13, 11, 9, 7 },
	{ 7, 9, 11, 11, 11, 11, 9, 7 },
	{ 7, 9, 9, 9, 9, 9, 9, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7 }
    };

    double m_k[8][8];

    int bishop_moves[4][2] =
	{ { -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    m_k[i][j] = m_0[i][j];
	}
    }

    for (int i = 0; i < ITERATIONS; i++) {
	double temp[8][8];
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		temp[i][j] = m_k[i][j];
	    }
	}
	/*
	   7  7  7  7
	   *  9  9  9 
	   *  * 11 11
	   *  * *  13
	 */
	for (int i = 0; i < N / 2; i++) {
	    for (int j = i; j < N / 2; j++) {
		double sum = 0;
		for (int k = 0; k < 4; k++) {
		    int ni = i, nj = j;
		    for (;;) {
			ni += bishop_moves[k][0];
			nj += bishop_moves[k][1];
			if (0 <= ni && ni < N && 0 <= nj && nj < N)
			    sum += temp[ni][nj];
			else
			    break;
		    }
		}
		double avg = sum / m_0[i][j];
		m_k[i][j] = avg;
		m_k[j][i] = avg;
		m_k[N - i - 1][j] = avg;
		m_k[i][N - j - 1] = avg;
		m_k[N - i - 1][N - j - 1] = avg;
		m_k[j][N - i - 1] = avg;
		m_k[N - j - 1][i] = avg;
		m_k[N - j - 1][N - i - 1] = avg;
	    }
	}
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    printf("%.10f ", m_k[i][j]);
	}
	printf("\n");
    }
    return 0;
}
