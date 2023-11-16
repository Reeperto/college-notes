/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #7    : Text Adventure
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/25/23
 *********************************************************/
#include "assignment_07.h"

#include <iostream>
using namespace std;
/*********************************************************
 *
 * Text Adventure
 *
 * ________________________________________________________
 *
 * A simple text adventure game
 *
 * ________________________________________________________
 * INPUT:
 *  name: Name of the player
 *  direction: Direction the player will go
 *  monster: The scariest monster
 *
 * OUTPUT:
 *  bananas: Number of bananas player has
 *  oranges: Number of oranges player has
 *
 *********************************************************/
int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #7 : Text Adventure\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    string name;       // INPUT - Name of plauer
    string monster;    // INPUT - The scariest monster
    char direction;    // INPUT - Which door to go through
    int bananas = 5;   // PROCESSING/OUTPUT - Number of bananas
    int oranges = 3;   // PROCESSING/OUTPUT - Number of oranges
    int configuration; // PROCESSING - The random door configuration id
    bool escaped;      // PROCESSING - If the player escaped

    // INPUT - Get the player's name
    cout << "Please enter your name: ";
    cin >> name;

    // INPUT - Get the player's monster
    cout << "Name your scariest monster: ";
    cin >> monster;

    // PROCESSING - Seed the random number generation for the doors
    srand(500);

    do
    {
        // PROCESSING - Generate this turn's configuration. Either 0 or 1
        configuration = rand() % 2;

        // OUTPUT - Display current banana and orange count
        cout << name << ", you are in a room with 4 doors.\n\n";
        cout << "You are carrying " << bananas << " bananas and "
             << oranges << " oranges.\n";

        // INPUT - Get door direction from player
        direction = get_direction();

        cout << "\n";

        // PROCESSING - Determine which door configuration to use
        if (configuration == 0)
        {
            // PROCESSING - Match the direction to the right room according
            // to the configuration
            if (direction == 'N')
            {
                monsterRoom(bananas, oranges, monster);
            } else if (direction == 'E')
            {
                pictureRoom();
            } else if (direction == 'S')
            {
                genieRoom(bananas, oranges);
            } else if (direction == 'W')
            {
                escaped = true;
            }
        } else if (configuration == 1)
        {
            // PROCESSING - Match the direction to the right room according
            // to the configuration
            if (direction == 'N')
            {
                escaped = true;
            } else if (direction == 'E')
            {
                genieRoom(bananas, oranges);
            } else if (direction == 'S')
            {
                monsterRoom(bananas, oranges, monster);
            } else if (direction == 'W')
            {
                pictureRoom();
            }
        }

    } while (!escaped);

    // OUTPUT - Display the escape message along with the final score
    cout << "You found the exit!\n";
    cout << "Your score is " << bananas + oranges << "(" << bananas
         << " bananas and " << oranges << " oranges).\n";
    cout << "Bye bye!!!\n";
}
