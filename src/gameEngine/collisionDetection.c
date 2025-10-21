typedef struct gameState {
    int** grid;
    int currentMove;
    int moveSuccessful;
} gameState;

void collisionDection(gameState* gs) {
    if (gs->currentMove == 'a') {
        // First move all tiles to the left without merging
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (gs->grid[i][j + 1] == 0) {
                        gs->grid[i][j + 1] = gs->grid[i][j];
                        gs->grid[i][j] = 0;
                    }
                }
            }
        }


        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j + 1] == 0) {
                    gs->grid[i][j + 1] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }
    } else if (gs->currentMove == 'd') {
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j > 0; j--) {
            }
        }

    } else if (gs->currentMove == 'w') {
    } else if (gs->currentMove == 's') {
    } else {
        gs->moveSuccessful = 1;
    }
}
