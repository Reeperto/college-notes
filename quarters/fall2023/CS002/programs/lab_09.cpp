/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #9           : Pass by Reference
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/20/23
 *********************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Pass by Reference
 *
 * ________________________________________________________
 *
 * A program that reads in a data file of numbers and calculates the mean,
 * max, and mean
 *
 * ________________________________________________________
 * INPUT:
 * 	exercise: Which exercise to run
 * 	seed: Random seed value
 *
 * OUTPUT:
 *  min: Min of data
 *  max: Max of data
 *  mean: Mean of data
 *
 *********************************************************/

void CalculateNumberDatStats(int &min, int &max, double &mean);
bool CalculateFileStats(string path, int &min, int &max, double &mean);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #9       : Pass by Reference\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    string input_path; // INPUT - File path to open
    int exercise;      // INPUT - Which exercise to run
    int seed;          // INPUT - Random seed value
    int min;           // OUTPUT - Min of data
    int max;           // OUTPUT - Max of data
    double mean;       // OUTPUT - Mean of data

    // INPUT - Determine which exercise the user will run
    cout << "Which exercise? ";
    cin >> exercise;

    cout << "Enter seed value: ";
    cin >> seed;

    srand(seed);

    // PROCESSING - Generate numbers.dat
    ofstream out_file("numbers.dat");
    int quantity = rand() % 10000 + 100;

    for (int i = 0; i < quantity; i++)
    {
        out_file << (rand() % 20000 - 1000) << endl;
    }

    out_file.close();

    // PROCESSING - Determine which exercise to run
    if (exercise == 1)
    {
        // PROCESSING - Calculate data based on the numbers.dat file
        CalculateNumberDatStats(min, max, mean);

        // OUTPUT - Output the number statistics
        cout << "The min is: " << min << "\n";
        cout << "The max is: " << max << "\n";
        cout << "The average is: " << mean << "\n";
    } else if (exercise == 2)
    {
        // INPUT - Get the file to open
        cout << "Enter the name of the file: ";
        cin >> input_path;

        // PROCESSING - Calculate the file statistics for the given file
        // path
        if (!CalculateFileStats(input_path, min, max, mean))
        {
            // OUTPUT - Notify the user that the file cant be opened
            cout << "Cannot open the file!\n";
        } else
        {
            // OUTPUT - Output the number statistics
            cout << "The min is: " << min << "\n";
            cout << "The max is: " << max << "\n";
            cout << "The average is: " << mean << "\n";
        }
    }

    return 0;
}

void CalculateNumberDatStats(int &min, int &max, double &mean)
{
    int current_number = 0;
    int accumulator = 0;
    int count = 0;

    min = 0;
    max = 0;
    mean = 0;

    ifstream input_file("numbers.dat");

    while (input_file >> current_number)
    {
        accumulator += current_number;
        ++count;

        if (current_number > max)
        {
            max = current_number;
        } else if (current_number < min)
        {
            min = current_number;
        }
    }

    mean = accumulator / (double)count;

    input_file.close();
}

bool CalculateFileStats(string path, int &min, int &max, double &mean)
{
    int current_number = 0;
    int accumulator = 0;
    int count = 0;

    min = 0;
    max = 0;
    mean = 0;

    ifstream input_file(path);

    if (!input_file.is_open())
    {
        return false;
    }

    while (input_file >> current_number)
    {
        accumulator += current_number;
        ++count;

        if (current_number > max)
        {
            max = current_number;
        } else if (current_number < min)
        {
            min = current_number;
        }
    }

    mean = accumulator / (double)count;

    input_file.close();

    return true;
}
