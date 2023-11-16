/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #13          : strings
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/12/23
 *********************************************************/
#include <cctype>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * strings
 *
 * ________________________________________________________
 *
 * A program that:
 *  - takes a camel case string and splits it apart
 *  - replaces every instance of a word with another
 *
 * ________________________________________________________
 * INPUT:
 *  exercise: Which exercise to run
 *  input_str: Input string
 *  pattern: The string to replace
 *  replace: The string that replaces pattern
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

    int exercise;     // INPUT - Which exercise to run
    string input_str; // INPUT - Input string
    string pattern;   // INPUT - The string to replace
    string replace;   // INPUT - The string that replaces pattern
    int pos;          // PROCESSING - Exercise 2: Position in input str
    int patt_size;    // PROCESSING - Exercise 2: Size of search string

    // INPUT - Get the exercise the user wants to run
    cout << "Which exercise?\n";
    cin >> exercise;
    cout << endl;
    cin.ignore(1000, '\n');

    if (exercise == 1)
    {
        // INPUT - Get the sentence from the user to split apart
        cout << "Enter a sentence (no spaces, 1st letter of each word is "
                "uppercase): \n";
        cin >> input_str;
        cout << endl;

        // PROCESSING - Loop over all characters (except the first) and
        // replace every uppercase with a space followed by the lowercased
        // version
        for (int i = 1; i < input_str.length(); ++i)
        {
            if (isupper(input_str[i]))
            {
                input_str[i] = tolower(input_str[i]);
                input_str.insert(i, 1, ' ');
            }
        }

        cout << input_str;
        cout << endl;
    } else if (exercise == 2)
    {
        // INPUT - Get the string to modify
        cout << "Enter the main string: ";
        getline(cin, input_str);
        cout << endl;

        // INPUT - Get the pattern to match against
        cout << "Enter the string to replace: ";
        getline(cin, pattern);
        cout << endl;

        // INPUT - Get the string to replace each match of the pattern
        cout << "Enter the replacement string: ";
        getline(cin, replace);
        cout << endl;

        pos = 0;
        patt_size = pattern.length();

        // PROCESSING - Search for a match starting from the index pos in
        // the string (which represents the position of the last match),
        // and if a match is found, assign to pos and replace the match
        // with the replacement string
        while ((pos = input_str.find(pattern, pos)) != string::npos)
        {
            input_str.replace(pos, patt_size, replace);
        }

        cout << input_str << endl;
    }

    cout << endl;

    return 0;
}
