/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #14          : Vectors
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/16/23
 *********************************************************/
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
/*********************************************************
 *
 * Vectors
 *
 * ________________________________________________________
 *
 * A program that takes a string and delimiter and splits the string with
 * the delimiter
 *
 * ________________________________________________________
 * INPUT:
 *  str: The input string
 *  delim: The delimiter
 *
 * OUTPUT:
 *
 *********************************************************/

vector<string> split(string, string);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #14        : Vectors \n";
    // cout << "*****************************************\n";
    // cout << "\n";

    string str;               // INPUT - The input string
    string delim;             // INPUT - The delimiter to split on
    vector<string> split_out; // PROCESSING - The out of the split function

    // INPUT - Get the input string
    cout << "Enter the target string: \n";
    getline(cin, str);

    // INPUT - Get the delimiter
    cout << "Enter the delimiter: \n";
    getline(cin, delim);

    // PROCESSING - Split the input string using the delimiter
    split_out = split(str, delim);

    // OUTPUT - Print the split output on seperate lines
    for (int i = 0; i < split_out.size(); ++i)
    {
        cout << split_out[i] << "\n";
    }
    cout << endl;

    return 0;
}

/*********************************************************
 * FUNCTION split
 * ________________________________________________________
 * Takes a string and returns a vector of the string split at the given
 * delimiter
 * ________________________________________________________
 * PRE-CONDITIONS
 *   target: The string to split
 *   delimiter: The delimiter to split on
 *
 * POST-CONDITIONS
 *  returns a vector of the split substrings
 *********************************************************/
vector<string> split(string target,    // IN - The string to split
                     string delimiter) // IN - The delimter to split on
{
    vector<string> out;
    string substr;
    int length = delimiter.length();

    int idx = 0;
    int last_match = 0;

    while ((last_match = target.find(delimiter, idx)) != string::npos)
    {
        substr = target.substr(idx, last_match - idx);

        if (!substr.empty())
        {
            out.push_back(substr);
        }

        idx = last_match + length;
    }

    substr = target.substr(idx);

    if (!substr.empty())
    {
        out.push_back(substr);
    }

    return out;
}
