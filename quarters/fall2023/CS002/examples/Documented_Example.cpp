/*******************************************************
 * AUTHOR       : ##### ########
 * Assignment #1: Madlibs
 * CLASS        : CS002
 * SECTION      : MW: 7:00a - 9:05a  TTh: 7:00a - 8:25 a
 * Due Date     : 9/14/18
 ******************************************************/

#include <iostream>

using namespace std;
/******************************************************
 *
 * Create a Madlib
 * ____________________________________________________
 * This program accepts 10 string inputs from the
 *  user, creates a story and outputs it to the
 *  monitor.
 * ____________________________________________________
 * INPUT:
 *  name1: a name --> input from the user
 *  creature: a creature --> input from the user
 *  weapon: a weapon --> input from the user
 *  villain: name for a villain --> input from the user
 *  place: a place --> input from the user
 *  planet: a planet --> input from the user
 *  adjective1: an adjective --> input from the user
 *  adjective2: another adjective --> input from the user
 *  organ: name of an organ --> input from the user
 *  bodypart: name of a body part --> input from the user
 *
 * OUTPUT:
 *  story:  outputs the story with the 10 user inputs 
 *          inserted into the story 
 *******************************************************/

int main()
{
    //constants
    const string MEASURINGSTICK(80, '-'); //OUTPUT - a tool for measuring

    //variables	- Data Table
    string name1;       //INPUT - a name
    string creature;    //INPUT - a creature
    string weapon;      //INPUT - a weapon
    string villain;     //INPUT - a name for a villain
    string place;       //INPUT - a place
    string planet;      //INPUT - a place
    string adjective1;  //INPUT - an adjective
    string adjective2;  //INPUT - another adjective
    string organ;       //INPUT - an organ
    string bodypart;    //INPUT - a body part
    
	
    //OUTPUT - display header information
    cout << "*********************************************************\n";
    cout << "       Programmed by: ###### #######\n";
    cout << "       Student ID   : 10117293\n";
    cout << "       CS002        : MW 7:00a - 9:05a TTh: 7:00a - 8:25a\n";
    cout << "       Assigment # 1: Madlibs\n";
    cout << "*********************************************************\n";
    cout << "\n";

    //INPUT -- get various input strings from the user to create a story
    cout << "Please enter a name: \n";
    cin  >> name1;

    cout << "\nPlease enter the name of a creature(mythical)/animal: \n";
    cin  >> creature;

    cout << "\nPlease enter the name of a wepon: \n";
    cin  >> weapon;

    cout << "\nPlease enter the name for a villain: \n";
    cin  >> villain;

    cout << "\nPlease enter the name of a place: \n";
    cin  >> place;

    cout << "\nPlease enter the name of a planet: \n";
    cin  >> planet;

    cout << "\nPlease enter an adjective: \n";
    cin  >> adjective1;

    cout << "\nPlease enter the name of another adjective: \n";
    cin  >> adjective2;

    cout << "\nPlease enter the name of an organ: \n";
    cin  >> organ;

    cout << "\nPlease enter the name of a body part: \n";
    cin  >> bodypart;

    //OUTPUT - display the story with the user inputs inserted into the story
    cout << "\n" << MEASURINGSTICK << "\n";

    //first paragraph
    cout << "The year is 20XX, humanity is in constant conflict with the"
         << " space " << creature << "s.\n";
    cout << "These ravenous monsters should not be taken lightly, however, "
         << "there are tales of\n";
    cout << "one being that leads the offensive against these beasts, its name "
         << "is " << name1 <<".\n";
    cout << "Today " << name1 << " will head out to the most dangerous mission "
         << "to date, that is to\n";
    cout << "go to " << planet << " and defeat the evil lord " << villain
         << " and finish the war for good.\n";
    cout << "\n";

    //second paragraph
    cout << "The hero was at the local " << place << ", preparing it's next "
         << "move to infiltrate the\n";
    cout << "enemy base and kill its leader. The time was nigh, the hero "
         << "grabbed its trusty\n";
    cout << weapon << " and headed to " << planet << ". Landing on the planet "
         << "the hero was received\n";
    cout << "by the angry army of " << creature << "s that tried to kill our "
         << "hero, they where no match\n";
    cout << "for our hero. He purged all these atrocities from the universe "
         << "and was finnally\n";
    cout << "at it's final destination, " << villain << "'s lair.\n";
    cout << "\n";

    //third paragraph
    cout << "The time for the final battle had come, just as our hero was about"
         << " to enter the\n";
    cout << "base, a giant robot emerged from it and on it was " << villain
         << " riding it massive\n";
    cout << "as he was, our hero was not scared. " << villain << " jumped from "
         << "the platform and\n";
    cout << "struck the first hit. Our hero was " << adjective1 << " but he did"
         << " not give up and with\n";
    cout << "it's signature " << weapon << " landed a critical hit. "
         << villain << " was in awe.\n";
    cout << "With " << villain << " " << adjective2 << " it was time to strike "
         << "the final blow and end it.\n";
    cout << "Badly injured from it's " << bodypart << ", our hero knew it "
         << "couldn't fail. As he\n";
    cout << "prepared i'ts ultimate attack " << villain << " lunged at him, "
         << "the time was right\n";
    cout << "the hero launched it's attack and pierced " << villain << " right "
         << "in the " << organ <<".\n";
    cout << "the giant robot exploded in a thousand pieces. As fire rained "
         << "down from the sky \n";
    cout << "our hero, " << name1 << ", looked into the horizon wondering if "
         << "that was the last\n";
    cout << "battle, if humanity could finally have peace, he did not know "
         << "that, but one \n";
    cout << "thing he knew was that if that ever happened, he would be "
         << "prepared.\n";
    cout << "\n";

    cout << MEASURINGSTICK << "\n";

    return 0;
}
