/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #4           : Loops
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 9/22/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Loops
 *
 * ________________________________________________________
 *
 * A program that can:
 *  - Determine if a string has an x or e in it
 *  - Apply the map e => 3, i => 1, and x => *
 *  - Find the first occurence of '.' and "stop"
 *
 * ________________________________________________________
 * INPUT:
 * 	- exercise: Which exercise the user is going to run.
 * 	- input: The word or sentence the user provides
 *
 * OUTPUT:
 * 	- transformed: The modified version of the user input
 *
 *********************************************************/

int main()
{
    string input; // INPUT - The word or sentence the user provides
    int exercise; // INPUT - Which exercise the user is going to run.

    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #4 : Loops\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    // INPUT - Determine which exercise to run
    cout << "Which exercise: ";
    cin >> exercise;
    cout << "\n";

    if (exercise == 1)
    {
        bool e_present; // PROCESSING - Is true if an e is present in input
        bool x_present; // PROCESSING - Is true if an x is present in input

        // INPUT - Get word from user
        cout << "Enter a word: ";
        cin >> input;
        cout << "\n";

        // PROCESSING - Loop through input and determine if an e or x is
        // present
        for (int i = 0; i < input.size(); ++i)
        {
            if (input.at(i) == 'e')
            {
                e_present = true;
            }
            if (input.at(i) == 'x')
            {
                x_present = true;
            }
        }

        // OUTPUT - If e is present, let the user know
        if (e_present)
        {
            cout << "Your word " << input
                 << " contains the character 'e'\n";
        }

        // OUTPUT - If x is present, let the user know
        if (x_present)
        {
            cout << "Your word " << input
                 << " contains the character 'x'\n";
        }
    } else if (exercise == 2)
    {
        // INPUT - Get word from user
        cout << "Enter a word: ";
        cin >> input;
        cout << "\n";

        // PROCESSING - Loop through input and replace appropriate
        // characters
        for (int i = 0; i < input.size(); ++i)
        {
            if (input.at(i) == 'e')
            {
                input.at(i) = '3';
            } else if (input.at(i) == 'i')
            {
                input.at(i) = '1';
            } else if (input.at(i) == 'x')
            {
                input.at(i) = '*';
            }
        }

        // OUTPUT - Show the user their transformed word
        cout << "Your word transformed is " << input << "\n";
    } else if (exercise == 3)
    {
        // INPUT - Get a sentence from the user
        cout << "Enter a sentence: ";
        cin >> input;
        cout << "\n";

        // PROCESSING - Get the index of '.' and "stop" in the sentence
        int dot_index = input.find('.');
        int stop_index = input.find("stop");

        // OUTPUT - If '.' was found, tell the user where it is
        if (dot_index != -1)
        {
            cout << "The character '.' is located at index " << dot_index
                 << "\n";
        } else
        {
            cout << "Your sentence does not contain the character '.'\n";
        }

        // OUTPUT - If "stop" was found, tell the user where it is
        if (stop_index != -1)
        {
            cout << "The word \"stop\" is located at index " << stop_index
                 << "\n";
        } else
        {
            cout << "Your sentence does not contain the word \"stop\"\n";
        }
    }
}
