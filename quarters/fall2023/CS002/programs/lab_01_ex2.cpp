/*********************************************************
 * AUTHOR   : Eli Griffiths and Sophie Chen
 * Lab #1   : Mathematical Operations (with floating point)
 * CLASS    : CS 002
 * SECTION  : Asynchronous
 * Due Date : 9/1/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * MATHEMATICAL OPERATIONS (WITH FLOATING POINT)
 *
 * ________________________________________________________
 *
 * This program accepts six numbers from the user and
 * 	outputs their sum and average.
 *
 * ________________________________________________________
 * INPUT:
 * 	num1: First floating point number
 * 	num2: Second floating point number
 * 	num3: Third floating point number
 * 	num4: Fourth floating point number
 * 	num5: Fifth floating point number
 * 	num6: Sixth floating point number
 *
 * OUTPUT:
 * 	sum: Sum of all 6 numbers
 * 	avg: Average/mean of all 6 numbers
 *
 *********************************************************/
int main()
{
    double num1; // INPUT - First floating point number
    double num2; // INPUT - Second floating point number
    double num3; // INPUT - Third floating point number
    double num4; // INPUT - Fourth floating point number
    double num5; // INPUT - Fifth floating point number
    double num6; // INPUT - Sixth floating point number
    double sum;  // OUTPUT - Sum of all 6 numbers
    double avg;  // OUTPUT - Average/mean of all 6 numbers

    /* cout << "*****************************************\n";
    cout << " Programmed by: Eli Griffiths and Sophie Chen\n";
    cout << " Student ID   : 10680823\n";
    cout << " CS002        : Asynchronous\n";
    cout << " Lab #1       : Mathematical Operations (with floating "
            "point)\n";
    cout << "*****************************************\n"; */

    // INPUT: Prompting the user for 6 floating point numbers that are
    // space seperated.
    cout << "Enter six fp numbers on a single line, separated by spaces: ";
    cin >> num1 >> num2 >> num3 >> num4 >> num5 >> num6;

    // PROCESSING: Add the 6 floating point numbers together, then take the
    // average of them using the calculated sum.
    sum = num1 + num2 + num3 + num4 + num5 + num6;
    avg = sum / 6;

    // OUTPUT: Display the calculated sum of the 6 numbers and their
    // average
    cout << "Sum of " << num1 << " + " << num2 << " + " << num3 << " + "
         << num4 << " + " << num5 << " + " << num6 << " = " << sum << "\n";

    cout << "Average = " << avg << "\n";

    return 0;
}
