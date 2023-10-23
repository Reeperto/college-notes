/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #4    : Game of Pig
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 9/27/23
 *********************************************************/
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Game of Pig
 *
 * ________________________________________________________
 *
 * Simulates turns of the Game of Pig using the 'Hold at N' strategy
 *
 * ________________________________________________________
 * INPUT:
 * 	hold_target: What point threshold to hold at
 * 	turns: How many turns to simulate
 *
 * OUTPUT:
 *
 *
 *********************************************************/

int main()
{
    // PROCESSING - Seed random number generation
    srand(333);

    int hold_target = 0;   // INPUT - Target N to hold at
    int turns = 0;         // INPUT - Number of turns to simulate
    int fail_count = 0;    // OUTPUT - Probability of 0 points
    int hold_count_0 = 0;  // OUTPUT - Probability of N points
    int hold_count_1 = 0;  // OUTPUT - Probability of N+1 points
    int hold_count_2 = 0;  // OUTPUT - Probability of N+2 points
    int hold_count_3 = 0;  // OUTPUT - Probability of N+3 points
    int hold_count_4 = 0;  // OUTPUT - Probability of N+4 points
    int hold_count_5 = 0;  // OUTPUT - Probability of N+5 points
    int current_score = 0; // PROCESSING - Current turn score
    int current_roll = 0;  // PROCESSING - Current dice roll

    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #4  : Game of Pig\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    // INPUT - Get the turn count and N to hold at
    cout << "What value should we hold at? ";
    cin >> hold_target;
    cout << "\n";

    cout << "Hold-at-N turn simulations? ";
    cin >> turns;
    cout << "\n";

    for (int i = 0; i < turns; ++i)
    {
        current_score = 0;

        while (current_score < hold_target)
        {
            current_roll = rand() % 6 + 1;

            if (current_roll == 1)
            {
                current_score = 0;
                fail_count += 1;
                break;
            }

            current_score += current_roll;
        }

        if (current_score == hold_target)
        {
            hold_count_0 += 1;
        } else if (current_score == hold_target + 1)
        {
            hold_count_1 += 1;
        } else if (current_score == hold_target + 2)
        {
            hold_count_2 += 1;
        } else if (current_score == hold_target + 3)
        {
            hold_count_3 += 1;
        } else if (current_score == hold_target + 4)
        {
            hold_count_4 += 1;
        } else if (current_score == hold_target + 5)
        {
            hold_count_5 += 1;
        }
    }

    // OUTPUT - Present the probabilities in a table
    cout << "Score"
         << "\t"
         << "Estimated Probability"
         << "\n";

    // Make all decimals show 6 places
    cout << setprecision(6) << fixed;

    cout << "0"
         << "\t" << fail_count / (double)turns << "\n";

    cout << hold_target << "\t" << hold_count_0 / (double)turns << "\n";

    cout << hold_target + 1 << "\t" << hold_count_1 / (double)turns
         << "\n";
    cout << hold_target + 2 << "\t" << hold_count_2 / (double)turns
         << "\n";
    cout << hold_target + 3 << "\t" << hold_count_3 / (double)turns
         << "\n";
    cout << hold_target + 4 << "\t" << hold_count_4 / (double)turns
         << "\n";
    cout << hold_target + 5 << "\t" << hold_count_5 / (double)turns
         << "\n";
}
