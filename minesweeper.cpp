#include <cstdio>
#include <string>
#include <ctime>

#include "helpers.h"

int main()
{
    // Number of flags
    int flags = 0;

    // Seed
    srand(time(0));

    // Introduction and choose difficulty
    printf("Welcome to Minesweeper!\nChoose difficulty\n");
    printf("Press 1 for BEGINNER (9*9 cells & 10 mines)\n");
    printf("Press 2 for INTERMEDIATE (16*16 cells & 40 mines)\n");
    printf("Press 3 for ADVANCED (16*30 cells & 99 mines)\n\n");

    // Getting input for difficulty
    int level;
    scanf("%i", &level);
    printf("\n");

    // Making game according to user inputed difficulty
    if (level == 1)
    {
        /*NROWS = 5;
        NCOLS = 5;
        NMINES = 5;*/
    }
    else if (level == 2)
    {
        /*NROWS = 5;
        NCOLS = 5;
        NMINES = 5;*/
    }
    else if (level == 3)
    {
        /*NROWS = 5;
        NCOLS = 5;
        NMINES = 5;*/
    }
    else
    {
        printf("Invalid input\n");
    }

    // Game board and mine board
    char game_board[NROWS][NCOLS];
    char mine_board[NROWS][NCOLS];

    // Fill gameboard with *
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            game_board[i][j] = '*';
        }
    }

    // Fill mineboard with '0'
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            mine_board[i][j] = '0';
        }
    }

    // First safe move and locating mine
    safe_move(game_board, mine_board, flags);

    //print_board(mine_board);

    // Game has end or not
    bool game_end = false;

    // While game hasn't end
    while (!game_end)
    {
        // Print game board
        print_board(game_board);

        // Flags left
        printf("%i flag/s left\n\n", flags);

        // Get user move
        int row, column;
        char move;
        // Ensure valid move
        do
        {
            printf("Enter your move, (row, column, safe(s)/flag(f) -> ");
            scanf("%i %i %c", &row, &column, &move);
            printf("\n\n");

            row--;
            column--;

        }   while(!isValid(game_board, row, column, move));

        // If user unlocks a bomb he loses
        if (move == 's' && mine_board[row][column] == '#')
        {
            game_board[row][column] = '#';
            print_board(game_board);
            printf("You lose!\n");
            game_end = true;
        }
        // If user put a flag
        else if (move == 'f')
        {
            game_board[row][column] = 'F';
            flags--;
        }
        // If it was really a safe move
        else if (move == 's' && mine_board[row][column] != '#')
        {
            if (game_board[row][column] == 'F')
            {
                flags++;
            }

            uncover_board(game_board, mine_board, row, column);
        }

        // Check if user won after this move
        if (has_won(game_board, mine_board) == true)
        {
            print_board(game_board);
            printf("You won!\n");
            game_end = true;
        }
    }

    return 0;
}