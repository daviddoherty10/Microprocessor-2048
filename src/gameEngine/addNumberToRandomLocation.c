#include "gameEngine.h"

void addNumberToRandomLocation(gameState *gs) {
    int freeSpaces[GRID_SIZE * GRID_SIZE][2];  // simplify to 1D list
    int index = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (gs->grid[i][j] == 0) {
                freeSpaces[index][0] = i;
                freeSpaces[index][1] = j;
                index++;
            }
        }
    }

    if (index == 0)
        return;  // grid full, nothing to add

    int randInt = secure_rand_int(index - 1);
    int value = (secure_rand_int(2) + 1) * 2;  // 2 or 4

    gs->grid[freeSpaces[randInt][0]][freeSpaces[randInt][1]] = value;
}
