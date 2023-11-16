/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #10          : Arrays
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         :
 *********************************************************/
#include "lab_10.h"

#include <cmath>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Arrays
 *
 * ________________________________________________________
 *
 * A program that numerically simulates gaussian random number generation
 *
 * ________________________________________________________
 * INPUT:
 *  none
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
    // cout << " Lab #10       : Arrays\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    srand(500);

    double th_mean;     // OUTPUT - Theoretical mean
    double pr_mean;     // OUTPUT - Practical mean
    double th_var;      // OUTPUT - Theoretical s.d.
    double pr_var;      // OUTPUT - Practical s.d.
    double seq1[100];   // PROCESSING - First sequence
    double seq2[10000]; // PROCESSING - First sequence

    // PROCESSING - Fill sequence 1 with 100 random numbers between 4 and
    // 10
    for (int i = 0; i < 100; ++i)
    {
        seq1[i] = randFloat(4.0, 10.0);
    }

    // PROCESSING - Fill sequence 2 with 100 random numbers between 4 and
    // 10
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
}
