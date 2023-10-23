/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #6           : Manipulators and File IO
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/6/23
 *********************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
/*********************************************************
 *
 * Manipulators and File IO
 *
 * ________________________________________________________
 *
 * Process some input data and output the processed version
 *
 * ________________________________________________________
 * INPUT:
 * 	inFile: The text file with the input data
 *
 * OUTPUT:
 *
 *********************************************************/

int main()
{

    const double pi = 3.14159;

    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #6 : Manipulators and File IO\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    ifstream inFile;   // INPUT - Input data
    double length;     // PROCESSING - Length of rect.
    double width;      // PROCESSING - Width of rect.
    double radius;     // PROCESSING - Radius of circ.
    string first_name; // PROCESSING - Name of person
    string last_name;  // PROCESSING - Name of person
    int age;           // PROCESSING - Age of person
    double savings;    // PROCESSING - Money in savings
    double interest;   // PROCESSING - Rate of yearly interest
    char letter;       // PROCESSING - Letter of alphabet

    // INPUT - Open files to read
    inFile.open("inData.txt");

    // INPUT - Get rectangle dimensions
    inFile >> length >> width;

    // INPUT - Get radius of circle
    inFile >> radius;

    // INPUT - Get name and age of person
    inFile >> first_name >> last_name >> age;

    // INPUT - Get savings and interest rate
    inFile >> savings >> interest;

    // INPUT - Get the letter of the alphabet
    inFile >> letter;

    // OUTPUT - Set precision of decimals to two digits
    cout << setprecision(2);
    cout << fixed;

    // OUTPUT - Print calculated metrics of rect.
    cout << "Rectangle:\n";
    cout << "Length = " << length << ", ";
    cout << "width = " << width << ", ";
    cout << "area = " << length * width << ", ";
    cout << "perimeter = " << 2.0 * length + 2.0 * width << "\n\n";

    // OUTPUT - Print calculated metrics of circ.
    cout << "Circle:\n";
    cout << "Radius = " << radius << ", ";
    cout << "area = " << pi * radius * radius << ", ";
    cout << "circumference = " << 2.0 * pi * radius << "\n\n";

    // OUTPUT - Print person info
    cout << "Name: " << first_name << " " << last_name << ", ";
    cout << "age: " << age << "\n";

    // OUTPUT - Print savings and interest calculations
    cout << "Beginning balance = $" << savings << ", ";
    cout << "interest rate = " << interest << "\n";
    cout << "Balance at the end of the month = $"
            << savings * (1 + interest / 1200.0) << "\n\n";

    // OUTPUT - Print the next letter in the alphabet
    cout << "The character that comes after " << letter
            << " in the ASCII set is " << (char)(letter + 1) << "\n";

    return 0;
}
