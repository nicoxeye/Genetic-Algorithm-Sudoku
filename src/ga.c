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

#define POPULATION_SIZE 100
#define NUM_GENERATIONS 200
#define MUTATION_RATE 0.05
#define CROSSOVER_RATE 0.7

int computeFitness(int grid[SIZE][SIZE]);
void calculateFitness(Individual *ind);
void evaluatePopulation(Individual population[]);
Individual selectParent(Individual population[]);
void crossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2);
void mutate(Individual *individual, bool fixed[SIZE][SIZE]);
void runGA(Individual population[], bool fixed[SIZE][SIZE]);
void initializeIndividual(Individual *ind, int baseGrid[SIZE][SIZE], bool fixed[SIZE][SIZE]);


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
        if (current.fitness > best_in_tournament.fitness) {
            best_in_tournament = current;
        }
    }

    return best_in_tournament;

}


// crossing two parents and creating children
void crossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2) {
    // copying genes
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            child1->grid[i][j] = parent1.grid[i][j];
            child2->grid[i][j] = parent2.grid[i][j];
        }
    }


    if ((double)rand() / RAND_MAX < CROSSOVER_RATE) {
        int crossover_row = rand() % SIZE;
        int crossover_col = rand() % SIZE;

        for (int i = crossover_row; i < SIZE; i++) {
            for (int j = (i == crossover_row ? crossover_col : 0); j < SIZE; j++) {
                int temp = child1->grid[i][j];
                child1->grid[i][j] = child2->grid[i][j];
                child2->grid[i][j] = temp;
            }
        }
    }

    child1->fitness = 0;
    child2->fitness = 0;
}


// mutating individual
void mutate(Individual *individual, bool fixed[SIZE][SIZE]) {
    for (int boxRow = 0; boxRow < BOX; boxRow++) {
        for (int boxCol = 0; boxCol < BOX; boxCol++) {

            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                // picking two mutable positions in the same box
                int i1, j1, i2, j2;

                do {
                    i1 = boxRow * BOX + rand() % BOX;
                    j1 = boxCol * BOX + rand() % BOX;
                } while (fixed[i1][j1]);

                do {
                    i2 = boxRow * BOX + rand() % BOX;
                    j2 = boxCol * BOX + rand() % BOX;
                } while (fixed[i2][j2] || (i1 == i2 && j1 == j2));

                // swapping values
                int temp = individual->grid[i1][j1];
                individual->grid[i1][j1] = individual->grid[i2][j2];
                individual->grid[i2][j2] = temp;
            }
        }
    }
}
