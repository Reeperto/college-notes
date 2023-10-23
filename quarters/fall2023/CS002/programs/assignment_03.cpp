/*********************************************************
 * AUTHOR 			: Eli Griffiths
 * Assignment #3    : Mathematics Specification
 * CLASS 			: CS 002
 * SECTION 			: Asynchronous
 * Due Date 		: 9/20/23
 *********************************************************/
#include <cmath>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Mathematics Specification
 *
 * ________________________________________________________
 *
 * A calculator app that support varius mathematical operations
 *
 * ________________________________________________________
 * INPUT:
 * 	operation: The operation the user wants to perform
 * 	number1, number, number3 : The possible numerical inputs the user
 *                             can input based on the operation
 *
 * OUTPUT:
 * 	result: The result of the computation or an error in the input
 *
 *********************************************************/

int main()
{

    string operation; // INPUT - The operation the user wants to perform
    double number1;   // INPUT - First possible numeric value
    double number2;   // INPUT - Second possible numeric value
    double number3;   // INPUT - Third possible numeric value
    double result;    // OUTPUT - The calculated output

    // // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #3  : Mathematics Specification\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    // INPUT - Get operation
    cout << "Please choose an operation: ";
    cin >> operation;

    // OUTPUT / PROCESSING - If the operation is not valid, error out.
    if (operation != "addition" && operation != "subtraction" &&
        operation != "division" && operation != "multiplication" &&
        operation != "fabs" && operation != "sqrt" &&
        operation != "quadratic" && operation != "pythagorean")
    {
        cout << "Error: Operation not supported.\n";
        return 0;
    }

    // INPUT - Get first number
    cout << "Enter your first number: ";
    cin >> number1;

    // PROCESSING - Check if the operation is one that only requires a
    // single number
    if (operation == "sqrt")
    {
        // OUTPUT - Display the equation
        cout << "Equation: sqrt(" << number1 << ")"
             << "\n\n";

        if (number1 < 0)
        {
            cout << "Error: Cannot take square root of a negative "
                    "number.\n";
            return 0;
        }

        result = sqrt(number1);
    } else if (operation == "fabs")
    {
        // OUTPUT - Display the equation
        cout << "Equation: fabs(" << number1 << ") "
             << "\n\n";
        result = fabs(number1);
    } else
    {
        // INPUT - All other functions required 2 numbers or more, so
        // prompt now for the second number
        cout << "Enter your second number: ";
        cin >> number2;

        // PROCESSING - Check if the operation is one that only needs 2
        // values and compute
        if (operation == "addition")
        {
            // OUTPUT - Display the equation
            cout << "Equation: " << number1 << " + " << number2 << "\n\n";
            result = number1 + number2;
        } else if (operation == "subtraction")
        {
            // OUTPUT - Display the equation
            cout << "Equation: " << number1 << " - " << number2 << "\n\n";
            result = number1 - number2;
        } else if (operation == "multiplication")
        {
            // OUTPUT - Display the equation
            cout << "Equation: " << number1 << " * " << number2 << "\n\n";
            result = number1 * number2;
        } else if (operation == "division")
        {
            // OUTPUT - Display the equation
            cout << "Equation: " << number1 << " / " << number2 << "\n\n";

            if (number2 == 0)
            {
                cout << "Error: Cannot divide by zero.\n";
                return 0;
            }

            result = number1 / number2;
        } else if (operation == "pythagorean")
        {
            // OUTPUT - Display the equation
            cout << "Equation: sqrt(" << number1 << "^2 + " << number2
                 << "^2)"
                 << "\n\n";
            result = sqrt(number1 * number1 + number2 * number2);
        } else
        {
            // INPUT - The only operation left is the quadratic which
            // requires three numbers. Therefore prompt the user for the
            // third number
            cout << "Enter your third number: ";
            cin >> number3;

            cout << "Equation: " << number1 << "x^2 + " << number2
                 << "x + " << number3 << " = 0\n\n";

            // PROCESSING - If coefficient of x^2 is 0, the equation is
            // linear and therefore solve it without the quadratic formula
            if (number1 == 0)
            {
                cout << "Result: " << -number3 / number2 << "\n";
                return 0;
            }

            // PROCESSING - Calculate the discriminant. If:
            // 	discriminant < 0 => The roots are imaginary, hence there is
            // 	                    a square root of a negative in the
            //                      answer. Error out.
            //
            // 	discriminant = 0 => There is a single root
            //
            // 	discriminant > 0 => There are two real roots
            double discriminant =
                number2 * number2 - 4 * number1 * number3;

            // OUTPUT - Present the correct error or number of results
            if (discriminant < 0)
            {
                cout << "Error: Cannot take square root of a negative "
                        "number.\n";
            } else if (discriminant == 0)
            {
                cout << "\n"
                     << "Result: " << -number2 / (2 * number1) << "\n";
            } else
            {
                cout << "Results: "
                     << (-number2 + sqrt(discriminant)) / (2 * number1)
                     << ", "
                     << (-number2 - sqrt(discriminant)) / (2 * number1)
                     << "\n";
            }

            return 0;
        }
    }

    // OUTPUT - For all single answer operations, output their result
    cout << "Result: " << result << "\n";
    return 0;
}
