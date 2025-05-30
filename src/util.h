#ifndef UTIL_H
#define UTIL_H

#define SIZE 9
#define BOX 3

void fillGrid(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]);
bool fixedValueInBox(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE], int blockRow, int blockCol, int val);
void initFixed(int grid[SIZE][SIZE], bool fixed[SIZE][SIZE]);
void printGrid(int grid[SIZE][SIZE]);

#endif