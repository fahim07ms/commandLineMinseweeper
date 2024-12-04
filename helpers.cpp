#include <cstdio>
#include <cstdlib>

#include "helpers.h"

// Safe move
void safe_move(char game_board[][NCOLS], char mine_board[][NCOLS], int &placed)
{
    // Print game board
    print_board(game_board);

    // Get user move
    int row, column;
    char move;
    do
    {
        printf("Enter your first move, (row, column, move) -> ");
        scanf("%i %i %c", &row, &column, &move);
        printf("\n\n");
        row--;
        column--;
    } while (!isValid(game_board, row, column, move));

    // Locate mines
    for (int i = 0; i < NMINES; i++)
    {
        locate_a_mine(mine_board, row, column);
        placed++;
    }

    if (move = 's')
    {
        // Uncover board
        uncover_board(game_board, mine_board, row, column);
    }
    else
    {
        // It's a flag
        game_board[row][column] = 'F';
    }
}

// Check if user inputted valid move
bool isValid(char game_board[][NCOLS], int row, int col, char move)
{
    // Checking row
    if (row < 0 || row >= NROWS)
    {
        return false;
    }

    // Checking column
    if (col < 0 || col >= NCOLS)
    {
        return false;
    }

    // Checking move
    if (move != 's' && move != 'f')
    {
        return false;
    }

    // Check if there is already a number
    if (game_board[row][col] != '*' && game_board[row][col] != 'F')
    {
        return false;
    }

    return true;
}


// Locate a mine
void locate_a_mine(char mine_board[][NCOLS], int s_row, int s_col)
{
    // Generate a random location
    int random = rand()%(NROWS*NCOLS);
    int row = random/NROWS;
    int col = random%NCOLS;

    if (row != s_row && col != s_col && mine_board[row][col] != '#')
    {
        mine_board[row][col] = '#';


        for (int j = row-1; j < row+2; j++)
        {
            if (j >= 0 && j < NROWS)
            {
                for (int k = col-1; k < col+2; k++)
                {
                    if (k >= 0 && k < NCOLS)
                    {
                        if (mine_board[j][k] >= 48 && mine_board[j][k] <= 57)
                        {
                            mine_board[j][k] = mine_board[j][k] + 1;
                        }
                    }
                }
            }
        }
    }
    else
    {
        locate_a_mine(mine_board, s_row, s_col);
    }
}

// Print board
void print_board(char game_board[][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        // Showing the columns numbers in top
        if (i == 0)
        {
            printf("   ");
            for (int j = 1; j <= NCOLS; j++)
            {
                printf("%i ", j);
            }
            printf("\n\n");
        }

        // Print row number in left
        printf("%i  ", (i+1));

        // Print main board and also rows numbers
        for (int j = 0; j < NCOLS; j++)
        {

            printf("%c ", game_board[i][j]);

        }

        // Print row number in right
        printf("  %i\n", (i+1));

        // Showing the column numbers in bottom
        if (i == NROWS-1)
        {
            printf("\n   ");
            for (int j = 1; j <= NCOLS; j++)
            {
                printf("%i ", j);
            }
            printf("\n\n");
        }
    }
}

// Uncover board after a step
void uncover_board(char game_board[][NCOLS], char mine_board[][NCOLS], int row, int col)
{
    // If it is a digit(1-9), show it
    if (mine_board[row][col] >= 49 && mine_board[row][col] <= 57)
    {
        game_board[row][col] = mine_board[row][col];
        return;
    }
    // If it's empty, try to show another cell
    else if (mine_board[row][col] == '0')
    {
        game_board[row][col] = mine_board[row][col];

        for (int j = row-1; j < row+2; j++)
        {

                for (int k = col-1; k < col+2; k++)
                {

                    if (isValid(game_board, j, k, 's') && game_board[j][k] != 'F')
                    {
                        uncover_board(game_board, mine_board, j, k);
                    }
                }

        }


    }
}

// Check if player has own
bool has_won(char game_board[NROWS][NCOLS], char mine_board[NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {

            if (mine_board[i][j] == '#')
            {
                if (game_board[i][j] != 'F')
                {
                    return false;
                }
            }
        }
    }

    return true;
}