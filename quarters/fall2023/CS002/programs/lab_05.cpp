/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #5           : More Loops
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 9/28/23
 *********************************************************/
#include <cstdlib>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * More Loops
 *
 * ________________________________________________________
 *
 * A program that:
 * 	- Generates three sequences given a start and end
 * 	- Determines the grade breakdown given student scores
 * 	- Does a series of coin tosses
 *
 * ________________________________________________________
 * INPUT:
 *  - excercise: The excercise the user wants to do
 * FOR EXERCISE #1
 *  - start: The range start
 *  - end: The range end
 *
 * FOR EXERCISE #2
 * 	- current_grade: The current student's score
 *
 * FOR EXERCISE #2
 * 	- flip_coin: Should a coin be flipped
 *
 * OUTPUT:
 * FOR EXERCISE #2
 * 	- a_grades: Number of A grades in the class
 * 	- b_grades: Number of B grades in the class
 * 	- c_grades: Number of C grades in the class
 * 	- d_grades: Number of D grades in the class
 * 	- f_grades: Number of F grades in the class
 *
 *********************************************************/

int main()
{
    int exercise;      // INPUT - Which exercise to do
    int start;         // INPUT - Beginning of range
    int end;           // INPUT - End of range
    int current_grade; // INPUT - Current students's score
    string flip_coin;  // INPUT - Should a coin be flipped
    int a_grades = 0;  // OUTPUT - Number of A grades in the class
    int b_grades = 0;  // OUTPUT - Number of B grades in the class
    int c_grades = 0;  // OUTPUT - Number of C grades in the class
    int d_grades = 0;  // OUTPUT - Number of D grades in the class
    int f_grades = 0;  // OUTPUT - Number of F grades in the class

    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #5 : More Loops\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    cout << "Which exercise? \n";
    cin >> exercise;

    if (exercise == 1)
    {
        // INPUT - Get the start and end of the first range
        cout << "Enter beginning and ending numbers, separated by space: "
                "\n";
        cin >> start >> end;

        // OUTPUT - Show the series [start, end]
        cout << start;
        for (int i = start + 1; i <= end; ++i)
        {
            cout << ", " << i;
        }
        cout << "\n";

        // INPUT - Get the start and end of the second range
        cout << "Enter beginning and ending numbers, separated by space: "
                "\n";
        cin >> start >> end;

        // OUTPUT - Show the series starting from start and increasing by 2
        // without exceeding end
        cout << start;
        for (int i = start + 2; i <= end; i += 2)
        {
            cout << ", " << i;
        }
        cout << "\n";

        // INPUT - Get the start and end of the third range
        cout << "Enter the beginning and largest positive numbers, "
                "separated by space: "
                "\n";
        cin >> start >> end;

        // OUTPUT - Show there series starting from start and multiplying
        // by -2 until end is reached
        cout << start;
        for (int i = start * -2; abs(i) <= end; i *= -2)
        {
            cout << ", " << i;
        }
        cout << "\n";
    } else if (exercise == 2)
    {
        current_grade = 0;
        while (current_grade >= 0)
        {
            cout << "Enter one or more grades, or -1 to stop: \n";
            cin >> current_grade;

            // PROCESSING - Match the given score to the correct letter
            // range
            if (current_grade >= 90)
            {
                a_grades += 1;
            } else if (current_grade < 90 && current_grade >= 80)
            {
                b_grades += 1;
            } else if (current_grade < 80 && current_grade >= 70)
            {
                c_grades += 1;
            } else if (current_grade < 70 && current_grade >= 60)
            {
                d_grades += 1;
            } else if (current_grade < 60 && current_grade >= 0)
            {
                f_grades += 1;
            }
        }

        // OUTPUT - Present the grade breakdown for each letter
        cout << "The grades breakdown is: \n";
        cout << "As: " << a_grades << "\n";
        cout << "Bs: " << b_grades << "\n";
        cout << "Cs: " << c_grades << "\n";
        cout << "Ds: " << d_grades << "\n";
        cout << "Fs: " << f_grades << "\n";
    } else if (exercise == 3)
    {
        flip_coin = "yes";

        while (flip_coin == "yes")
        {
            // INPUT - Determine if to the flip the coin or not
            cout << "Toss the coin? \n";
            cin >> flip_coin;

            if (flip_coin == "yes")
            {
                // PROCESSING - Generate randomnly 0 or 1.
                // 	0 => Heads
                // 	1 => Tails
                if (rand() % 2 == 0)
                {
                    cout << "heads\n";
                } else
                {
                    cout << "tails\n";
                }
            }
        }
    }
}
