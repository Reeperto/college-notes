#include "header.h"

// USeful board display constants
const string BOARD_SEPERATOR = "-----------------------------------------";
const string BOARDS_GAP = "    ";

void display_column_header()
{
    cout << " ";
    for (int i = 1; i <= 10; ++i)
    {
        cout << setw(4) << right << i;
    }
}

void display_board_line(char board[][10], char row)
{
    cout << setw(2) << left << row;

    for (int i = 0; i < 10; ++i)
    {
        cout << "|";
        cout << " " << board[row - 'A'][i] << " ";
    }
    cout << "|";
}

void display_boards(char main_board[][10], char enemy_board[][10])
{
    cout << "                  Your Board                                 "
            "   Enemy Board";
    // cout << setw(28) << "Your Board";
    // cout << BOARDS_GAP;
    // cout << setw(29 + 14) << "Enemy Board";
    cout << '\n';

    display_column_header();
    cout << "  " << BOARDS_GAP;
    display_column_header();
    cout << '\n';

    cout << "  " << BOARD_SEPERATOR << BOARDS_GAP << "  "
         << BOARD_SEPERATOR << "\n";

    for (char j = 'A'; j <= 'J'; ++j)
    {
        display_board_line(main_board, j);
        cout << BOARDS_GAP;
        display_board_line(enemy_board, j);
        cout << '\n';

        cout << "  " << BOARD_SEPERATOR << BOARDS_GAP << "  "
             << BOARD_SEPERATOR << "\n";
    }
}
