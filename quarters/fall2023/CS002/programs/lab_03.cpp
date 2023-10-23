/*********************************************************
 * AUTHOR 			: Eli Griffiths
 * Lab #3           : Branching
 * CLASS 			: CS 002
 * SECTION 			: Asynchronous
 * Due Date 		: 9/13/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Branching
 *
 * ________________________________________________________
 *
 * A program that does 2 things:
 *  - Give the user the amount of minutes, hours, or days given an arbitray
 *    amount of seconds
 *  - Provides a simple menu system for the user to decide what they want
 *    to do tonight
 *
 * ________________________________________________________
 * INPUT:
 * 	- excercise: Which excercise is going to run
 * 	- seconds: For #1 => Number of seconds to be converted
 * 	- choice: For #2 => what the user wants to do
 *
 * OUTPUT:
 * 	- minutes: Number of minutes in `seconds`
 * 	- hours: Number of hours in `seconds`
 * 	- days: Number of days in `seconds`
 *
 *********************************************************/

int main()
{
    /* // OUTPUT - Class header information
    cout << "*****************************************\n";
    cout << " Programmed by  : Eli Griffiths\n";
    cout << " Student ID     : 10680823\n";
    cout << " CS002          : Asynchronous\n";
    cout << " Lab #3         : Branching\n";
    cout << "*****************************************\n";
    cout << "\n"; */

    int excercise;
    cout << "Which exercise? ";
    cin >> excercise;

    if (excercise == 1)
    {
        int seconds;  // INPUT - Number of seconds user enters
        int quantity; // OUTPUT - Proper number of units in `seconds`

        // INPUT - Get user input for number of seconds
        cout << "Enter a number of seconds: ";
        cin >> seconds;

        // OUTPUT / PROCESSING - Determine which unit to use and output the
        // proper units to the user
        if (seconds >= 60 && seconds < 3600)
        {
            quantity = seconds / 60;
            if (quantity == 1)
            {
                cout << "There is " << quantity << " minute in " << seconds
                     << " seconds."
                     << "\n";
            } else
            {
                cout << "There are " << quantity << " minutes in "
                     << seconds << " seconds."
                     << "\n";
            }
        } else if (seconds >= 3600 && seconds < 86400)
        {
            quantity = seconds / 3600;
            if (quantity == 1)
            {
                cout << "There is " << quantity << " hour in " << seconds
                     << " seconds."
                     << "\n";
            } else
            {
                cout << "There are " << quantity << " hours in " << seconds
                     << " seconds."
                     << "\n";
            }
        } else if (seconds >= 86400)
        {
            quantity = seconds / 86400;
            if (quantity == 1)
            {
                cout << "There is " << quantity << " day in " << seconds
                     << " seconds."
                     << "\n";
            } else
            {
                cout << "There are " << quantity << " days in " << seconds
                     << " seconds."
                     << "\n";
            }
        }
    } else if (excercise == 2)
    {
        char choice; // INPUT - The user's choice

        // INPUT - Ask the user which choice they want to choose
        cout << "What do you want to do tonight?"
             << "\n";
        cout << "a. Go to the movies"
             << "\n";
        cout << "b. Eat out"
             << "\n";
        cout << "c. Hang out at the Mall"
             << "\n";
        cout << "d. Go watch the Dodgers"
             << "\n";

        cin >> choice;

        if (choice == 'a' || choice == 'A')
        {
            cout << "I know just the movie to see!"
                 << "\n";
        } else if (choice == 'b' || choice == 'B')
        {
            cout << "Great! I've been wanting to try that new Tuvaluan "
                    "restaurant!"
                 << "\n";
        } else if (choice == 'c' || choice == 'C')
        {
            cout << "You bring the cash!"
                 << "\n";
        } else if (choice == 'd' || choice == 'D')
        {
            cout << "Take me out to the ball game ..."
                 << "\n";
        } else
        {
            cout << "Nothing suits you, then? I guess we’ll just stay and "
                    "program!"
                 << "\n";
        }
    }

    return 0;
}
