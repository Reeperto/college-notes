#include "header.h"

/*********************************************************
 * FUNCTION ai_init_fleet
 * ________________________________________________________
 * Creates the computer's fleet by randomly placing ships
 * ________________________________________________________
 * PRE-CONDITIONS
 *  none
 *
 * POST-CONDITIONS
 *  fills the entire fleet and board with the proper initial data - returns
 *  nothing
 *********************************************************/
void ai_init_fleet(ComputerAI &ai) // OUT - The ai board to setup
{
    int row, col;
    char orientation;
    bool valid_placement = false;

    // PROCESSING - Fill every spot in the character board with spaces
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            ai.board.main_board[i][j] = ' ';
            ai.board.enemy_board[i][j] = ' ';
        }
    }

    // PROCESSING - Make copies of each ship type into the player board
    ai.board.fleet[0] = CARRIER;
    ai.board.fleet[1] = BATTLESHIP;
    ai.board.fleet[2] = CRUISER;
    ai.board.fleet[3] = SUBMARINE;
    ai.board.fleet[4] = DESTROYER;

    // PROCESSING - Run through each ship and make a placement for it
    for (int i = 0; i < FLEET_SIZE; ++i)
    {
        Ship &ship = ai.board.fleet[i];

        // PROCESSING - Generate a placement over and over until it is
        // valid
        do
        {
            row = rand() % 10;
            col = rand() % 10;
            orientation = (rand() % 2) ? 'v' : 'h';

            valid_placement =
                in_bounds(row, col, orientation, ship.size) &&
                !space_occupied(ai.board, row, col, orientation,
                                ship.size);

        } while (!valid_placement);

        // PROCESSING - Add placement to fleet with the right orientation
        if (orientation == 'v')
        {
            for (int i = 0; i < ship.size; ++i)
            {
                Point cell = {row + i, col};
                ship.cells.push_back(cell);
                ai.board.main_board[row + i][col] = 's';
            }
        } else if (orientation == 'h')
        {
            for (int i = 0; i < ship.size; ++i)
            {
                Point cell = {row, col + i};
                ship.cells.push_back(cell);
                ai.board.main_board[row][col + i] = 's';
            }
        }
    }
}

/*********************************************************
 * FUNCTION ai_turn
 * ________________________________________________________
 * Steps through a single turn of the AI
 * ________________________________________________________
 * PRE-CONDITIONS
 *  ai: An ai struct that has a full active fleet
 *  enemy: The enemies board
 *
 * POST-CONDITIONS
 *  turn_over: The ai indicates based on this turn if it should take
 *             another turn or not
 *  winner: If the ai wins on this turn, it stores it into winner
 *
 *  returns nothing
 *********************************************************/
void ai_turn(
    ComputerAI &ai,     // IN - The current AI board and state
    PlayerBoard &enemy, // OUT - The enemy board
    bool &turn_over,    // OUT - Indicate if the turn cycle should end
    Player &winner)     // OUT - If the current turn wins, store who won
{
    ShipType sunken_ship;
    Point shot = ai_get_shot(ai);
    HitType hit = check_hit(shot.y, shot.x, sunken_ship, enemy, ai.board);
    ai_log_shot(ai, shot, hit);

    switch (hit)
    {
    case HIT:
        cout << "The AI Hit!"
             << "\n";
        turn_over = false;
        break;
    case MISS:
        cout << "The AI Missed!"
             << "\n";
        turn_over = true;
        break;
    default:
        break;
    }

    switch (sunken_ship)
    {
    case TYPE_CARRIER:
        cout << "The AI sunk your Carrier!"
             << "\n";
        break;
    case TYPE_BATTLESHIP:
        cout << "The AI sunk your Battleship!"
             << "\n";
        break;
    case TYPE_CRUISER:
        cout << "The AI sunk your Cruiser!"
             << "\n";
        break;
    case TYPE_SUBMARINE:
        cout << "The AI sunk your Submarine!"
             << "\n";
        break;
    case TYPE_DESTROYER:
        cout << "The AI sunk your Destroyer!"
             << "\n";
        break;
    case TYPE_NONE:
        break;
    }

    winner = check_winner(enemy, ai.board, true);
}

/*********************************************************
 * FUNCTION ai_already_shot
 * ________________________________________________________
 * Checks if a point has already been shot by the AI before
 * ________________________________________________________
 * PRE-CONDITIONS
 *  ai: An ai struct that has a full active fleet
 *  point: A valid cell on the grid
 *
 * POST-CONDITIONS
 *  returns a boolean indicating if the shot has been seen or not
 *********************************************************/
bool ai_already_shot(ComputerAI &ai, // IN - The AI state
                     Point p)        // IN - The point to check
{
    // PROCESSING - Iterate through all previous shots the AI has made and
    // check if the current one has already been done.
    for (int i = 0; i < ai.all_shots.size(); ++i)
    {
        if (p == ai.all_shots[i])
        {
            return true;
        }
    }

    return false;
}

/*********************************************************
 * FUNCTION ai_get_shot
 * ________________________________________________________
 * Gets the next shot the AI will make
 * ________________________________________________________
 * PRE-CONDITIONS
 *  ai: An ai struct that has a full active fleet
 *
 * POST-CONDITIONS
 *  returns a cell to fire at
 *********************************************************/
Point ai_get_shot(ComputerAI &ai) // IN - The current AI state
{
    Point mark;

    // PROCESSING - If there are no cells in the stack, fire at a random
    // cell
    if (ai.point_stack.empty())
    {
        do
        {
            mark.x = rand() % 10;
            mark.y = rand() % 10;
        } while (ai_already_shot(ai, mark));
    } else
    {
        // PROCESSING - Get the next cell from the stack
        mark = ai.point_stack.back();
        ai.point_stack.pop_back();
    }

    return mark;
}

/*********************************************************
 * FUNCTION ai_log_shot
 * ________________________________________________________
 * Updates the computer's information about the current game state based on
 * the previous shot
 * ________________________________________________________
 * PRE-CONDITIONS
 *  ai: An ai struct that has a full active fleet
 *  point: A cell on the board
 *  hit: What kind of hit was made at that point
 *
 * POST-CONDITIONS
 *  adds any valid adjacent cells to the point stack
 *
 *  returns nothing
 *********************************************************/
void ai_log_shot(ComputerAI &ai, // IN/OUT - The ai state and history
                 Point p,        // IN - The point to log
                 HitType hit)    // IN - The type of hit that occurred at p
{
    // PROCESSING - Log the shot in the shot history
    ai.all_shots.push_back(p);

    Point top = p;
    Point bottom = p;
    Point left = p;
    Point right = p;

    // PROCESSING - If the ai made a hit add adjacent cells to
    if (hit == HIT)
    {
        top.y += -1;
        bottom.y += 1;
        left.x -= 1;
        right.x += 1;

        // PROCESSING - Check which adjacent cells are on the grid and add
        // them to the point stack
        if (is_valid_coordinate(top.y, top.x))
        {
            ai.point_stack.push_back(top);
        }

        if (is_valid_coordinate(bottom.y, bottom.x))
        {
            ai.point_stack.push_back(bottom);
        }

        if (is_valid_coordinate(left.y, left.x))
        {
            ai.point_stack.push_back(left);
        }

        if (is_valid_coordinate(right.y, right.x))
        {
            ai.point_stack.push_back(right);
        }
    }
}
