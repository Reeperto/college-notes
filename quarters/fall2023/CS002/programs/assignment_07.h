#pragma once
#include <iostream>
using namespace std;

/*********************************************************
 * FUNCTION monsterRoom
 * ________________________________________________________
 * Display's the encounter with the player's scariest monster and steals
 * the player's fruits - returns nothing
 * ________________________________________________________
 * PRE-CONDITIONS
 *   bananas: Player's banana count
 *   oranges: Plauer's orange count
 *   monster: Player's feared monster
 *
 * POST-CONDITIONS
 *  The function updates the player's counts:
 *  -  bananas
 *  -  oranges
 *********************************************************/
void monsterRoom(int &bananas,   // IN/OUT - Banana count
                 int &oranges,   // IN/OUT - Orange count
                 string monster) // IN - The feared monster
{
    // OUTPUT - Display genie message
    cout << "WATCH OUT!!!\n";
    cout << monster
         << " attacks you and steals all of your bananas and oranges.\n";

    // PROCESSING - Update the scores
    bananas = oranges = 0;
}

/*********************************************************
 * FUNCTION genieRoom
 * ________________________________________________________
 * Display's the encounter with the genie and gives
 * the player fruits - returns nothing
 * ________________________________________________________
 * PRE-CONDITIONS
 *   bananas: Player's banana count
 *   oranges: Plauer's orange count
 *
 * POST-CONDITIONS
 *  The function updates the player's counts:
 *  -  bananas
 *  -  oranges
 *********************************************************/
void genieRoom(int &bananas, int &oranges)
{
    // OUTPUT - Display genie message
    cout << "!!POOF!!\n";
    cout << "A genie pops out and grants you 2 bananas and 1 orange.";

    // PROCESSING - Update the scores
    bananas += 2;
    oranges += 1;
}

/*********************************************************
 * FUNCTION drawPicture
 * ________________________________________________________
 * Display's a fun picture - returns nothing
 * ________________________________________________________
 * PRE-CONDITIONS
 *  - none
 * POST-CONDITIONS
 *  - none
 *********************************************************/
void drawPicture()
{
    cout << "        _--~~--_" << endl;
    cout << "      /~/_|  |_\\~\\" << endl;
    cout << "     |____________|" << endl;
    cout << "     |[][][][][][]|" << endl;
    cout << "   __| __         |__" << endl;
    cout << "  |  ||. |   ==   |  |" << endl;
    cout << " (|  ||__|   ==   |  |)" << endl;
    cout << "  |  |[] []  ==   |  |" << endl;
    cout << "  |  |____________|  |" << endl;
    cout << "  /__\\            /__\\" << endl;
    cout << "   ~~              ~~ " << endl;
    cout << endl;
}

/*********************************************************
 * FUNCTION pictureRoom
 * ________________________________________________________
 * Display's the encounter with the picture room and shows
 * the player the image - returns nothing
 * ________________________________________________________
 * PRE-CONDITIONS
 *  - none
 * POST-CONDITIONS
 *  - none
 *********************************************************/
void pictureRoom()
{
    cout << "You found a picture!\n";
    drawPicture();
};

/*********************************************************
 * FUNCTION get_direction
 * ________________________________________________________
 * Prompts the user for what direction door to go through. Does input
 * validation to ensure the direction is a cardinal direction and reprompts
 * for input - returns the direction they chose
 * ________________________________________________________
 * PRE-CONDITIONS
 *  - none
 * POST-CONDITIONS
 *  - none
 *********************************************************/
char get_direction()
{
    bool valid = false; // PROCESSING - Validity of user input
    char direction;     // INPUT/OUTPUT - The player's door choice

    do
    {
        cout << "Pick a door to enter by typing the direction it is in "
                "(N/E/S/W): ";
        cin >> direction;

        valid = (direction == 'N') || (direction == 'E') ||
                (direction == 'S') || (direction == 'W');

    } while (!valid);

    return direction;
}
