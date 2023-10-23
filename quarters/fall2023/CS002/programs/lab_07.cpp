/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #7           : Liters and MPG
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/13/23
 *********************************************************/
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Liters and MPG
 *
 * ________________________________________________________
 *
 * Calculates the miles per gallon of a car and also compare mpg between
 * two cars
 *
 * ________________________________________________________
 * INPUT:
 * 	car1_liters: The number of liters car 1 consumed
 * 	car1_miles:  The number of miles car 1 drove
 * 	car2_liters: The number of liters car 2 consumed
 * 	car2_miles:  The number of miles car 2 drove
 * 	calc_again: If the user wants to calculate mpg again
 *
 * OUTPUT:
 * 	car1_mpg: The mpg of car 1
 * 	car2_mpg: The mpg of car 2
 *
 *********************************************************/

const double liter_to_gallons = 0.264179;

double mpgCalculator(double miles, double liters);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #7         : Liters and MPG\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    double car1_liters; // INPUT - The number of liters car 1 consumed
    double car1_miles;  // INPUT -  The number of miles car 1 drove
    double car1_mpg;    // OUTPUT - The mpg of car 1
    double car2_liters; // INPUT - The number of liters car 2 consumed
    double car2_miles;  // INPUT -  The number of miles car 2 drove
    double car2_mpg;    // OUTPUT - The mpg of car 2
    char calc_again =
        'n'; // INPUT - If the user wants to calculate mpg again

    // PROCESSING/OUTPUT - Set decimal precision to 4 places
    cout << setprecision(4) << fixed;

    do
    {
        // INPUT - Get the number of liters and miles the car traveled
        cout << "Enter the number of liters of gas consumed: \n";
        cin >> car1_liters;
        cout << "Enter the number of miles traveled: \n";
        cin >> car1_miles;

        // OUTPUT - Output miles per gallon the car gets
        cout << "This car gets " << mpgCalculator(car1_miles, car1_liters)
             << " miles per gallon.\n";

        // INPUT - Determine if user wants to calculate again
        cout << "Calculate again? \n";
        cin >> calc_again;
    } while (calc_again == 'y');

    // OUTPUT - Padding
    cout << "\n\n";

    // INPUT - Get the number of liters and miles the first car traveled
    cout << "Enter the number of liters consumed for the first car: \n";
    cin >> car1_liters;
    cout << "Enter the number of miles traveled for the first car: \n";
    cin >> car1_miles;

    // INPUT - Get the number of liters and miles the second car traveled
    cout << "Enter the number of liters consumed for the second car: \n";
    cin >> car2_liters;
    cout << "Enter the number of miles traveled for the second car: \n";
    cin >> car2_miles;

    // OUTPUT - Padding
    cout << "\n\n";

    car1_mpg = mpgCalculator(car1_miles, car1_liters);
    car2_mpg = mpgCalculator(car2_miles, car2_liters);

    // OUTPUT - Print the mpg for each car
    cout << "The first car gets " << car1_mpg << " miles per gallon.\n";
    cout << "The second car gets " << car2_mpg << " miles per gallon.\n";

    // OUTPUI - Print which car had better gas mileage
    if (car1_mpg > car2_mpg)
    {
        cout << "The first car has better gas mileage.\n";
    } else
    {
        cout << "The second car has better gas mileage.\n";
    }
}

double mpgCalculator(double miles, double liters)
{
    return miles / (liters * liter_to_gallons);
}
