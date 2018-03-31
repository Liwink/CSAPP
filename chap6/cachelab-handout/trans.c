#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
}

char trans7_desc[] = "Transpose7: try 4*8 cache";
void trans7(int M, int N, int A[N][M], int B[M][N])
{
    // 64 * 64: 1085 misses!
    int i, j, n, m;
    int cache_a[9];
    int cache_b[4][8];

    for (n = 0; n < N / 8; n++) {
        for (m = 0; m < M / 8; m++) {
            for (i = 0; i < 8; i++) {
                if (n == m) {
                    for (j = 0; j < 8; j++) {
                        cache_a[j] = A[n * 8 + i][m * 8 + j];
                    }
                    for (j = 0; j < 4; j++) {
                        cache_b[j][i] = cache_a[j];
                    }
                    for (j = 4; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = cache_a[j];
                    }
                }
                else {
                    for (j = 0; j < 4; j++) {
                        cache_b[j][i] = A[n * 8 + i][m * 8 + j];
                    }
                    for (j = 4; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = A[n * 8 + i][m * 8 + j];
                    }
                }
            }
            for (j = 0; j < 4; j++) {
                for (i = 0; i < 8; i++) {
                    B[m * 8 + j][n * 8 + i] = cache_b[j][i];
                }
            }
        }
    }
}


char trans6_desc[] = "Transpose6: 1 * 8 cache, 289 misses";
void trans6(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;
    int cache[8];

    for (n = 0; n < N / 8; n++) {
        for (m = 0; m < M / 8; m++) {
            for (i = 0; i < 8; i++) {
                if (n == m) {
                    for (j = 0; j < 8; j++) {
                        cache[j] = A[n * 8 + i][m * 8 + j];
                    }
                    for (j = 0; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = cache[j];
                    }
                }
                else {
                    for (j = 0; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = A[n * 8 + i][m * 8 + j];
                    }
                }
            }
        }
    }
}

char trans5_desc[] = "Transpose5: register, 287 misses";
void trans5(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int i6;
    int i7;

    for (n = 0; n < N / 8; n++) {
        for (m = 0; m < M / 8; m++) {
            for (i = 0; i < 8; i++) {
                if (n == m) {
                    i0 = A[n * 8 + i][m * 8];
                    i1 = A[n * 8 + i][m * 8 + 1];
                    i2 = A[n * 8 + i][m * 8 + 2];
                    i3 = A[n * 8 + i][m * 8 + 3];
                    i4 = A[n * 8 + i][m * 8 + 4];
                    i5 = A[n * 8 + i][m * 8 + 5];
                    i6 = A[n * 8 + i][m * 8 + 6];
                    i7 = A[n * 8 + i][m * 8 + 7];
                    B[m * 8 + 0][n * 8 + i] = i0;
                    B[m * 8 + 1][n * 8 + i] = i1;
                    B[m * 8 + 2][n * 8 + i] = i2;
                    B[m * 8 + 3][n * 8 + i] = i3;
                    B[m * 8 + 4][n * 8 + i] = i4;
                    B[m * 8 + 5][n * 8 + i] = i5;
                    B[m * 8 + 6][n * 8 + i] = i6;
                    B[m * 8 + 7][n * 8 + i] = i7;
                }
                else {
                    for (j = 0; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = A[n * 8 + i][m * 8 + j];
                    }
                }
            }
        }
    }
}

char trans4_desc[] = "Transpose4: memcpy";
void trans4(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;
    int cache[8];

    for (n = 0; n < N / 8; n++) {
        for (m = 0; m < M / 8; m++) {
            for (i = 0; i < 8; i++) {
                if (n == m) {
                    memcpy(cache, &A[n * 8 + i][m * 8], sizeof(cache));
                    for (j = 0; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = cache[j];
                    }
                }
                else {
                    for (j = 0; j < 8; j++) {
                        B[m * 8 + j][n * 8 + i] = A[n * 8 + i][m * 8 + j];
                    }
                }
            }
        }
    }
}

char trans3_desc[] = "Transpose3: 343 misses";
void trans3(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;

    for (n = 0; n < N / 8; n++) {
        for (m = 0; m < M / 8; m++) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    B[m * 8 + j][n * 8 + i] = A[n * 8 + i][m * 8 + j];
                }
            }
        }
    }
}

char trans2_desc[] = "Transpose2: 463 misses";
void trans2(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;

    for (n = 0; n < N / 4; n++) {
        for (m = 0; m < M / 4; m++) {
            for (j = 0; j < 4; j++) {
                for (i = 0; i < 4; i++) {
                    B[m * 4 + j][n * 4 + i] = A[n * 4 + i][m * 4 + j];
                }
            }
        }
    }
}

char trans1_desc[] = "Transpose1";
void trans1(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m;

    for (n = 0; n < N / 4; n++) {
        for (m = 0; m < M / 4; m++) {
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    B[m * 4 + j][n * 4 + i] = A[n * 4 + i][m * 4 + j];
                }
            }
        }
    }
}

char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

void registerFunctions()
{
    registerTransFunction(transpose_submit, transpose_submit_desc);
    registerTransFunction(trans1, trans1_desc);
    registerTransFunction(trans2, trans2_desc);
    registerTransFunction(trans3, trans3_desc);
    registerTransFunction(trans4, trans4_desc);
    registerTransFunction(trans5, trans5_desc);
    registerTransFunction(trans6, trans6_desc);
    registerTransFunction(trans7, trans7_desc);
    registerTransFunction(trans, trans_desc);

}

int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

