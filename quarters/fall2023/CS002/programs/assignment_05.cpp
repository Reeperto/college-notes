/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #5    : Cipher
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 10/4/23
 *********************************************************/
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Cipher
 *
 * ________________________________________________________
 *
 * Encrypts and Decrypts ciphered messages
 *
 * ________________________________________________________
 * INPUT:
 * 	method: Are we encrypting or decrypting?
 * 	cipher: The encoding used for the message
 * 	message: The message to be encoded or decoded
 *
 * OUTPUT:
 *
 *
 *********************************************************/

int main()
{

    string method;  // INPUT - Are we encrypting or decrypting?
    string cipher;  // INPUT - The encoding used for the message
    string message; // INPUT - The message to be encoded or decoded

    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #5  : Cipher\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    // INPUT - Determine if user is encrypting or decrypting
    cout << "What is the method (encryption or decryption)? ";
    cin >> method;
    cout << "\n";

    if (method != "encryption" && method != "decryption")
    {
        cout << "Error: invalid method choice.\n";
        return 0;
    }

    // INPUT - Get cipher map
    cout
        << "What is the translation map (type 'default' to use default): ";
    cin >> cipher;
    cout << "\n";

    // PROCESSING - Get default cipher if user said 'default'
    if (cipher == "default")
    {
        cipher = "zyxwvutsrqponmlkjihgfedcba";
    } else
    {
        if (cipher.length() != 26)
        {
            cout << "Error: invalid translation map size.\n";
            return 0;
        }
    }

    // INPUT - Get the message
    cout << "What is the single word to translate: ";
    cin >> message;
    cout << "\n";

    if (method == "encryption")
    {

        // PROCESSING/OUTPUT - Make sure that the message is only lowercase
        // letters
        for (int i = 0; i < message.length(); ++i)
        {
            if (message[i] < 'a' || message[i] > 'z')
            {
                cout << "Error: encryption cannot be performed.\n";
                return 0;
            }
        }

        // OUTPUT - Encrypt the word and display it
        cout << "Encrypted word: ";
        for (int i = 0; i < message.length(); ++i)
        {
            cout << cipher[message[i] - 'a'];
        }
        cout << "\n";

    } else if (method == "decryption")
    {

        // PROCESSING/OUTPUT - Make sure that the cipher is only lowercase
        // letters, otherwise error out
        for (int i = 0; i < cipher.length(); ++i)
        {
            if (cipher[i] < 'a' || cipher[i] > 'z')
            {
                cout << "Error: decryption cannot be performed.\n";
                return 0;
            }
        }

        // PROCESSING/OUTPUT - Make sure that the message is only lowercase
        // letters, otherwise error out
        for (int i = 0; i < message.length(); ++i)
        {
            if (message[i] < 'a' || message[i] > 'z')
            {
                cout << "Error: decryption cannot be performed.\n";
                return 0;
            }
        }

        // OUTPUT - Decrypt the word and display it
        cout << "Decrypted word: ";
        for (int i = 0; i < message.length(); ++i)
        {
            cout << cipher[message[i] - 'a'];
        }
        cout << "\n";
    }

    return 0;
}
