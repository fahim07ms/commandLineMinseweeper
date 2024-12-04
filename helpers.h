// Header guard
#ifndef HELPERS_H
#define HELPERS_H

// Global variables
const int NROWS = 9;
const int NCOLS = 9;
const int NMINES = 10;

// Safe move
void safe_move(char game_board[][NCOLS], char mine_board[][NCOLS], int &placed);

// Check if user inputted valid move
bool isValid(char game_board[][NCOLS], int row, int col, char move);

// Locates a mine
void locate_a_mine(char mine_board[][NCOLS], int s_row, int s_col);

// Print board
void print_board(char mine_board[][NCOLS]);

// Uncover board after a step
void uncover_board(char game_board[][NCOLS], char mine_board[][NCOLS], int row, int col);

// Has won or not
bool has_won(char game_board[NROWS][NCOLS], char mine_board[NROWS][NCOLS]);

#endif // HELPERS_H