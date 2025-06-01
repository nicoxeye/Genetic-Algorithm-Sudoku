#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"
#include "ga.h"
#include "util.h"

#define SIZE 9
#define BOX 3

int computeFitness(int grid[SIZE][SIZE]);
void calculateFitness(Individual *ind);
void evaluatePopulation(Individual population[]);
Individual selectParent(Individual population[]);
void crossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2, bool fixed[SIZE][SIZE]);
void mutate(Individual *individual, bool fixed[SIZE][SIZE]);


// fitness = total number of unique digits in all rows, columns, and boxes
//  max fittness = 243
int computeFitness(int grid[SIZE][SIZE]) {
    int fitness = 0;

    // rows
    for (int i = 0; i < SIZE; i++) {
        bool present[SIZE + 1] = {false};
        int uniqueCount = 0;
        for (int j = 0; j < SIZE; j++) {
            int val = grid[i][j];
            if (val >= 1 && val <= SIZE && !present[val]) {
                present[val] = true;
                uniqueCount++;
            }
        }
        fitness += uniqueCount;
    }

    // columns
    for (int j = 0; j < SIZE; j++) {
        bool present[SIZE + 1] = {false};
        int uniqueCount = 0;
        for (int i = 0; i < SIZE; i++) {
            int val = grid[i][j];
            if (val >= 1 && val <= SIZE && !present[val]) {
                present[val] = true;
                uniqueCount++;
            }
        }
        fitness += uniqueCount;
    }

    // boxes
    for (int boxRow = 0; boxRow < BOX; boxRow++) {
        for (int boxCol = 0; boxCol < BOX; boxCol++) {
            bool present[SIZE + 1] = {false};
            int uniqueCount = 0;
            for (int i = 0; i < BOX; i++) {
                for (int j = 0; j < BOX; j++) {
                    int val = grid[boxRow * BOX + i][boxCol * BOX + j];
                    if (val >= 1 && val <= SIZE && !present[val]) {
                        present[val] = true;
                        uniqueCount++;
                    }
                }
            }
            fitness += uniqueCount;
        }
    }

    return fitness;
}



void calculateFitness(Individual *ind) {
    ind->fitness = computeFitness(ind->grid);
}


// evaluating fitness for a whole population
void evaluatePopulation(Individual population[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        calculateFitness(&population[i]);
    }
}


void initializePopulation(Individual population[], int baseGrid[SIZE][SIZE], bool fixed[SIZE][SIZE]) {
    for (int p = 0; p < POPULATION_SIZE; p++) {
        // copying base grid
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                population[p].grid[r][c] = baseGrid[r][c];
            }
        }

        // filling free spaces
        fillGrid(population[p].grid, fixed);

        // calculating fitness
        calculateFitness(&population[p]);
    }
}


// parent selection (tournament selection)
Individual selectParent(Individual population[]) {
    // random 3
    int tournament_size = 3;
    Individual best_in_tournament = population[rand() % POPULATION_SIZE];

    for (int i = 1; i < tournament_size; i++) {
        Individual current = population[rand() % POPULATION_SIZE];
        if (current.fitness >= best_in_tournament.fitness) {
            best_in_tournament = current;
        }
    }

    return best_in_tournament;

}


// crossing two parents and creating children
void crossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2, bool fixed[SIZE][SIZE]) {
    // copy parents into children
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            child1->grid[i][j] = parent1.grid[i][j];
            child2->grid[i][j] = parent2.grid[i][j];
        }
    }

    if (((double)rand() / RAND_MAX) < CROSSOVER_RATE) {
        // a random row crossover point
        int crossover_row = rand() % SIZE;

        // swap rows from crossover_row to end, but skip fixed cells
        for (int i = crossover_row; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!fixed[i][j]) {
                    int temp = child1->grid[i][j];
                    child1->grid[i][j] = child2->grid[i][j];
                    child2->grid[i][j] = temp;
                }
            }
        }
    }

    child1->fitness = 0;
    child2->fitness = 0;
}


// mutating an individual
void mutate(Individual *individual, bool fixed[SIZE][SIZE]) {
    for (int boxRow = 0; boxRow < 3; boxRow++) {
        for (int boxCol = 0; boxCol < 3; boxCol++) {
            // mutation rate
            if (((double)rand() / RAND_MAX) < MUTATION_RATE) {
                // collecting mutable cells in the current 3x3 box
                // checks it with the fixed board :]
                int mutable_cells[SIZE][2];
                int count = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int r = boxRow * 3 + i;
                        int c = boxCol * 3 + j;
                        if (!fixed[r][c]) {
                            mutable_cells[count][0] = r;
                            mutable_cells[count][1] = c;
                            count++;
                        }
                    }
                }

                // must have at least two mutable cells to perform a swap
                if (count >= 2) {
                    // choosing the cells^
                    int idx1 = rand() % count;
                    int idx2 = rand() % count;
                    while (idx2 == idx1) idx2 = rand() % count;

                    int r1 = mutable_cells[idx1][0];
                    int c1 = mutable_cells[idx1][1];
                    int r2 = mutable_cells[idx2][0];
                    int c2 = mutable_cells[idx2][1];

                    // swapping values
                    int temp = individual->grid[r1][c1];
                    individual->grid[r1][c1] = individual->grid[r2][c2];
                    individual->grid[r2][c2] = temp;
                }
            }
        }
    }

    // additional mutation; swap two random non-fixed cells in the same row for more diversity cause it got stuck often in the first generation
    if (((double)rand() / RAND_MAX) < MUTATION_RATE) {
        int row = rand() % SIZE;

        // find non-fixed cells in row
        int mutable_cells[SIZE];
        int count = 0;

        for (int col = 0; col < SIZE; col++) {
            if (!fixed[row][col]) {
                mutable_cells[count++] = col;
            }
        }

        if (count >= 2) {
            int idx1 = rand() % count;
            int idx2 = rand() % count;
            while (idx2 == idx1) idx2 = rand() % count;

            int c1 = mutable_cells[idx1];
            int c2 = mutable_cells[idx2];

            int temp = individual->grid[row][c1];
            individual->grid[row][c1] = individual->grid[row][c2];
            individual->grid[row][c2] = temp;
        }
    }
}

