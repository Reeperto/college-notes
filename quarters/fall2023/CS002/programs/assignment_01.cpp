/*********************************************************
 * AUTHOR          : Eli Griffiths
 * Assignment #1   : Madlibs
 * CLASS           : CS 002
 * SECTION         : Asynchronous
 * Due Date        : 9/6/23
 *********************************************************/
#import <iostream>
using namespace std;
/*********************************************************
 *
 * Adlib Generator
 *
 * ________________________________________________________
 *
 * This program takes in 11 different words from the user and inserts them into
 * a madlib story structure, outputting the madlib to the screen
 *
 * ________________________________________________________
 * INPUT:
 * 	noun1: A name
 * 	noun2: Another name
 * 	noun3: An item
 * 	noun4: An item
 * 	adjective1: An adjective
 * 	adjective2: An adjective
 * 	adjective3: An adjective
 * 	adjective4: An adjective
 *  plural_noun: A plural noun
 *  verb: A verb
 *  color: A color
 *  exclamation: An exclamation like "Yikes" without the exclmaation point
 *
 * OUTPUT:
 * 	story: The generated story by inserting all the inputs of the user into
 *         the madlib
 *
 *********************************************************/

int main() {
  const string measuring_stick(80, '-');

  string noun1 = "aaaaaaaaaa";       // INPUT - An item
  string noun2 = "aaaaaaaaaa";       // INPUT - An item
  string noun3 = "aaaaaaaaaa";       // INPUT - An item
  string noun4 = "aaaaaaaaaa";       // INPUT - An item
  string adjective1 = "aaaaaaaaaa";  // INPUT - An adjective
  string adjective2 = "aaaaaaaaaa";  // INPUT - An adjective
  string adjective3 = "aaaaaaaaaa";  // INPUT - An adjective
  string adjective4 = "aaaaaaaaaa";  // INPUT - An adjective
  string plural_noun = "aaaaaaaaaa"; // INPUT - A plural noun
  string verb = "aaaaaaaaaa";        // INPUT - A verb
  string color = "aaaaaaaaaa";       // INPUT - A color
  string exclamation = "aaaaaaaaaa"; // Input - An exclamation like "Yikes"
                                     // without the exclmaation point

  // OUTPUT - Class header information
  cout << "*****************************************\n";
  cout << " Programmed by : Eli Griffiths\n";
  cout << " Student ID    : 10680823\n";
  cout << " CS002         : Asynchronous\n";
  cout << " Assignment #1 : Madlibs\n";
  cout << "*****************************************\n";
  cout << "\n";

  // INPUT - Get all the various words from the user for the madlib
  cout << "Please enter a noun: ";
  cin >> noun1;

  cout << "Please enter another noun: ";
  cin >> noun2;

  cout << "Please enter an adjective: ";
  cin >> adjective1;

  cout << "Please enter a plural noun: ";
  cin >> plural_noun;

  cout << "Please enter an adjective: ";
  cin >> adjective2;

  cout << "Please enter an verb ending in 'ing': ";
  cin >> verb;

  cout << "Please enter a noun: ";
  cin >> noun3;

  cout << "Please enter a color: ";
  cin >> color;

  cout << "Please enter an adjective: ";
  cin >> adjective3;

  cout << "Please enter an exclamation without an '!': ";
  cin >> exclamation;

  cout << "Please enter a noun: ";
  cin >> noun4;

  cout << "Please enter an adjective: ";
  cin >> adjective4;

  // OUTPUT - Use the above input in the madlib
  cout << "\n" << measuring_stick << "\n";

  // Paragraph 1:
  cout << "  Once upon a time in a " << adjective1 << " kingdom, there lived a "
       << adjective2 << " " << noun1 << "\n"
       << "and a group of " << plural_noun << ". ";
  cout << "The " << noun1 << " was known for " << verb << " through the"
       << "\n"
       << "lush " << adjective3 << " forests, "
       << "and the " << plural_noun << " admired their " << color << " "
       << noun3 << ".\n";
  cout << "One day, a " << noun2 << " arrived, exclaiming \"" << exclamation
       << "!\" and challenging the\n"
       << noun1 << " to a duel."
       << "\n\n";

  // Paragraph 2:
  cout << "  The " << noun1 << " and the " << noun2
       << " prepared for the epic showdown. ";
  cout << "With\n"
       << adjective3 << " skill, the " << noun1 << " swung their " << color
       << " " << noun3 << ", while the\n"
       << noun2 << " countered with a lightning-fast " << noun4
       << " that left gashes on the\nground. ";
  cout << "Spectators gasped, and some even shouted \"" << exclamation
       << "!\" as the battle\nraged on. ";
  cout << "In the end, the " << noun2
       << " emerged victorious, earning the respect\nof the " << plural_noun
       << "."
       << "\n\n";

  // Paragraph 3:
  cout << "  With the duel settled, the " << noun1 << " and the " << noun2
       << " became fast friends,\nembarking on " << adjective4
       << " adventures together. ";
  cout << "They explored and discovered\nhidden treasures across " << color
       << " landscapes, and shared many laughs."
       << "\n";
  cout << "As they looked up at the " << adjective3 << " sky one evening, the "
       << noun1 << " said,\n\"" << exclamation
       << "! Life is truly amazing with a friend.\"";

  cout << "\n" << measuring_stick << "\n";
}
