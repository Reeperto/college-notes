/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #9    : Temperature Distribution
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/8/23
 *********************************************************/
#include <fstream>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Temperature Distribution
 *
 * ________________________________________________________
 *
 * Simulates the distribution of heat in a plate
 *
 * ________________________________________________________
 * INPUT:
 *  input_file: The file containing the initial temperatures and tolerance
 *  output_file: The file to contain the inner cell's temperatures
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
    // cout << " Assignment #9 : Temperature Distribution\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    ifstream input_file;  // INPUT - The file containing the initial
                          // temperatures and tolerance
    ofstream output_file; // INPUT - The file to contain the inner cell's
                          // temperatures
    string temporary_str; // PROCESSING - Temporary name of file
    double max_diff;      // PROCESSING - Largest previous temperature diff
    double epsilon;       // PROCESSING - Temperature tolerance
    double temp_val;      // PROCESSING - Temporary temperature
    double temp_grid[6][8]; // OUTPUT - Isothermal plate

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            temp_grid[i][j] = 0;
        }
    }

    // INPUT - Get input file
    cout << "Enter input file name: \n";
    getline(cin, temporary_str);
    input_file.open(temporary_str);
    cout << endl;

    // INPUT - Get output file
    cout << "Enter output file name: \n";
    getline(cin, temporary_str);
    output_file.open(temporary_str);
    cout << endl;

    // INPUT - Get the top temperature
    input_file >> temp_val;
    for (int i = 0; i < 8; ++i)
    {
        temp_grid[0][i] = temp_val;
    }

    // INPUT - Get the right temperature
    input_file >> temp_val;
    for (int i = 1; i < 5; ++i)
    {
        temp_grid[i][7] = temp_val;
    }

    // INPUT - Get the bottom temperature
    input_file >> temp_val;
    for (int i = 0; i < 8; ++i)
    {
        temp_grid[5][i] = temp_val;
    }

    // INPUT - Get the left temperature
    input_file >> temp_val;
    for (int i = 1; i < 5; ++i)
    {
        temp_grid[i][0] = temp_val;
    }

    // INPUT - Get the temperature tolerance
    input_file >> epsilon;

    // PROCESSING - While the temperature difference is out of tolerance,
    // continue to update cell temperatures
    do
    {
        max_diff = 0;
        // PROCESSING - Iterate row by row over the inner cells
        for (int i = 1; i < 5; ++i)
        {
            for (int j = 1; j < 7; ++j)
            {
                // PROCESSING - Update the current cell with the average of
                // it's neighboring cells
                temp_val = temp_grid[i][j];
                temp_grid[i][j] =
                    (temp_grid[i - 1][j] + temp_grid[i + 1][j] +
                     temp_grid[i][j - 1] + temp_grid[i][j + 1]) /
                    4.0;

                // PROCESSING - If the change in temperature of the cell is
                // larger than the current max, update the max
                if (temp_grid[i][j] - temp_val > max_diff)
                {
                    max_diff = temp_grid[i][j] - temp_val;
                }
            }
        }
    } while (max_diff > epsilon);

    // OUTPUT - Output the inner cell temperatures to the file and stdout
    for (int i = 1; i < 5; ++i)
    {
        for (int j = 1; j < 7; ++j)
        {
            output_file << temp_grid[i][j] << " ";
            cout << temp_grid[i][j] << " ";
        }
        output_file << "\n";
        cout << "\n";
    }
}
