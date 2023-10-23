/*********************************************************
 * AUTHOR 			: Eli Griffiths and Junrui Hei
 * Lab #2 			: Arithmetic Operations and Data Types
 * CLASS 			: CS 002
 * SECTION 			: Asynchronous
 * Due Date 		: 9/7/23
 *********************************************************/
#import <iostream>
using namespace std;
/*********************************************************
 *
 * Arithmetic Operations and Data Types
 *
 * ________________________________________________________
 *
 * A program that can do two taks:
 *  - Calculate the checksum of an ISBN-10
 *  - Take in a character and tell the user what position in the alphabet
 *    it has
 *
 * ________________________________________________________
 * INPUT:
 *  ex: ID of which excercise to run
 *  isbn: For example 1; ISBN to the checksummed
 *  letter: For example 2; Letter to be indexed in the alphabet
 *
 * OUTPUT:
 *  checksum: For example 1; The calculated checksum
 *  index: For example 2; The index of letter
 *
 *********************************************************/

int main()
{
    // OUTPUT - Class header information
    /* cout << "*****************************************\n";
    cout << " Programmed by : Eli Griffiths and Junrui Hei\n";
    cout << " Student ID    : 10680823\n";
    cout << " CS002         : Asynchronous\n";
    cout << " Lab #2        : Arithmetic Operations and Data Types\n";
    cout << "*****************************************\n";
    cout << "\n"; */

    int ex;
    cout << "Which exercise? ";
    cin >> ex;
    cout << endl;
    if (ex == 1)
    {
        int isbn;     // INPUT - First 9 digits of an ISBN-10;
        int checksum; // OUTPUT - The calculated checksum of `isbn`
        int weight;   // CALC - Used in the loop for weighting

        // INPUT - Get first 9 digits of an ISBN-10 from user
        cout << "Please enter the first 9 digits of the ISBN: ";
        cin >> isbn;

        // PROCESSING - Go through each digit and apply the algorithm to
        // find the checksum
        weight = 9;
        checksum = 0;
        while (weight != 0)
        {
            checksum += weight * (isbn % 10);
            isbn /= 10;
            weight -= 1;
        };
        checksum %= 11;

        // OUTPUT - Display the checksum to the user
        cout << "Checksum: " << checksum << "\n";

    } else if (ex == 2)
    {
        char letter; // INPUT - Character to be indexed
        int index;   // OUTPUT - Index of character in alphabet

        // INPUT - Ask user for the letter to be indexed
        cout << "Enter a character: ";
        cin >> letter;

        // PROCESSING - Use character arithmetic to get index of char
        index = letter - '`';

        // OUTPUt - Outputting the index of the character
        cout << letter << " is letter " << index << "\n";
    }

    return 0;
}
