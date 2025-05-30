#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"
#include "util.h"
#include "ga.h"

#define SIZE 9
#define BOX 3

void printGrid(int grid[SIZE][SIZE]);

int main(){
    srand(time(NULL));

    gameState.boxSize = 3;
    gameState.difficulty = 2;
    gameState.sizeOfTheBoard = 9;
    gameState.board = sudokuGenerator();

    int grid[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = gameState.board[i][j];
        }
    }


    printf("generated sudoku:\n\n");
    printBoard();

    // creates a fixed boards and stores bools whether the places on the grid were filled before
    bool fixed[SIZE][SIZE];
    initFixed(grid, fixed);
    // if fixed has false then it is randomly filled with numbers 1 through 9
    // makes sure no digit is duplicated within the box
    fillGrid(grid, fixed);

    printf("initial filled grid:\n"); //informational
    printGrid(grid);

    freeBoard();

    return 0;
}