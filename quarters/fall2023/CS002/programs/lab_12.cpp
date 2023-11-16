/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #12          : cstrings
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/12/23
 *********************************************************/
#include "lab_12.h"

#include <iostream>
using namespace std;
/*********************************************************
 *
 * cstrings
 *
 * ________________________________________________________
 *
 * A program that does certain manipulations on a user string
 *
 * ________________________________________________________
 * INPUT:
 *  choice: The menu option the user selects
 *  text: The text the user inputs
 *
 * OUTPUT:
 *
 *********************************************************/

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #12       : cstrings\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    char choice;    // INPUT - The menu choice the user picks
    char text[102]; // INPUT - The text the user provides
    bool exit;      // PROCESSING - Should the program exit

    // INPUT - Get the initial text from the user
    cout << "Input a line of text, up to 100 characters: \n";
    cin.getline(text, 102);

    exit = false;

    // OUTPUT - Display the choice menu
    cout << "A)  Count the number of vowels in the string\n";
    cout << "B)  Count the number of consonants in the string\n";
    cout << "C)  Convert the string to uppercase\n";
    cout << "D)  Convert the string to lowercase\n";
    cout << "E)  Display the current string\n";
    cout << "F)  Enter another string\n";
    cout << "\n";
    cout << "M)  Display this menu\n";
    cout << "X)  Exit the program\n";
    cout << "\n";

    // PRCOESSING - While the user doesn't exit, loop
    do
    {
        // INPUT - Get the user's menu choice
        cout << "Enter your menu selection: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        // PROCESSING - Lowercase choice for simpler matching
        choice = lower_char(choice);
        cout << "\n";

        // OUTPUT - Display the proper action according the menu choice the
        // user gave
        if (choice == 'a')
        {
            cout << "Number of vowels: " << count_vowels(text) << "\n";
        } else if (choice == 'b')
        {
            cout << "Number of consonants: " << count_consonants(text)
                 << "\n";
        } else if (choice == 'c')
        {
            // PROCESSING - Uppercase the text and return to top of loop
            uppercase(text);
            continue;
        } else if (choice == 'd')
        {
            // PROCESSING - Lowercase the text and return to top of loop
            lowercase(text);
            continue;
        } else if (choice == 'e')
        {
            cout << text << "\n";
        } else if (choice == 'x')
        {
            // PROCESSING - Leave the loop
            exit = true;
            continue;
        } else if (choice == 'f')
        {
            // INPUT - Get the new text from the user
            cout << "Input a new line of text, up to 100 characters: \n";
            cin.getline(text, 102);
            continue;
        } else if (choice == 'm')
        {
            // OUTPUT - Display the choice menu
            cout << "A)  Count the number of vowels in the string\n";
            cout << "B)  Count the number of consonants in the string\n";
            cout << "C)  Convert the string to uppercase\n";
            cout << "D)  Convert the string to lowercase\n";
            cout << "E)  Display the current string\n";
            cout << "F)  Enter another string\n";
            cout << "\n";
            cout << "M)  Display this menu\n";
            cout << "X)  Exit the program\n";
        }

        cout << "\n";

    } while (!exit);

    return 0;
}
