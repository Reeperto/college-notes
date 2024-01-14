/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Final Project    : Battleship
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 12/9/23
 *********************************************************/
#include "header.h"
/*********************************************************
 *
 * Battleship
 *
 * ________________________________________________________
 *
 * A game of battleship that supports player vs player or player vs
 * computer modes
 *
 * ________________________________________________________
 * INPUT:
 *  game_selection: If the game is player vs. player or player vs. computer
 *  seed: An optional randomness seed for testing/predictability
 * OUTPUT:
 *  winner: Who won the game
 *
 *********************************************************/
int main()
{
    PlayerBoard player1;   // PROCESSING - Player 1's board + fleet
    PlayerBoard player2;   // PROCESSING - Player 2's board + fleet
    ComputerAI computer;   // PROCESSING - The AI's board + fleet
    Player current_player; // PROCESSING - Current player's turn
    bool turn_over;        // PROCESSING - Is the current turn over
    bool ai_game;          // PROCESSING - Is game PvP or PvC
    Player winner;         // OUTPUT - Who won the game
    int game_selection;    // INPUT - Is game PvP or PvC
    int seed;              // INPUT - Random number seed

    cout << "Enter a seed for the random number generator (0 for random "
            "seed): ";
    cin >> seed;

    if (seed == 0)
    {
        srand(time(NULL));
    } else
    {
        srand(seed);
    }

    // INPUT - Determine if user wants to play against another player or
    // the computer
    cout << "What mode do you want to play?\n";
    cout << "1.) Player vs Player"
         << "\n";
    cout << "2.) Player vs Computer"
         << "\n";

    cin >> game_selection;

    // PROCESSING - Make this game Player v. Computer if they chose option
    // 2
    ai_game = game_selection == 2;

    // INPUT - Go through the board setup for player 1
    cout << "Player 1 set your board.\n";
    init_fleet(player1);

    // PROCESSING - If the game is not computer vs player, then setup a
    // second player
    if (!ai_game)
    {
        // INPUT - Go through the board setup for player 2
        cout << "Player 2 set your board.\n";
        init_fleet(player2);
    } else
    {
        // PROCESSING - Create the computer AI fleet
        ai_init_fleet(computer);
    }

    // PROCESSING - Start the game with player 1
    current_player = PLAYER1;

    // PROCESSING - While nobody has won, play goes back and forth
    do
    {
        turn_over = false;

        // OUTPUT - Show which player's turn it is
        switch (current_player)
        {
        case PLAYER1:
            cout << "Your turn player 1.\n";
            break;
        case PLAYER2:
            cout << "Your turn player 2.\n";
            break;
        case COMPUTER:
            cout << "It is the AI's turn.\n";
            break;
        default:
            break;
        }

        // PROCESSING - Let the current player's turn run until they miss
        do
        {
            switch (current_player)
            {
            case PLAYER1:
                if (ai_game)
                {
                    player_turn(player1, computer.board, turn_over, winner,
                                ai_game);
                } else
                {
                    player_turn(player1, player2, turn_over, winner,
                                ai_game);
                }
                break;
            case PLAYER2:
                player_turn(player2, player1, turn_over, winner, ai_game);
                break;
            case COMPUTER:
                ai_turn(computer, player1, turn_over, winner);
            default:
                break;
            }

            if (winner != NONE)
            {
                break;
            }
        } while (!turn_over);

        // PROCESSING - At the end of the player's turn, switch who is not
        // the current player to the other player/computer
        if (current_player == PLAYER1)
        {
            if (ai_game)
            {
                current_player = COMPUTER;
            } else
            {
                current_player = PLAYER2;
            }
        } else if (current_player == PLAYER2)
        {
            current_player = PLAYER1;
        } else if (current_player == COMPUTER)
        {
            current_player = PLAYER1;
        }

        cout << endl << endl;
    } while (winner == NONE);

    // OUTPUT - Display the player who won
    switch (winner)
    {
    case PLAYER1:
        cout << "Player 1 wins!" << endl;
        break;
    case PLAYER2:
        cout << "Player 2 wins!" << endl;
        break;
    case COMPUTER:
        cout << "The AI wins!" << endl;
        break;
    case NONE:
        break;
    }

    return 0;
}
