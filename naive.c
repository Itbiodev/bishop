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

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         m_0[i][j] = count_bishop_moves(i, j);
    //     }
    // }

    double m_k[N][N];

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
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
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
		m_k[i][j] = sum / m_0[i][j];
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

// int count_bishop_moves(int i, int j) {
//     int bishop_moves[4][2] = {
//         {-1, -1}, 
//         {1, -1}, 
//         {-1, 1}, 
//         {1, 1}
//     };
//     int count = 0;
//     for (int k = 0; k < 4; k++) {
//         int ni = i, nj = j;
//         for (;;) {
//             ni += bishop_moves[k][0];
//             nj += bishop_moves[k][1];
//             if (is_within_bounds(ni, nj)) 
//                 count++;
//             else 
//                 break;
//         }    
//     }
//     return count;
// }
