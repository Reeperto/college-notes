#include <iostream>
using namespace std;

int main()
{
    int num1, num2, sum;

	// Prompt for the first whole number
    cout << "Enter in a whole number: ";
    cin >> num1;

	// Prompt for the another whole number
    cout << "Enter in another whole number: ";
    cin >> num2;

    // Calculate their sum
    sum = num1 + num2;

    // Display the sum
    cout << "The sum of " << num1 << " and " << num2 << " is " << sum << "\n";

    return 0;
}
