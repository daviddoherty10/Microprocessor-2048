#include "gameEngine.h"

void collisionDetection(gameState* gs) {
    if (gs->currentMove == 'a') { // LEFT
        // Shift everything left
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE - 1; j++) {
                if (gs->grid[i][j] == 0 && gs->grid[i][j+1] != 0) {
                    gs->grid[i][j] = gs->grid[i][j+1];
                    gs->grid[i][j+1] = 0;
                }
            }
        }

        // Merge left
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE - 1; j++) {
                if (gs->grid[i][j] == gs->grid[i][j+1] && gs->grid[i][j] != 0) {
                    gs->grid[i][j] *= 2;
                    gs->grid[i][j+1] = 0;
                }
            }
        }

        // Cleanup pass
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE - 1; j++) {
                if (gs->grid[i][j] == 0 && gs->grid[i][j+1] != 0) {
                    gs->grid[i][j] = gs->grid[i][j+1];
                    gs->grid[i][j+1] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;

    } else if (gs->currentMove == 'd') { // RIGHT
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = GRID_SIZE - 1; j > 0; j--) {
                if (gs->grid[i][j] == 0 && gs->grid[i][j-1] != 0) {
                    gs->grid[i][j] = gs->grid[i][j-1];
                    gs->grid[i][j-1] = 0;
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = GRID_SIZE - 1; j > 0; j--) {
                if (gs->grid[i][j] == gs->grid[i][j-1] && gs->grid[i][j] != 0) {
                    gs->grid[i][j] *= 2;
                    gs->grid[i][j-1] = 0;
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = GRID_SIZE - 1; j > 0; j--) {
                if (gs->grid[i][j] == 0 && gs->grid[i][j-1] != 0) {
                    gs->grid[i][j] = gs->grid[i][j-1];
                    gs->grid[i][j-1] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;

    } else if (gs->currentMove == 'w') { // UP
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = 0; i < GRID_SIZE - 1; i++) {
                if (gs->grid[i][j] == 0 && gs->grid[i+1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i+1][j];
                    gs->grid[i+1][j] = 0;
                }
            }
        }

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = 0; i < GRID_SIZE - 1; i++) {
                if (gs->grid[i][j] == gs->grid[i+1][j] && gs->grid[i][j] != 0) {
                    gs->grid[i][j] *= 2;
                    gs->grid[i+1][j] = 0;
                }
            }
        }

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = 0; i < GRID_SIZE - 1; i++) {
                if (gs->grid[i][j] == 0 && gs->grid[i+1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i+1][j];
                    gs->grid[i+1][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;

    } else if (gs->currentMove == 's') { // DOWN
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = GRID_SIZE - 1; i > 0; i--) {
                if (gs->grid[i][j] == 0 && gs->grid[i-1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i-1][j];
                    gs->grid[i-1][j] = 0;
                }
            }
        }

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = GRID_SIZE - 1; i > 0; i--) {
                if (gs->grid[i][j] == gs->grid[i-1][j] && gs->grid[i][j] != 0) {
                    gs->grid[i][j] *= 2;
                    gs->grid[i-1][j] = 0;
                }
            }
        }

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int i = GRID_SIZE - 1; i > 0; i--) {
                if (gs->grid[i][j] == 0 && gs->grid[i-1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i-1][j];
                    gs->grid[i-1][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;

    } else {
        gs->moveSuccessful = 1; // invalid move
    }
}

