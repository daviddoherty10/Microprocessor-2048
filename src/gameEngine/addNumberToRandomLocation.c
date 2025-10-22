#include <strings.h>
#include "gameEngine.h"

void addNumberToRandomLocation(gameState *gs) {
    int freeSpaces[GRID_SIZE][2] = {};
    int index = 0;
    for (int i = 0;i<GRID_SIZE; i++) {
        for (int j = 0; j<GRID_SIZE; j++) {
            if (gs->grid[i][j]==0){
                freeSpaces[index][0] = i;
                freeSpaces[index][1] = j;
                index++;
            }
        }
    }
    int randInt = secure_rand_int(index);

    gs->grid[freeSpaces[randInt][0]][freeSpaces[randInt][1]] = (secure_rand_int(2)+1)*2;
}
