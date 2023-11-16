#pragma once
#include <cmath>
#include <iostream>
using namespace std;

/*This function generates a random double value between a and b*/
double randFloat(double a, double b)
{
    return a + (static_cast<double>(rand()) / RAND_MAX) * (b - a);
}

/*********************************************************
 * FUNCTION calculate_stats
 * ________________________________________________________
 * Calculates the mean and variance of an array of doubles
 * ________________________________________________________
 * PRE-CONDITIONS
 *   size: Size of array
 *   array: The array of doubles
 *
 * POST-CONDITIONS
 *  The function stores the mean and variance into:
 *   mean
 *   var
 *********************************************************/
void calculate_stats(double array[], // IN - Array of values
                     int size,       // IN - Size of array
                     double &mean,   // OUT - The array's mean
                     double &var)    // OUT - The array's variance
{
    double accumulator_mean = 0; // PROCESSING - Running total for mean
    double accumulator_var = 0;  // PROCESSING - Running total for var

    // PROCESSING - Calculate the mean of the array
    for (int i = 0; i < size; ++i)
    {
        accumulator_mean += array[i];
    }
    mean = accumulator_mean /= static_cast<double>(size);

    // PROCESSING - Calculate the variance of the array
    for (int i = 0; i < size; ++i)
    {
        accumulator_var += pow(array[i] - mean, 2.0);
    }
    var = accumulator_var /= static_cast<double>(size);
}

/*********************************************************
 * FUNCTION rand_mv
 * ________________________________________________________
 * Calculates and prints the bounds of a sequence to obtain the given
 * theoretical mean and variance. Returns a random value from within this
 * bound
 * ________________________________________________________
 * PRE-CONDITIONS
 *   mean: Theoretical mean
 *   var: Theoretical variance
 *
 * POST-CONDITIONS
 *   none
 *********************************************************/
double rand_mv(double mean, // IN - Theoretical mean
               double var)  // IN - Theoretical variance
{
    double lower; // OUTPUT - Lower bound of sequence
    double upper; // OUTPUT - Upper bound of sequence

    // PROCESSING - The lower and upper bounds are determined by the
    // formula:
    //
    //   μ ± sqrt(3 * σ^2)
    //
    lower = mean - sqrt(3 * var);
    upper = mean + sqrt(3 * var);

    // OUTPUT - Display the bounds
    cout << lower << " " << upper << endl;

    return randFloat(lower, upper);
}
