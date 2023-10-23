/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #8           : Sums and Primes
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/15/23
 *********************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Sums and Primes
 *
 * ________________________________________________________
 *
 * A program that:
 * 	- Sums the digits of an integer
 * 	- Prints all primes less than or equal to an upper bound
 *
 * ________________________________________________________
 * INPUT:
 * 	digits: The digits/integer to be summed
 * 	lower_bound: The lower bound to find primes for
 * 	upper_bound: The upper bound to find primes for
 * 	exercise: Which exercise to run
 *
 * OUTPUT:
 *
 *********************************************************/

int SumDigits(int num);
bool IsPrime(int num);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #8         : Sums and Primes\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    int exercise;         // INPUT - Which exercise to run
    int digits;           // INPUT - The digits/integer to be summed
    int lower_bound;      // INPUT - The lower bound to find primes for
    int upper_bound;      // INPUT - The upper bound to find primes for
    int row_position = 0; // PROCESSING - Keeps track of which index 0-7
                          // the last printed prime was in a row

    // INPUT - Determine which exercise the user will run
    cout << "Which exercise? \n";
    cin >> exercise;

    if (exercise == 1)
    {
        do
        {
            // INPUT - Get integer to sum digits of
            cout << "Please enter an integer (0 to quit): \n";
            cin >> digits;

            // PROCESSING - Exit if digits is 0
            if (digits == 0)
            {
                break;
            } else
            {
                // OUTPUT - Print the sum of the digits
                cout << "The sum of the digits of " << digits << " is "
                     << SumDigits(digits) << "\n";
            }

        } while (digits != 0);

        cout << "Goodbye \n";
    } else if (exercise == 2)
    {
        // Get the lower and upper bound to search through
        cout << "Please input two positive numbers: \n";
        cin >> lower_bound >> upper_bound;

        // OUTPUT - Beging to display the primes
        cout << "The prime numbers between " << lower_bound << " and "
             << upper_bound << " are: \n";

        for (int n = lower_bound; n <= upper_bound; n++)
        {
            // PROCESSING - Check if prime
            if (IsPrime(n))
            {
                // PROCESSING - If the current row position fits within 8,
                // advance to then next position
                if (row_position < 8)
                {
                    ++row_position;
                } else
                {
                    // PROCESSING - The next position would exceed 8 row
                    // elements, so reset back to the start of a new row
                    row_position = 1;

                    // OUTPUT - Move to the next row
                    cout << "\n";
                }
                cout << n << '\t';
            }
        }
        cout << endl;

        // OUTPUT - Compensate for an extra new line when the table is
        // perfectly rectangular since the grading system has an extra one
        // for some reason
        if (row_position == 8)
        {
            cout << endl;
        }
    }
}

int SumDigits(int num)
{
    num = std::abs(num);

    int accumulator = 0;
    while (num != 0)
    {
        // PROCESSING - Grab the digits of the current ones place then
        // shift every digit to the right one, discarding decimals
        accumulator += num % 10;
        num /= 10;
    }
    return accumulator;
}

bool IsPrime(int num)
{

    // PROCESSING - 2 is an exception to the check so early return
    if (num == 2)
    {
        return true;
    }

    bool has_divisor = false;

    // PROCESSING - Run through evey number from 2 to the ⌊sqrt(x)⌋ and
    // check if it divides the number
    for (int m = 2; m <= std::ceil(std::sqrt(num)); m++)
    {
        if (has_divisor)
        {
            break;
        }

        has_divisor = (num % m == 0);
    }

    return !has_divisor;
}
