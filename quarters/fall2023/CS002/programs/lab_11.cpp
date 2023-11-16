/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #11          : Intro to 2D Arrays
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/4/23
 *********************************************************/
#include "lab_11.h"

#include <iostream>
using namespace std;
/*********************************************************
 *
 * Intro to 2D Arrays
 *
 * ________________________________________________________
 *
 * A program that adds and multiplies matrices
 *
 * ________________________________________________________
 * INPUT:
 *  m1 - Matrix 1
 *  m2 - Matrix 2
 *  m3 - Matrix 3
 *  m4 - Matrix 4
 *
 * OUTPUT:
 *  sum - Matrix 1 + Matrix 2
 *  prod - Matrix 3 * Matrix 4
 *
 *********************************************************/

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #11       : Intro to 2D Arrays\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    int m1[M][N];   // INPUT - Matrix 1
    int m2[M][N];   // INPUT - Matrix 2
    int m3[Q][R];   // INPUT - Matrix 3
    int m4[R][S];   // INPUT - Matrix 4
    int sum[M][N];  // OUTPUT - Matrix 1 + Matrix 2
    int prod[Q][S]; // OUTPUT - Matrix 3 * Matrix 4

    // INPUT - Get the entries for matrix 1
    cout << "Enter Matrix A(size 2x3): ";
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> m1[i][j];
        }
    }

    // INPUT - Get the entries for matrix 2
    cout << "Enter Matrix B(size 2x3): ";
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> m2[i][j];
        }
    }

    // PROCESSING - Add matrix 1 and 2 and store in sum
    matrixAdd(m1, m2, sum);

    // OUTPUT - Display sum of matrices
    cout << "Res:\n";
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }

    // INPUT - Get the entries for matrix 3
    cout << "Enter Matrix A(size 2x3): ";
    for (int i = 0; i < Q; ++i)
    {
        for (int j = 0; j < R; ++j)
        {
            cin >> m3[i][j];
        }
    }

    // INPUT - Get the entries for matrix 4
    cout << "Enter Matrix B(size 3x3): ";
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            cin >> m4[i][j];
        }
    }

    // PROCESSING - Multiply matrix 3 and 4 and store in prod
    matrixMult(m3, m4, prod);

    // OUTPUT - Display product of matrices
    cout << "Res:\n";
    for (int i = 0; i < Q; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            cout << prod[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
