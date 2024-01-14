#include "header.h"

/*********************************************************
 * FUNCTION row_to_idx
 * ________________________________________________________
 * Converts a row from its character form to a 0 indexed number
 * ________________________________________________________
 * PRE-CONDITIONS
 *  row: The character
 *
 * POST-CONDITIONS
 *  returns a zero indexed row position
 *********************************************************/
int row_to_idx(char row) // IN - The character to convert
{
    return row - 'A';
}

/*********************************************************
 * FUNCTION is_valid_coordinate
 * ________________________________________________________
 * Checks if a zero indexed cell coordinate is valid
 * ________________________________________________________
 * PRE-CONDITIONS
 *  row: The zero indexed row
 *  col: The zero indexed col
 *
 * POST-CONDITIONS
 *  returns a boolean indicating if the (row, col) pair is valid
 *********************************************************/
bool is_valid_coordinate(int row, // IN - The zero indexed row
                         int col) // IN - The zero indexed col
{
    return (row >= 0 && row <= 9 && col >= 0 && col <= 9);
}

/*********************************************************
 * FUNCTION get_valid_coordinate
 * ________________________________________________________
 * Gets coordinates to a cell
 * ________________________________________________________
 * PRE-CONDITIONS
 *  none
 *
 * POST-CONDITIONS
 *  p: The user input is stored into
 *
 *  returns a boolean indicating if the (row, col) pair is valid
 *********************************************************/
bool get_valid_coordinate(Point &p) // OUT - The row, col the user entered
{
    char row_char;
    int row, col;

    cin >> row_char >> col;

    row = row_to_idx(row_char);
    --col;

    p.x = col;
    p.y = row;

    return is_valid_coordinate(row, col);
}

/*********************************************************
 * FUNCTION init_fleet
 * ________________________________________________________
 * Sets up the player board and gets all ship placements from the user
 * ________________________________________________________
 * PRE-CONDITIONS
 *  board: A playerboard in any state
 *
 * POST-CONDITIONS
 *  board: Both char' arrays will be filled and the fleet will be fully
 *  setup
 *
 *  returns nothing
 *********************************************************/
void init_fleet(PlayerBoard &board) // OUT - Board to store fleet info to
{
    // PROCESSING - Fill every spot in the character board with spaces
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            board.main_board[i][j] = ' ';
            board.enemy_board[i][j] = ' ';
        }
    }

    // PROCESSING - Make copies of each ship type into the player board
    board.fleet[0] = CARRIER;
    board.fleet[1] = BATTLESHIP;
    board.fleet[2] = CRUISER;
    board.fleet[3] = SUBMARINE;
    board.fleet[4] = DESTROYER;

    // PROCESSING/INPUT - Run through all the ship types and have the user
    // enter the positions of the entire fleet
    for (int i = 0; i < FLEET_SIZE; ++i)
    {
        display_boards(board.main_board, board.enemy_board);
        place_ship(board, i);
    }
    display_boards(board.main_board, board.enemy_board);
}

/*********************************************************
 * FUNCTION place_ship
 * ________________________________________________________
 * Gets a valid ship placement from the user and adds it to the player's
 * fleet
 * ________________________________________________________
 * PRE-CONDITIONS
 *  board: The board must have its fleet semi populated with sizes
 *
 * POST-CONDITIONS
 *  board: The ship at the ship index will be completed
 *
 *  returns nothing
 *********************************************************/
void place_ship(
    PlayerBoard &board, // IN/OUT - The board to store the ship info to
    int ship_idx)       // IN - The ship index to work with
{
    char orientation;
    int row, col;

    Ship &ship = board.fleet[ship_idx];

    get_valid_ship_info(board, row, col, orientation, ship_idx);

    if (orientation == 'v')
    {
        for (int i = 0; i < ship.size; ++i)
        {
            Point cell = {row + i, col};
            ship.cells.push_back(cell);
            board.main_board[row + i][col] = 's';
        }
    } else if (orientation == 'h')
    {
        for (int i = 0; i < ship.size; ++i)
        {
            Point cell = {row, col + i};
            ship.cells.push_back(cell);
            board.main_board[row][col + i] = 's';
        }
    }
}

