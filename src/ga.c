#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"
#include "ga.h"

#define SIZE 9
#define BOX 3
#define BOARD_CELLS 81

int computeFitness(int grid[SIZE][SIZE]);

// calculating the fitness = sum of "errors" a board has but flipped :]
// so a number of correctly placed numbers
int computeFitness(int grid[SIZE][SIZE]) {
    int cost = 0;

    // rows
    for (int i = 0; i < SIZE; i++) {
        int count[SIZE + 1] = {0};
        for (int j = 0; j < SIZE; j++) {
            count[grid[i][j]]++;
        }
        for (int k = 1; k <= SIZE; k++) {
            if (count[k] > 1){
                cost += count[k] - 1;
            }
        }
    }

    // columns
    for (int j = 0; j < SIZE; j++) {
        int count[SIZE + 1] = {0};
        for (int i = 0; i < SIZE; i++) {
            count[grid[i][j]]++;
        }
        for (int k = 1; k <= SIZE; k++) {
            if (count[k] > 1){
                cost += count[k] - 1;
            }
        }
    }

    return BOARD_CELLS - cost;
}


