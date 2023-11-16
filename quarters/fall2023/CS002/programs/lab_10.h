#pragma once
#include <cmath>

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
