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


int main(){
    srand(time(NULL));

    int grid[SIZE][SIZE];
    Individual population[POPULATION_SIZE];
    Individual next_population[POPULATION_SIZE];
    // creates a fixed boards and stores bools whether the places on the grid were filled before
    bool fixed[SIZE][SIZE];

    gameState.boxSize = 3;
    gameState.difficulty = 2;
    gameState.sizeOfTheBoard = 9;
    gameState.board = sudokuGenerator();

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = gameState.board[i][j];
        }
    }

    initFixed(grid, fixed);
    // if fixed has false then it is randomly filled with numbers 1 through 9
    // makes sure no digit is duplicated within the box
    fillGrid(grid, fixed);

    printf("initial filled grid:\n"); //informational
    printGrid(grid);

    initializePopulation(population, grid, fixed);

    Individual best_solution_ever;
    best_solution_ever.fitness = -1;

    // main loop
    for (int generation = 0; generation < NUM_GENERATIONS; generation++) {

        evaluatePopulation(population);

        Individual current_best = population[0];

        for (int i = 1; i < POPULATION_SIZE; i++) {
            if (population[i].fitness > current_best.fitness) {
                current_best = population[i];
            }
        }

        if (current_best.fitness > best_solution_ever.fitness) {
            best_solution_ever = current_best;
            printf("Generation %d: New better solution - fitness = %d\n", generation, best_solution_ever.fitness);
            getchar();
            getchar();
        } 
        else {
            printf("Generation %d: Current best fitness = %d, Best ever fitness = %d\n", generation, current_best.fitness, best_solution_ever.fitness);
            getchar();
            getchar();
        }

        for (int current_population_idx = 0; current_population_idx < POPULATION_SIZE; current_population_idx += 2) {
            Individual parent1 = selectParent(population);
            Individual parent2 = selectParent(population);

            Individual child1, child2;

            crossover(parent1, parent2, &child1, &child2);

            mutate(&child1, fixed);
            mutate(&child2, fixed);
            

            next_population[current_population_idx++] = child1;

            if (current_population_idx < POPULATION_SIZE) {
                next_population[current_population_idx++] = child2;
            }
        }

        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = next_population[i];
        }

    }


    printf("\n--- THE END ---\n");
    printf("Best solution (fitness = %d):\n", best_solution_ever.fitness);
    printGrid(best_solution_ever.grid);
    getchar();
    getchar();

    freeBoard();
    return 0;
}