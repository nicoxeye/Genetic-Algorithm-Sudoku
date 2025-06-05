#ifndef ADDITIONAL_GA_H
#define ADDITIONAL_GA_H

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

#endif