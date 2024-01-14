#pragma once

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int FLEET_SIZE = 5;

const int SIZE_CARRIER = 5;
const int SIZE_BATTLESHIP = 4;
const int SIZE_CRUISER = 3;
const int SIZE_SUBMARINE = 3;
const int SIZE_DESTROYER = 2;

enum Player
{
    NONE,
    PLAYER1,
    PLAYER2,
    COMPUTER,
};

enum HitType
{
    HIT,
    MISS,
    ALREADY_SHOT
};

enum ShipType
{
    TYPE_NONE,
    TYPE_CARRIER,
    TYPE_BATTLESHIP,
    TYPE_CRUISER,
    TYPE_SUBMARINE,
    TYPE_DESTROYER,
};

struct Point
{
    int x;
    int y;

    bool operator==(const Point &other);
};

struct Ship
{
    string name;
    int size;
    int hitcount;
    vector<Point> cells;
};

// Basic instances of each ship type
const Ship BATTLESHIP = {"Battleship", SIZE_BATTLESHIP, 0};
const Ship CARRIER = {"Carrier", SIZE_CARRIER, 0};
const Ship CRUISER = {"Cruiser", SIZE_CRUISER, 0};
const Ship SUBMARINE = {"Submarine", SIZE_SUBMARINE, 0};
const Ship DESTROYER = {"Destroyer", SIZE_DESTROYER, 0};

struct PlayerBoard
{
    char main_board[10][10];
    char enemy_board[10][10];
    Ship fleet[FLEET_SIZE];
};

struct ComputerAI
{
    PlayerBoard board;
    vector<Point> point_stack;
    vector<Point> all_shots;
};

// Helper functions
int row_to_idx(char row);
bool is_valid_coordinate(int row, int col);
bool get_valid_coordinate(Point &p);

// Display function
void display_boards(char board1[][10], char board2[][10]);

// Gameplay functions
void player_turn(PlayerBoard &player, PlayerBoard &enemy, bool &turn_over,
                 Player &winner, bool ai_game);
HitType check_hit(int row, int col, ShipType &sunken_ship,
                  PlayerBoard &enemy_board, PlayerBoard &main_board);
Player check_winner(PlayerBoard &player1, PlayerBoard &player2,
                    bool ai_game);

// Setup functions
void init_fleet(PlayerBoard &board);
void place_ship(PlayerBoard &board, int ship_idx);
void get_valid_ship_info(PlayerBoard &board, int &row, int &col,
                         char &orientation, int ship_idx);
bool in_bounds(int row, int col, char orientation, int ship_size);
bool space_occupied(PlayerBoard &board, int row, int col, char orientation,
                    int ship_size);

// Computer/AI Functions
void ai_init_fleet(ComputerAI &ai);
void ai_turn(ComputerAI &ai, PlayerBoard &enemy, bool &turn_over,
             Player &winner);
bool ai_already_shot(ComputerAI &ai, Point p);
void ai_log_shot(ComputerAI &ai, Point p, HitType hit);
Point ai_get_shot(ComputerAI &ai);
