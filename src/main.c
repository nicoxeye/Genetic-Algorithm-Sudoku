#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"

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


    printf("generated sudoku:\n");
    printBoard();

    freeBoard();

    return 0;
}


// printing the grid
void printGrid(int grid[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
  
    if (i % BOX == 0) {
    printf("--------------------------------\n");
    }
  
    for (int j = 0; j < SIZE; j++) {
  
    if (j % BOX == 0) {
        printf("| ");
    }
  
    if (grid[i][j] == 0) {
        printf(" 0 ");
    } 
    else if (grid[i][j] <= 9) {
        printf("%2d ", grid[i][j]);
    } 
    else {
        // it will replace 10-16 with a char of A-F
        printf(" %c ", 'A' + (grid[i][j] - 10));
        }
    }
      printf("\n");
    }
}