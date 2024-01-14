/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Assignment #10   : Tic-Tac-Toe
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/18/23
 *********************************************************/
#include "assignment_10.h"
using namespace std;
/*********************************************************
 *
 * Tic-Tac-Toe
 *
 * ________________________________________________________
 *
 * A program that is a game of tic-tac-toe
 *
 * ________________________________________________________
 * INPUT:
 *
 * OUTPUT:
 *
 *********************************************************/

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Assignment #10 : Tic-Tac-Toe\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    vector<char> board(9, 0); // PROCESSING - The tic-tac-toe board
    int turn = PLAYER1;       // PROCESSING - Which player's turn it is
    int idx = 0;              // PROCESSING - The index into the board
    bool won;                 // PROCESSING - Has any player won
    bool full;                // PROCESSING - Is the board full

    // PROCESSING - Initialize the board
    initVector(board);

    // OUTPUT - Display the board in its initial state
    drawBoard(board);

    // PROCESSING - Play the game until the board is full or someone wins
    do
    {
        // INPUT - Get a valid position from the current player
        idx = getPlay(board);

        // PROCESSING - Place the corresponding marker based on whose turn
        // it is
        if (turn == PLAYER1)
        {
            board[idx] = 'x';
            turn = PLAYER2;
        } else if (turn == PLAYER2)
        {
            board[idx] = 'o';
            turn = PLAYER1;
        }

        // PROCESSING - Check if board is full or is in a winning state
        won = gameWon(board);
        full = boardFull(board);

        // OUTPUT - Display the board in its current state
        drawBoard(board);

    } while (!won && !full);

    // OUTPUT - If the board is full but no one won, then no one wins.
    // Otherwise the player who played last turn is the winner.
    if (full && !won)
    {
        cout << "No one wins.\n";
    } else if (won)
    {
        if (turn == PLAYER1)
        {
            cout << "Player 2 wins!!\n";
        } else if (turn == PLAYER2)
        {
            cout << "Player 1 wins!!\n";
        }
    }
}
