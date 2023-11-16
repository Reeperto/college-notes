#pragma once
#include <iostream>
using namespace std;

const int M = 2, N = 3;
const int Q = 2, R = 3, S = 3;

/*********************************************************
 * FUNCTION matrixAdd
 * ________________________________________________________
 * Adds two matrices together
 * ________________________________________________________
 * PRE-CONDITIONS
 *   a: 2x3 matrix 1
 *   b: 2x3 matrix 2
 *
 * POST-CONDITIONS
 *  The function outputs the sum of a and b in sum
 *********************************************************/
void matrixAdd(const int a[M][N], // IN - Matrix 1
               const int b[M][N], // IN - Matrix 2
               int sum[M][N])     // OUT - Sum of matrices
{
    // PROCESSING - Loop over all entries of the sum matrix and
    // populate with the sum of (i,j) from matrix 1 and 2
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }
}

/*********************************************************
 * FUNCTION matrixMult
 * ________________________________________________________
 * Multiply two matrices together
 * ________________________________________________________
 * PRE-CONDITIONS
 *   a: 2x3 matrix 1
 *   b: 3x3 matrix 2
 *
 * POST-CONDITIONS
 *  The function outputs the matrix product of a and b in product
 *********************************************************/
void matrixMult(const int a[Q][R], // IN - Matrix 1
                const int b[R][S], // IN - Matrix 2
                int product[Q][S]) // OUT - Product of matrices
{
    // PROCESSING - Loop over all entries of the product matrix and
    // populate with the product of row i in matrix 1 and column j in
    // matrix 2
    for (int i = 0; i < Q; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            for (int k = 0; k < R; ++k)
            {
                product[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
