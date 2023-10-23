/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #6    : Hangman
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/18/23
 *********************************************************/
#include <cctype>
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Hangman
 *
 * ________________________________________________________
 *
 * A game of hangman
 *
 * ________________________________________________________
 * INPUT:
 * 	phrase: The phrase to be solved for
 * 	unsolved: The unsolved version of the phrase
 * 	guessed: The letters that have been guessed
 *
 * OUTPUT:
 * 	unsolved
 *
 *********************************************************/

/// @brief Puts dashes in place of alphabetic characters in the phrase.
/// @param phrase the phrase to be solved
/// @return the phrase with all alphabetic characters converted to dashes
string setupUnsolved(string phrase);

/// @brief Replaces the dashes with the guessed character.
/// @param phrase the phrase to be solved
/// @param unsolved the phrase with dashes for all unsolved characters
/// @param guess the char containing the current guessed character
/// @return the new unsolved string with dashes replaced by new guess
string updateUnsolved(string phrase, string unsolved, char guess);

/// @brief Gets valid guess as input.
///
///    A guess is taken as input as a character. It is valid if
///    1) it is an alphabetic character; and
///    2) the character has not already been guessed
///
/// @param prevGuesses the string containing all characters guessed so far
/// @return a valid guess and only a valid guess as a character
char getGuess(string prevGuesses);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #6 : Hangman\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    string unsolved;  // INPUT/OUTPUT - The unsolved phrase
    string previous;  // INPUT - The previous unsolved phrase
    string phrase;    // INPUT - The phrase to be solved for
    string guessed;   // INPUT - The letters that have been guessed
    bool win = false; // PROCESSING - Has the user won?
    int guesses = 7;  // PROCESSING - How many guesses?

    // INPUT - Get the phrase
    cout << "Enter phrase: ";
    getline(cin, phrase);

    // PROCESSING - Obfuscate the phrase
    unsolved = previous = setupUnsolved(phrase);

    // OUTPUT - Show the unsolved phrase
    cout << "Phrase: " << unsolved << "\n";

    // PROCESSING - Start the main game loop
    do
    {
        // INPUT/PROCESSING - Get the user's guess and update the unsolved
        // phrase
        guessed += getGuess(guessed);
        unsolved = updateUnsolved(phrase, unsolved,
                                  guessed[guessed.length() - 1]);

        // PROCESSING - If updating the unsolved phrase did nothing, the
        // guess did not reveal any information and therefore was a wrong
        // guess.
        if (previous == unsolved)
        {
            --guesses;
        }
        previous = unsolved;

        // OUTPUT - Provide the user with the current state of the game
        // after their guess
        cout << "Guessed so far: " << guessed << "\n";
        cout << "Wrong guesses left: " << guesses << "\n";
        cout << unsolved << "\n\n";

        // PROCESSING - If the unsolved phrase is equivalent to the
        // original phrase, the player has revealed every hidden letter
        // before running out of guesses and therefore wins
        if (unsolved == phrase)
        {
            win = true;
        }

    } while (guesses > 0 && !win);

    // OUTPUT - Tell the user if they lost or won
    if (win)
    {
        cout << "Congratulations!! You won!\n";
    } else
    {
        cout << "BOOOO";
    }
}

char getGuess(string prevGuesses)
{
    char current_guess;
    bool valid = false;

    // INPUT - Get the guess
    cout << "Enter a guess: ";
    cin >> current_guess;

    do
    {
        // PROCESSING - A guess is valid if it follows this criteria
        //
        // 	- Is a letter of the alphabet
        // 	- Hasn't been guessed before
        // 	- Is lowercase
        //
        valid = (isalpha(current_guess) > 0) &&
                (prevGuesses.find(current_guess) == string::npos) &&
                (current_guess == tolower(current_guess));

        // INPUT - If the guess is invalid, then prompt for rentry
        if (!valid)
        {
            cout << "Invalid guess! Please re-enter a guess: ";
            cin >> current_guess;
        }

    } while (!valid);

    current_guess = tolower(current_guess);
    return current_guess;
}

string setupUnsolved(string phrase)
{
    string unsolved = "";

    // PROCESSING - Run through the phrase and find all instances of
    // letters and replace them with a dash. Leave any non-alphabet
    // characters in place
    for (int i = 0; i < phrase.length(); ++i)
    {
        if (isalpha(phrase[i]) > 0)
        {
            unsolved += '-';
        } else
        {
            unsolved += phrase[i];
        }
    }

    return unsolved;
}

string updateUnsolved(string phrase, string unsolved, char guess)
{
    for (int i = 0; i < phrase.length(); ++i)
    {
        // PROCESSING - If the guess is the same letter (case insensitive),
        // reveal the guess in the unsolved phrase
        if (guess == tolower(phrase[i]))
        {
            unsolved[i] = phrase[i];
        }
    }

    return unsolved;
}
