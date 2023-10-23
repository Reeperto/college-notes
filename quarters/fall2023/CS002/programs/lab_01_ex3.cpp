/*********************************************************
 * AUTHOR   : Eli Griffiths and Sophie Chen
 * Lab #1   : Target Heart Rate
 * CLASS    : CS 002
 * SECTION  : Asynchronous
 * Due Date : 9/1/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * TARGET HEART RATE CALCULATOR
 *
 * ________________________________________________________
 *
 * Calculator that takes in a user's age and outputs their target heart
 * 	rate zone, showing both the lower and upper limits, as
 * 	floating-point values.
 *
 * ________________________________________________________
 * INPUT:
 * 	age: Age of user
 *
 * OUTPUT:
 * 	lower_limit: Lower limit BPM for aerboic excercise
 * 	upper_limit: Lower limit BPM for aerboic excercise
 *
 *********************************************************/
int main()
{
    double age;         // INPUT - First floating point number
    double lower_limit; // OUTPUT - Lower limit BPM for aerboic excercise
    double upper_limit; // OUTPUT - Lower limit BPM for aerboic excercise

    /* cout << "*****************************************\n";
    cout << " Programmed by: Eli Griffiths and Sophie Chen\n";
    cout << " Student ID   : 10680823\n";
    cout << " CS002        : Asynchronous\n";
    cout << " Lab #1       : Target Heart Rate\n";
    cout << "*****************************************\n"; */

    // INPUT: Prompting the user for their age.
    cout << "What is your age: ";
    cin >> age;

    // PROCESSING: Use the formulas
    //
    // 	Lower limit (bpm) = 60% of the difference between 220 and your age
    // 	Upper limit (bpm) = 75% of the difference between 220 and your age
    //
    // to calculate the user's target heart rate zone for aerobic exercise
    lower_limit = 0.6 * (220 - age);
    upper_limit = 0.75 * (220 - age);

    // OUTPUT: Display the calculated target heart rate zone for the user
    cout << "Your target heart rate is between " << lower_limit << " and "
         << upper_limit << " bpm.\n";

    return 0;
}
