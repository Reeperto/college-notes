/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #8    : Arrays
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/1/23
 *********************************************************/
#include "assignment_08.h"

#include <cmath>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Noise Signals
 *
 * ________________________________________________________
 *
 * A program that numerically simulates gaussian random number generation
 *
 * ________________________________________________________
 * INPUT:
 *  in_mean - Mean entered by user
 *  in_var - Variance entered by user
 *
 * OUTPUT:
 *  th_mean - Theoretical mean
 *  pr_mean - Practical mean
 *  th_var - Theoretical s.d.
 *  pr_var - Practical s.d.
 *
 *********************************************************/

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #8  : Noise Signals\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    srand(500);

    double in_mean;     // INPUT - Mean entered by user
    double in_var;      // INPUT - Variance entered by user
    double th_mean;     // OUTPUT - Theoretical mean
    double pr_mean;     // OUTPUT - Practical mean
    double th_var;      // OUTPUT - Theoretical s.d.
    double pr_var;      // OUTPUT - Practical s.d.
    double seq1[100];   // PROCESSING - First sequence
    double seq2[10000]; // PROCESSING - First sequence
    double seq3[500];   // PROCESSING - Third sequence
    double seq4[500];   // PROCESSING - Fourth sequence
    double seq5[500];   // PROCESSING - Fifth sequence
    double seq6[500];   // PROCESSING - Sixth sequence

    // -------------------------------------------------------------------------
    // PART 1
    // -------------------------------------------------------------------------

    // PROCESSING - Fill sequence 1 with 100 random numbers im [4, 10]
    for (int i = 0; i < 100; ++i)
    {
        seq1[i] = randFloat(4.0, 10.0);
    }

    // PROCESSING - Fill sequence 2 with 100 random numbers im [4, 10]
    for (int i = 0; i < 10000; ++i)
    {
        seq2[i] = randFloat(4.0, 10.0);
    }

    // PROCESSING - Calculate the theoretical mean and variance
    th_mean = (4 + 10) / 2.0;
    th_var = (10 - 4) * (10 - 4) / 12.0;

    // PROCESSING - Calculate stats for sequence 1
    calculate_stats(seq1, 100, pr_mean, pr_var);

    // OUTPUT - Display the statistics
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";

    // PROCESSING - Calculate stats for sequence 2
    calculate_stats(seq2, 10000, pr_mean, pr_var);

    // OUTPUT - Display the statistics
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";
    cout << endl;

    // -------------------------------------------------------------------------
    // PART 2
    // -------------------------------------------------------------------------

    // PROCESSING - Fill sequence 3 with 500 random numbers with bounds
    // that have a theoretical mean of 4 and variance of 1/2
    for (int i = 0; i < 500; ++i)
    {
        seq3[i] = randFloat(2.7752551286084109509, 5.2247448713915890491);
    }

    // PROCESSING - Fill sequence 4 with 500 random numbers with bounds
    // that have a theoretical mean of 4 and variance of 2
    for (int i = 0; i < 500; ++i)
    {
        seq4[i] = randFloat(1.5505102572168219018, 6.4494897427831780982);
    }

    th_mean = 4;
    th_var = 0.5;

    // PROCESSING - Calculate stats for sequence 3
    calculate_stats(seq3, 500, pr_mean, pr_var);

    // OUTPUT - Display the statistics of sequence 3
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";

    th_mean = 4;
    th_var = 2;

    // PROCESSING - Calculate stats for sequence 4
    calculate_stats(seq4, 500, pr_mean, pr_var);

    // OUTPUT - Display the statistics of sequence 4
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";
    cout << endl;

    // -------------------------------------------------------------------------
    // PART 3
    // -------------------------------------------------------------------------

    // PROCESSING - Fill sequence 5 with 500 random numbers with bounds
    // that have a theoretical mean of 0 and variance of 3
    for (int i = 0; i < 500; ++i)
    {
        seq5[i] = randFloat(-3, 3);
    }

    // PROCESSING - Fill sequence 6 with 500 random numbers with bounds
    // that have a theoretical mean of -4 and variance of 3
    for (int i = 0; i < 500; ++i)
    {
        seq6[i] = randFloat(-7, -1);
    }

    th_mean = 0;
    th_var = 3;

    // PROCESSING - Calculate stats for sequence 5
    calculate_stats(seq5, 500, pr_mean, pr_var);

    // OUTPUT - Display the statistics of sequence 5
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";

    th_mean = -4;
    th_var = 3;

    // PROCESSING - Calculate stats for sequence 6
    calculate_stats(seq6, 500, pr_mean, pr_var);

    // OUTPUT - Display the statistics of sequence 6
    cout << th_mean << " " << pr_mean << " " << th_var << " " << pr_var
         << "\n";
    cout << endl;

    // -------------------------------------------------------------------------
    // PART 4
    // -------------------------------------------------------------------------

    // INPUT - Get mean and variance from user
    cout << "Enter Mean: \n";
    cin >> in_mean;
    cout << "Enter Variance: \n";
    cin >> in_var;

    // OUTPUT - Display the corresponding bounds and a random value between
    // those bounds
    cout << rand_mv(in_mean, in_var) << endl;

    return 0;
}
