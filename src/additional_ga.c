#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 9
#define BOX 3
#define SIZE 9
#define BOX 3

#define POPULATION_SIZE 100
#define NUM_GENERATIONS 200
#define MUTATION_RATE 0.05
#define CROSSOVER_RATE 0.8

// candidate structure
typedef struct {
    int grid[SIZE][SIZE];
    int fitness;
} Individual;


Individual rouletteSelection(Individual population[]);
void multiPointCrossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2, bool fixed[SIZE][SIZE]);
void uniformCrossover(Individual parent1, Individual parent2, Individual *child, bool fixed[SIZE][SIZE]);
void simpleMutate(Individual *individual, bool fixed[SIZE][SIZE]);

/*
roulette selection chooses individuals proportionally to their fitness
https://cratecode.com/info/roulette-wheel-selection
*/
Individual rouletteSelection(Individual population[]){
    // calculation total fitness
    int totalFitness = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        totalFitness += population[i].fitness;
    }

    // generatatitng a random value in from 0 to totalFitness
    double r = ((double) rand() / RAND_MAX) * totalFitness;

    // going through population to find the individual with the same fitness
    int cumulativeFitness = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        cumulativeFitness += population[i].fitness;
        if (r < cumulativeFitness) {
            return population[i];
        }
    }

    // fallback if something goes wrong
    return population[POPULATION_SIZE - 1];
}


// https://www.geeksforgeeks.org/crossover-in-genetic-algorithm/
void multiPointCrossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2, bool fixed[SIZE][SIZE]) {
    // copy parents into children
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            child1->grid[i][j] = parent1.grid[i][j];
            child2->grid[i][j] = parent2.grid[i][j];
        }
    }

    if (((double)rand() / RAND_MAX) < CROSSOVER_RATE) {
        // choosing two crossover points randomly (multi-point)
        int point1 = rand() % SIZE;
        int point2 = rand() % SIZE;
        if (point2 < point1) {
            int temp = point1;
            point1 = point2;
            point2 = temp;
        }

        /// iterates through each row starting from point1 up to and including point2
        // for each of these rows, it will swap cells between the two children, but only in the non-fixed cells
        for (int row = point1; row <= point2; row++) { 
            for (int col = 0; col < SIZE; col++) {
                if (!fixed[row][col]) {
                    int temp = child1->grid[row][col];
                    child1->grid[row][col] = child2->grid[row][col];
                    child2->grid[row][col] = temp;
                }
            }
        }
    }

    //resewting fitness
    child1->fitness = 0;
    child2->fitness = 0;
}


// https://www.geeksforgeeks.org/crossover-in-genetic-algorithm/
void uniformCrossover(Individual parent1, Individual parent2, Individual *child, bool fixed[SIZE][SIZE]) {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (fixed[i][j]) {
                // keep the fixed value
                child->grid[i][j] = parent1.grid[i][j];
            } else {
                // randomly choose which parent1 or parent2 to take cell from
                if (((double) rand() / RAND_MAX) < 0.5){
                    child->grid[i][j] = parent1.grid[i][j];
                }
                else {
                    child->grid[i][j] = parent2.grid[i][j];
                }
            }
        }
    }

    // resetting fitness
    child->fitness = 0;
}


// mutating an individual
void simpleMutate(Individual *individual, bool fixed[SIZE][SIZE]) {
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

}

