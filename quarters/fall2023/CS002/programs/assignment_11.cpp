/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #10   : Breakfast Billing System
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/25/23
 *********************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*********************************************************
 *
 * Breakfast Billing System
 *
 * ________________________________________________________
 *
 * A program that allows the user to pick items from a menu and calculate
 * the total price
 *
 * ________________________________________________________
 * INPUT:
 *  item_idx: The item on the menu the user orders
 *  quantity: The number of items the user orders
 *  input_name: The name of the file with the menu
 * OUTPUT:
 *
 *********************************************************/

struct MenuItemType
{
    string menuItem;
    double menuPrice;
};

void getData(string file_name, vector<MenuItemType> &menuList);
void showMenu(vector<MenuItemType> &menuList);
void printCheck(vector<MenuItemType> &menuList, vector<int> &counts);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #10 : Breakfast Billing System\n";
    // cout << "*****************************************\n";
    // cout << "\n"

    int item_idx;      // INPUT - The item on the menu the user orders
    int quantity;      // INPUT - The number of items the user orders
    string input_name; // INPUT - The name of the file with the menu
    vector<MenuItemType> menu_list; // PROCESSING - The list of menu items
    vector<int> bill_count; // PROCESSING - The number of ordered items

    // PROCESSING - Make all money appear as two figures after the decimal
    cout << fixed << setprecision(2);

    // INPUT - Get the menu file
    cout << "Enter filename: \n";
    getline(cin, input_name);
    cout << "\n";

    // PROCESSING - Extract the menu data from the menu file path and make
    // the count's vector the same size
    getData(input_name, menu_list);
    bill_count.resize(menu_list.size());

    do
    {
        // OUTPUT - Display the menu choices to the user
        showMenu(menu_list);

        // INPUT - Get the menu item the user wishes to order
        cout << "Enter 0 when you finish your order.\n\n";
        cout << "Enter the item number: ";
        cin >> item_idx;

        // PROCESSING/INPUT - If the user chooses an actual item on the
        // menu, get the number that they want to order
        if (item_idx != 0)
        {
            cout << "\n";
            cout << "How many would you like to order? ";
            cin >> quantity;

            // PROCESSING - Add the ordered amount to the current order
            // counts
            bill_count[item_idx - 1] += quantity;
        }

        cout << "\n\n\n";
    } while (item_idx != 0);

    // OUTPUT - Calculate and display the final bill
    printCheck(menu_list, bill_count);
    cout << endl;
}

/*********************************************************
 * FUNCTION getData
 * ________________________________________________________
 * Takes a file path and reads the menu listings in it to a vector
 * ________________________________________________________
 * PRE-CONDITIONS
 *  file_name: The path to the menu file
 *  menuList: An empty vector to store the menu data
 *
 * POST-CONDITIONS
 *  fills menuList with the menu data
 *********************************************************/
void getData(string file_name, vector<MenuItemType> &menuList)
{
    MenuItemType item;
    ifstream file(file_name);
    string current_line;
    int dollar_sign;

    // PROCESSING - Get each line of the input menu
    while (getline(file, current_line))
    {
        // PROCESSING - Use the dollar sign as a "pivot" to split each line
        // into the menu item's name and its price
        dollar_sign = current_line.find("$");
        item.menuItem = current_line.substr(0, dollar_sign - 1);
        item.menuPrice = stod(current_line.substr(dollar_sign + 1));
        menuList.push_back(item);
    }

    file.close();
}

/*********************************************************
 * FUNCTION showMenu
 * ________________________________________________________
 * Pretty prints the given menu
 * ________________________________________________________
 * PRE-CONDITIONS
 *  menuList: A vector to with menu data
 *
 * POST-CONDITIONS
 *  none
 *********************************************************/
void showMenu(vector<MenuItemType> &menuList)
{
    // OUPUT - Display banner
    cout << "Welcome to Johnny's Restaurant\n\n";
    cout << setw(19) << "Menu\n\n";

    // OUTPUT - Iterate through the menu and display the item, its number,
    // and its price
    for (int i = 0; i < menuList.size(); ++i)
    {
        cout << left << setw(3) << to_string(i + 1) + "." << setw(20)
             << menuList[i].menuItem << "$" << setw(5) << right
             << menuList[i].menuPrice << "\n";
    }
    cout << "\n";
}

/*********************************************************
 * FUNCTION printCheck
 * ________________________________________________________
 * Calcultes interest and prints the final bill based on what was ordered
 * ________________________________________________________
 * PRE-CONDITIONS
 *  menuList: A vector of all the menu items
 *  counts: A vector of the same length as menuList where the data is
 *          parallel to menuList and represents how many of that item the
 *          user ordered
 *
 * POST-CONDITIONS
 *  none
 *********************************************************/
void printCheck(vector<MenuItemType> &menuList, vector<int> &counts)
{
    double total_cost = 0;
    double current_cost = 0;

    // OUPUT - Display banner
    cout << fixed << setprecision(2);
    cout << "Welcome to Johnny's Restaurant\n\n";
    cout << setw(19) << "SALE\n\n";

    for (int i = 0; i < menuList.size(); ++i)
    {
        if (counts[i] != 0)
        {
            // PROCESSING - Caclulate the current cost of this single item
            // ordered however many times the user chose
            current_cost = menuList[i].menuPrice * counts[i];

            cout << left << setw(3) << counts[i] << setw(20)
                 << menuList[i].menuItem << "$" << setw(5) << right
                 << current_cost << "\n";

            // PROCESSING - Add cost for this item to total
            total_cost += current_cost;
        }
    }

    // OUTPUT - Display the 5% tax
    cout << "Tax" << setw(21) << right << "$" << setw(5) << right
         << total_cost * 0.05 << "\n";
    cout << "-----------------------------\n";

    // OUTPUT - Display the total + 5% tax
    cout << "Amount Due" << setw(14) << right << "$" << setw(5) << right
         << total_cost * 1.05 << "\n";
}
