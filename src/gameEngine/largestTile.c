#include "gameEngine.h"

void largestTile(gameState *gs) {
    int largtTile = 2;
    for (int i = 0;i < GRID_SIZE; i++) {
        for (int j = 0;j < GRID_SIZE; j++) {
            if (gs->grid[i][j] > largtTile) {
                largtTile = gs->grid[i][j];
            }
        }
    }
    gs->biggestSquare = largtTile;
}
