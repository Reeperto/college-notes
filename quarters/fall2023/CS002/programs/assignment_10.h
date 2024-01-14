#pragma once

#include <iostream>
#include <vector>
using namespace std;

/// @brief Draws the provided tic-tac-toe board to the screen
//  @param board is the tic-tac-toe board that should be drawn
void drawBoard(const vector<char> &board)
{
    for (int i = 0; i < 9; i += 3)
    {
        cout << "  " << board.at(i) << "  |  " << board.at(i + 1)
             << "  |  " << board.at(i + 2) << "  " << endl;
        if (i < 6)
        {
            cout << "-----|-----|-----" << endl;
        }
    }
    cout << endl;
}

/// @brief Fills vector with characters starting at lower case a.
///
///     The amount of the alphabet placed into the vector depends on its
///     size. When the vector is size 1 then it will have only character a.
///     When the vector is size 5 then it will have characters a to e.
///     When the vector is size 26 then it will have characters a to z.
///
/// @param v the vector to initialize
/// @pre-condition the vector size will never be over 26
void initVector(vector<char> &v)
{
    // PROCESSING - Iterate from the start of the vector to the end,
    // filling with the appropriate character relative to 'a'
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = 'a' + i;
    }
}

/// @brief Converts a character representing a cell to associated vector
/// index
/// @param the position to be converted to a vector index
/// @return the integer index in the vector, should be 0 to (vector size -
/// 1)
int convertPosition(char position) { return position - 'a'; }

/// @brief Predicate function to determine if a spot in board is available.
/// @param board the current tic-tac-toe board
/// @param position is an index into vector to check if available
/// @return true if position's state is available (not marked) AND is in
/// bounds
bool validPlacement(const vector<char> &board, int position)
{
    // PROCESSING - If the board at the position is not marked, then it is
    // valid
    if (board[position] != 'x' && board[position] != 'o')
    {
        return true;
    }
    return false;
}

/// @brief Acquires a play from the user as to where to put her mark
///
///     Utilizes convertPosition and validPlacement functions to convert
///     the user input and then determine if the converted input is a valid
///     play.
///
/// @param board the current tic-tac-toe board
/// @return an integer index in board vector of a chosen available board
/// spot
int getPlay(const vector<char> &board)
{
    int idx = 0;
    char position;

    // INPUT - Get a position for the board that is on the board and is
    // valid. Keep asking for input if the player provides a bad position
    do
    {
        cout << "Please choose a position: ";
        cin >> position;
        idx = convertPosition(position);
    } while (idx < 0 || idx >= 9 || !validPlacement(board, idx));

    return idx;
}

/// @brief Predicate function to determine if the game has been won
///
///     Winning conditions in tic-tac-toe require three marks from same
///     player in a single row, column or diagonal.
///
/// @param board the current tic-tac-toe board
/// @return true if the game has been won, false otherwise
bool gameWon(const vector<char> &board)
{
    char candidate;
    bool won = true;

    for (int i = 0; i < 3; ++i)
    {
        // PROCESSING - Check if any columns are winning
        candidate = board[i];
        if (board[i + 3] == candidate && board[i + 6] == candidate)
        {
            return true;
        }

        // PROCESSING - Check if any rows are winning
        candidate = board[3 * i];
        if (board[3 * i + 1] == candidate && board[3 * i + 2] == candidate)
        {
            return true;
        }
    }

    // PROCESSING - Check if main diagonal is winning
    candidate = board[convertPosition('a')];
    if (board[convertPosition('e')] == candidate &&
        board[convertPosition('i')] == candidate)
    {
        return true;
    }

    // PROCESSING - Check if anti diagonal is winning
    candidate = board[convertPosition('c')];
    if (board[convertPosition('e')] == candidate &&
        board[convertPosition('g')] == candidate)
    {
        return true;
    }

    return false;
}

/// @brief Predicate function to determine if the board is full
/// @param board the current tic-tac-toe board
/// @return true iff the board is full (no cell is available)
bool boardFull(const vector<char> &board)
{
    // PROCESSING - If there is any spot on the board that isnt marked with
    // and 'x' or 'o', then the board isnt full
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] != 'x' && board[i] != 'o')
        {
            return false;
        }
    }
    return true;
}

// Global constants for player representation
const int PLAYER1 = 0;
const int PLAYER2 = 1;
