#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"
#include "ga.h"

#define SIZE 9
#define BOX 3

void fillGrid(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]);
bool fixedValueInBox(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE], int blockRow, int blockCol, int val);
void initFixed(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]);
void printGrid(int grid[SIZE][SIZE]);

// fills the spots; '0's on the board with numbers 1-9
// makes sure no digit is duplicated within the box
void fillGrid(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]) {

    for (int blockRow = 0; blockRow < BOX; blockRow++) {
        for (int blockCol = 0; blockCol < BOX; blockCol++) {
            int digits[SIZE];
            int count = 0;

            // collect digits 1–9
            for (int i = 0; i < SIZE; i++) {
                digits[i] = i + 1;
            }

            // shuffle digits
            for (int i = SIZE - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                int temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
            }

            // fill unfixed cells with shuffled digits, skip over fixed
            int index = 0;
            for (int i = 0; i < BOX; i++) {
                for (int j = 0; j < BOX; j++) {
                    int row = blockRow * BOX + i;
                    int col = blockCol * BOX + j;

                    if (!fixed[row][col]) {
                        // skip used values by fixed cells in this box
                        while (index < SIZE && fixedValueInBox(grid, fixed, blockRow, blockCol, digits[index])) {
                            index++;
                        }
                        //fills the cell with the next available digit.
                        if (index < SIZE) {
                            grid[row][col] = digits[index++];
                        }
                    }
                }
            }

        }
    }
}


// check if digit already used in this box (for fixed cells)
bool fixedValueInBox(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE], int blockRow, int blockCol, int val) {
    for (int i = 0; i < BOX; i++) {
        for (int j = 0; j < BOX; j++) {
            int row = blockRow * BOX + i;
            int col = blockCol * BOX + j;
            if (fixed[row][col] && grid[row][col] == val) {
                return true;
            }
        }
    }
    return false;
}


//function which initializes the bool fixed[SIZE][SIDE] board
void initFixed(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 0)
                fixed[i][j] = true;   // 'frozen'
            else
                fixed[i][j] = false;  // can be changed
        }
    }
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
