#ifndef GA_H
#define GA_H

#define SIZE 9
#define BOX 3

#define POPULATION_SIZE 100
#define NUM_GENERATIONS 200
#define MUTATION_RATE 0.05
#define CROSSOVER_RATE 0.7

// candidate structure
typedef struct {
    int grid[SIZE][SIZE];
    int fitness;
} Individual;


int computeFitness(int grid[SIZE][SIZE]);
void calculateFitness(Individual *ind);
void evaluatePopulation(Individual population[]);
Individual selectParent(Individual population[]);
void crossover(Individual parent1, Individual parent2, Individual *child1, Individual *child2);
void mutate(Individual *individual, bool fixed[SIZE][SIZE]);
void initializePopulation(Individual population[], int baseGrid[SIZE][SIZE], bool fixed[SIZE][SIZE]);

#endif