/*********************************************************
 * FUNCTION get_valid_ship_info
 * ________________________________________________________
 * Gets a shipment placement from the user with proper input validation and
 * checking
 * ________________________________________________________
 * PRE-CONDITIONS
 *  board: A board with the fleet setup partially
 *  row: The output row
 *  col: The output column
 *  orientation: The output orientation
 *  ship_idx: Which ship to work on
 *
 * POST-CONDITIONS
 *  stores the valid info into row, col, and orientation
 *
 *  returns nothing
 *********************************************************/
void get_valid_ship_info(
    PlayerBoard &board, // IN/OUT - The board to read and store to
    int &row,           // OUT - The valid row the user chose
    int &col,           // OUT - The valid col the user chose
    char &orientation,  // OUT - The valid orientation chosen
    int ship_idx)       // IN - The ship to work on
{
    bool valid = false;

    char row_char;
    Ship &ship = board.fleet[ship_idx];

    // PROCESSING - Keep prompting for user input until the user enters a
    // valid ship coordinate
    do
    {
        // INPUT - Get the row and column of the starting point
        cout << "Enter the starting coordinate of your " << ship.name
             << ": ";
        cin >> row_char >> col;

        // PROCESSING - Convert row and column to numbers in the range 0-9
        row = row_to_idx(row_char);
        --col;

        // PROCESSING - Check if the starting point is in bounds
        if (!is_valid_coordinate(row, col))
        {
            cout << "Out of bounds coordinate. Try again.\n";
            valid = false;
            continue;
        }

        // INPUT - Get the orientation the users wants to place their ship
        cout << "Enter the orientation of your " << ship.name
             << " (horizontal(h) or vertical(v)): ";
        cin >> orientation;
        cout << "\n";

        // PROCESSING - Check if the orientation is valid
        if (orientation != 'v' && orientation != 'h')
        {
            cout << "Invalid orientation. Try Again\n";
            valid = false;
            continue;
        }

        // PROCESSING - Check if the ship placement would fit in the bounds
        if (!in_bounds(row, col, orientation, ship.size))
        {
            cout << "Ship placement would be out of bounds. Try again\n";
            valid = false;
            continue;
        }

        // PROCESSING - Check if the ship placement would overlap another
        if (space_occupied(board, row, col, orientation, ship.size))
        {
            cout << "Ship placement overlaps another ship. Try again\n";
            valid = false;
            continue;
        }

        // PROCESSING - At this point, the ship placement is valid.
        valid = true;
    } while (!valid);
}

/*********************************************************
 * FUNCTION in_bounds
 * ________________________________________________________
 * Gets a shipment placement from the user with proper input validation and
 * checking
 * ________________________________________________________
 * PRE-CONDITIONS
 *  row: The starting row
 *  col: The starting col
 *  orientation: A char that is 'v' or 'h'
 *  ship_size: The size of the ship
 *
 * POST-CONDITIONS
 *  returns if the ship placed at row, col with the given orientation fits
 *  in the grid
 *********************************************************/
bool in_bounds(int row,          // IN - The starting row
               int col,          // IN - The starting column
               char orientation, // IN - The orientation
               int ship_size)    // IN - The size of the ship
{
    int max_row;
    int max_col;

    // PROCESSING - Since the ship either grows further downwards or
    // rightwards, it only needs to be checked that the end of the ship is
    // in or out of the grid
    if (orientation == 'v')
    {
        max_row = row + ship_size;
        max_col = col;
    } else if (orientation == 'h')
    {
        max_row = row;
        max_col = col + ship_size;
    }

    // PROCESSING - Check if the end of the ship would be in the grid
    return is_valid_coordinate(max_row, max_col);
}

/*********************************************************
 * FUNCTION space_occupied
 * ________________________________________________________
 * Checks if a ship placement at a given cell with a given orietnation and
 * length would overlap any occupied cells
 * ________________________________________________________
 * PRE-CONDITIONS
 *  board: A board with the fleet partially filled
 *  row: A valid row index
 *  col: A valid col index
 *  orientation: A valid orientation
 *  ship_size: The ship size
 *
 * POST-CONDITIONS
 *  returns if the ship placed at row, col with the given orientation
 *  overlaps another ship
 *********************************************************/
