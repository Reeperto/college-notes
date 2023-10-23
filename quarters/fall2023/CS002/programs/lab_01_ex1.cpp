/*********************************************************
 * AUTHOR   : Eli Griffiths and Sophie Chen
 * Lab #1   : Mathematical Operations (with integers)
 * CLASS    : CS 002
 * SECTION  : Asynchronous
 * Due Date : 9/1/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * MATHEMATICAL OPERATIONS (WITH INTEGERS)
 *
 * ________________________________________________________
 *
 * This program accepts two integers from the user
 * 	and performs:
 * 		- addition
 * 		- multiplication
 * 		- division
 * 		- modulo
 *
 * 	on the two integers and displays the result of each
 * 	operation.
 *
 * ________________________________________________________
 * INPUT:
 * 	num1: First integer operand -> Input from user
 * 	num2: Second integer operand -> Input from user
 *
 * OUTPUT:
 * 	sum: Sum of both integers
 * 	product: Product of both integers
 * 	division: Division of integer 1 by integer 2
 * 	modulu: Modulus of integer 1 by integer 2
 *
 *********************************************************/
int main()
{
    int num1; // INPUT - First intgeger operand
    int num2; // INPUT - Second integer operand

    int sum;      // OUTPUT - Sum of both integers
    int product;  // OUTPUT - Product of both integers
    int division; // OUTPUT - Division of num1 by num2
    int modulo;   // OUTPUT - Modulus of num1 by num2

    /* cout << "*****************************************\n";
    cout << " Programmed by: Eli Griffiths and Sophie Chen\n";
    cout << " Student ID   : 10680823\n";
    cout << " CS002        : Asynchronous\n";
    cout << " Lab #1       : Mathematical Operations (with integers)\n";
    cout << "*****************************************\n"; */

    // INPUT: Prompting the user for the first integer operand and storing
    // in num1
    cout << "Enter the first integer: ";
    cin >> num1;

    // INPUT: Prompting the user for the second integer operand and storing
    // 	in num2
    cout << "Enter the second integer: ";
    cin >> num2;

    // PROCESSING: Operate on num1 and num2, storing their outputs in their
    // respective data variable
    sum = num1 + num2;
    product = num1 * num2;
    division = num1 / num2;
    modulo = num1 % num2;

    // OUTPUT: Display the result of each operation in the form of
    // 	num1 [operator] num2 = [result]
    // with a newline after each.
    cout << num1 << " + " << num2 << " = " << sum << "\n";
    cout << num1 << " * " << num2 << " = " << product << "\n";
    cout << num1 << " / " << num2 << " = " << division << "\n";
    cout << num1 << " % " << num2 << " = " << modulo << "\n";

    return 0;
}
