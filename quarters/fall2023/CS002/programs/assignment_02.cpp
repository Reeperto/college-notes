/*********************************************************
 * AUTHOR 			: Eli Griffiths
 * Assignment #2 	: Cash Register
 * CLASS 			: CS 002
 * SECTION 			: Asynchronous
 * Due Date 		: 9/13/23
 *********************************************************/
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Cash Register
 *
 * ________________________________________________________
 *
 * A program that simulates a cash register
 *
 * ________________________________________________________
 * INPUT:
 *  - purchase: The price of the purchase
 *  - recieved: Money given to the register
 *
 * OUTPUT:
 *  - dollars:  The number of dollars in the change
 *  - quarters: The number of quarters in the change
 *  - dimes:    The number of dimes in the change
 *  - nickels:  The number of nickels in the change
 *  - pennies:  The number of pennies in the change
 *
 *********************************************************/

int main()
{
    float purchase; // INPUT - The price of the purchase
    float recieved; // INPUT - Money given to the register
    float change;   // CALC/OUTPUT - Calculated change
    int dollars;    // OUTPUT - Number of dollars in the change
    int quarters;   // OUTPUT - Number of quarters in the change
    int dimes;      // OUTPUT - Number of dimes in the change
    int nickels;    // OUTPUT - Number of nickels in the change
    int pennies;    // OUTPUT - Number of pennies in the change

    // // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by : Eli Griffiths\n";
    // cout << " Student ID    : 10680823\n";
    // cout << " CS002         : Asynchronous\n";
    // cout << " Assignment #2 : Cash Register\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    // INPUT - Get purchase and recieved quantities
    cout << "Enter purchase amount: ";
    cin >> purchase;
	cout << "\n";

    cout << "Enter amount received: ";
    cin >> recieved;
	cout << "\n";

    // PROCESSING - Calculate the change and work starting from
    // pennies to figure out the proper split of denominations

    change = recieved - purchase;
    pennies = static_cast<int>(change * 100 + 0.5);

    dollars = pennies / 100;
    pennies %= 100;
    quarters = pennies / 25;
    pennies %= 25;
    dimes = pennies / 10;
    pennies %= 10;
    nickels = pennies / 5;
    pennies %= 5;

    // OUTPUT - Display the user their change and the denominations
    cout << "Total Change: $" << change << "\n\n";

    cout << "dollars " << dollars << "\n";
    cout << "quarters " << quarters << "\n";
    cout << "dimes " << dimes << "\n";
    cout << "nickels " << nickels << "\n";
    cout << "pennies " << pennies << "\n";
}