bool space_occupied(PlayerBoard &board, // IN - Player's fleet
                    int row,            // IN - The starting row
                    int col,            // IN - The starting column
                    char orientation,   // IN - The ship orientation
                    int ship_size)      // IN - The ship's size
{
    // PROCESSING - Check every ship for overlap
    for (int s = 0; s < FLEET_SIZE; ++s)
    {
        Ship &ship = board.fleet[s];

        // PROCESSING - Check if the cells are
        // already occupied by another ship by iterating over every ships
        // cells and see if any are equal to the cells of the new ship
        if (orientation == 'v')
        {
            for (int i = 0; i < ship_size; ++i)
            {
                Point cell = {row + i, col};
                for (int k = 0; k < ship.cells.size(); ++k)
                {
                    if (ship.cells[k] == cell)
                    {
                        return true;
                    }
                }
            }
        } else if (orientation == 'h')
        {
            for (int i = 0; i < ship_size; ++i)
            {
                Point cell = {row, col + i};
                for (int k = 0; k < ship.cells.size(); ++k)
                {
                    if (ship.cells[k] == cell)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/*********************************************************
 * FUNCTION check_hit
 * ________________________________________________________
 * Takes a position and boards and checks if the player would hit a ship.
 * If so, it adds the hit towards the ship's hit counter. Takes a position
 * ________________________________________________________
 * PRE-CONDITIONS
 *  row: A valid row index
 *  col: A valid col index
 *  sunken_ship: If a ship is sunk, store which one to here
 *  enemy: The enemy's board
 *  player: The player's board
 *
 * POST-CONDITIONS
 *  if the mark is a hit, then log the hit for the enemy ship and add to
 *  the corresponding boards. If a miss, log it the same way.
 *
 *  returns if the mark missed, hit, or has already been done before
 *********************************************************/
HitType check_hit(int row,               // IN - The row to mark
                  int col,               // IN - The column to mark
                  ShipType &sunken_ship, // OUT - The ship sunk, if any
                  PlayerBoard &enemy,    // OUT - The board to hit
                  PlayerBoard &player)   // IN - The player's board
{
    // PROCESSING - Mark the current sunken ship as none
    sunken_ship = TYPE_NONE;

    // PROCESSING - If the player has already tried this spot, return early
    if (player.enemy_board[row][col] != ' ')
    {
        return ALREADY_SHOT;
    }

    Point mark = {row, col};

    // PROCESSING - Iterate through all the enemies ships and see if the
    // mark overlaps any
    for (int s = 0; s < FLEET_SIZE; ++s)
    {
        Ship &ship = enemy.fleet[s];

        for (int i = 0; i < ship.cells.size(); ++i)
        {
            // PROCESSING - If the mark hits an enemy ship, add to its
            // hitcount
            if (ship.cells[i] == mark)
            {
                ship.hitcount += 1;

                // PROCESSING - If this hit causes the entire ship to be
                // hit, write to the sunken_ship output which ship was sunk
                if (ship.hitcount == ship.size)
                {
                    sunken_ship = static_cast<ShipType>(s + 1);
                }

                player.enemy_board[row][col] = 'H';
                enemy.main_board[row][col] = 'H';
                return HIT;
            }
        }
    }

    // PROCESSING - If the loop completed, then there was no overlap with
    // the enemies ships and hence the mark missed
    player.enemy_board[row][col] = 'M';
    enemy.main_board[row][col] = 'M';
    return MISS;
}

/*********************************************************
 * FUNCTION check_winner
 * ________________________________________________________
 * Checks if either of the input boards have lost. That is, all their ships
 * are sunk. If so, return which player has won then
 * ________________________________________________________
 * PRE-CONDITIONS
 *  player1: The first player's board
 *  player2: The second player's board
 *  ai_game: Is the second player a computer?
 *
 * POST-CONDITIONS
 *  returns which player won, if any
 *********************************************************/
Player check_winner(PlayerBoard &player1, // IN - The first player's board
                    PlayerBoard &player2, // IN - The second player's board
                    bool ai_game)         // IN - If player 2 is an AI
{
    // PROCESSING - Assume that both player's lost
    bool player1_sunk = true;
    bool player2_sunk = true;

    // PROCESSING - Check if any of the ships for player 1 or 2 are still
    // standing. If so, then mark the corresponding player as not defeated
    for (int s = 0; s < FLEET_SIZE; ++s)
    {
        Ship &ship_p1 = player1.fleet[s];
        Ship &ship_p2 = player2.fleet[s];

        if (ship_p1.hitcount != ship_p1.size)
        {
            player1_sunk = false;
        }

        if (ship_p2.hitcount != ship_p2.size)
        {
            player2_sunk = false;
        }
    }

    // PROCESSING - Check if either of the players have been defeated and
    // return the corresponding winner
    if (player1_sunk)
    {
        if (ai_game)
        {
            return COMPUTER;
        }

        return PLAYER2;
    } else if (player2_sunk)
    {
        return PLAYER1;
    }

    // PROCESSING - No player is defeated so no one is a winner
    return NONE;
}

/*********************************************************
 * FUNCTION player_turn
 * ________________________________________________________
 * Executes an entire turn for a player
 * ________________________________________________________
 * PRE-CONDITIONS
 *  player: The current player whose turn it is
 *  enemy: The opposing player's board
 *  turn_over: Should the turn cycle end after this turn?
 *  winner: If someone wins, store who won here
 *
 * POST-CONDITIONS
 *  if the turn should continue, that is stored in the turn_over variable.
 *  Additionally, if the player wins, it is stored in the winner variable.
 *
 *  returns nothing
 *********************************************************/
void player_turn(
    PlayerBoard &player, // IN/OUT - The current player's board
    PlayerBoard &enemy,  // IN/OUT - The enemy's board
    bool &turn_over,     // OUT - Indicate if the turn cycle should end
    Player &winner,      // OUT - If the current turn wins, store who won
    bool ai_game)        // IN - Is this a game against a computer
{
    Point shot;
    HitType shot_hit;
    bool new_shot_mark;
    ShipType sunken_ship = TYPE_NONE;

    // OUTPUT - Display the correct board for whoever's current
    // turn it is
    display_boards(player.main_board, player.enemy_board);

    // PROCESSING - Make sure that the player's mark is a valid location
    // and hasn't been seen before
    do
    {
        // INPUT - Get a shot coordinate from the user. If it is
        // invalid, keep trying until the user enters a valid one
        cout << "Fire a shot: ";
        while (!get_valid_coordinate(shot))
        {
            cout << "Invalid coordinate. Try again\n";
            cout << "Fire a shot: ";
        }

        // PROCESSING - Take the shot and check if it hit, missed, or is a
        // spot that already has been checked. Additionally, check if a
        // ship has been sunk
        shot_hit = check_hit(shot.y, shot.x, sunken_ship, enemy, player);

        // OUTPUT - Display if the user hit, missed, or already shot at
        // this cell
        switch (shot_hit)
        {
        case HIT:
            cout << "Hit!"
                 << "\n";
            new_shot_mark = true;
            turn_over = false;
            break;
        case MISS:
            cout << "Miss!"
                 << "\n";
            new_shot_mark = true;
            turn_over = true;
            break;
        case ALREADY_SHOT:
            cout << "You have already shot here. Try again"
                 << "\n";
            new_shot_mark = false;
            break;
        }
    } while (!new_shot_mark);

    // OUTPUT - If the shot hit, notify the current player,
    // otherwise notify them they missed

    // PROCESSING/OUTPUT - If the hit sunk a ship, display which
    // ship was sunk
    switch (sunken_ship)
    {
    case TYPE_CARRIER:
        cout << "You sunk the Carrier!"
             << "\n";
        break;
    case TYPE_BATTLESHIP:
        cout << "You sunk the Battleship!"
             << "\n";
        break;
    case TYPE_CRUISER:
        cout << "You sunk the Cruiser!"
             << "\n";
        break;
    case TYPE_SUBMARINE:
        cout << "You sunk the Submarine!"
             << "\n";
        break;
    case TYPE_DESTROYER:
        cout << "You sunk the Destroyer!"
             << "\n";
        break;
    case TYPE_NONE:
        break;
    }

    // PROCESSING - After the current turn/sub-turn, check if the
    // player actually won and therefore their turn should "end"
    winner = check_winner(player, enemy, ai_game);
}

// A helper function that defines the equality operator between two points
// so it is possible to do comparison such as
//
//  ```
//  Point p1 = {1,2};
//  Point p2 = {2,1};
//
//  cout << (p1 == p2)
//  ```
bool Point::operator==(const Point &other)
{
    return (other.x == x) && (other.y == y);
}
