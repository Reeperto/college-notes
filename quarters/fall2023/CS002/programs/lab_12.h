#pragma once

/*********************************************************
 * FUNCTION lower_char
 * ________________________________________________________
 * Takes a character and lowercases it if possible
 * ________________________________________________________
 * PRE-CONDITIONS
 *   c: The char
 *
 * POST-CONDITIONS
 *  returns the lowercased char (if possible)
 *********************************************************/
char lower_char(char c) // IN - Char to lower
{
    // PROCESSING - If in the uppercase alpha character range, make
    // lowercase
    if (c >= 'A' && c <= 'Z')
    {
        c = c + ('a' - 'A');
    }
    return c;
}

/*********************************************************
 * FUNCTION count_vowels
 * ________________________________________________________
 * Counts the number of vowels in a c-str
 * ________________________________________________________
 * PRE-CONDITIONS
 *   str: The c string
 *
 * POST-CONDITIONS
 *  returns the number of vowels
 *********************************************************/
int count_vowels(const char str[]) // IN - Input c-str
{
    char current = '\0';
    int count = 0;
    int i = 0;

    // PROCESSING - Iterate over string until its a null character
    while (str[i] != '\0')
    {
        current = lower_char(str[i]);

        // PROCESSING - If the current char is a vowel, add to the vowel
        // count
        count += (current == 'a' || current == 'e' || current == 'i' ||
                  current == 'o' || current == 'u');
        ++i;
    }

    return count;
}

/*********************************************************
 * FUNCTION count_consonants
 * ________________________________________________________
 * Counts the number of consonants in a c-str
 * ________________________________________________________
 * PRE-CONDITIONS
 *   str: The c string
 *
 * POST-CONDITIONS
 *  returns the number of consonants
 *********************************************************/
int count_consonants(const char str[]) // IN - Input c-str
{
    char current = '\0';
    int letters = 0;
    int i = 0;

    // PROCESSING - Iterate over string and count the total alpha
    // characters/letters
    while (str[i] != '\0')
    {
        current = lower_char(str[i]);
        letters += current >= 'a' && current <= 'z';
        ++i;
    }

    // PROCESSING - The number of consonants is the number of letters that
    // arent vowels
    return letters - count_vowels(str);
}

/*********************************************************
 * FUNCTION lowercase
 * ________________________________________________________
 * Modifies the string to be lowercased
 * ________________________________________________________
 * PRE-CONDITIONS
 *   str: The c string
 *
 * POST-CONDITIONS
 *   modifies str and makes it lowercase
 *********************************************************/
void lowercase(char str[]) // IN - Input c-str
{
    int i = 0;

    while (str[i] != '\0')
    {
        // PROCESSING - Replace every character with its lower-cased
        // version if possible
        str[i] = lower_char(str[i]);
        ++i;
    }
}

/*********************************************************
 * FUNCTION uppercase
 * ________________________________________________________
 * Modifies the string to be uppercased
 * ________________________________________________________
 * PRE-CONDITIONS
 *   str: The c string
 *
 * POST-CONDITIONS
 *   modifies str and makes it uppercase
 *********************************************************/
void uppercase(char str[]) // IN - Input c-str
{
    char current;
    int i = 0;

    while (str[i] != '\0')
    {
        current = str[i];

        // PROCESSING - If the character is lowercase, uppercase it.
        // Otherwise leave it alone
        if (current >= 'a' && current <= 'z')
        {
            str[i] = current - ('a' - 'A');
        }
        ++i;
    }
}
