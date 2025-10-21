typedef struct gameState {
    int** grid;
    int currentMove;
    int moveSuccessful;
    int gameIsOver;
} gameState;

void collisionDection(gameState* gs) {
    if (gs->currentMove == 'a') {
        // First move all tiles to the left without merging
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j + 1] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i][j + 1] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        // Them if the tile to the left is the same as the current tile then we'll merge them
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j + 1] == gs->grid[i][j]) {
                    gs->grid[i][j] = gs->grid[i][j] * 2;
                    gs->grid[i][j + 1] = 0;
                    j++;
                }
            }
        }

        // Finally clean up by moving all the tiles to the left by moving them past all the used white space
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j + 1] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i][j + 1] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;
    } else if (gs->currentMove == 'd') {
        // First shift all the tiles to the right without merging
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j > 0; j--) {
                if (gs->grid[i][j-1] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i][j-1] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        // Merge all tiles
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j > 0; j--) {
                if (gs->grid[i][j] == gs->grid[i][j-1] && gs->grid[i][j] != 0) {
                    gs->grid[i][j-1] = gs->grid[i][j] *2;
                    gs->grid[i][j] = 0;
                }
            }
        }

        // Cleanup all tiles by filling in blanks
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j > 0; j--) {
                if (gs->grid[i][j-1] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i][j-1] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;
    } else if (gs->currentMove == 'w') {
        // Move everything up without merging
        for (int i = 4; i > 1; i--) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j] == 0 && gs->grid[i-1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i-1][j];
                    gs->grid[i-1][j] = 0;
                }
            }
        }

        // Merge
        for (int i =4; i > 1; i--) {
            for (int j = 0; j < 4; j++){
                if (gs->grid[i][j] == gs->grid[i-1][j] && gs->grid[i][j] != 0){
                    gs->grid[i][j] = gs->grid[i][j] *2;
                    gs->grid[i-1][j] = 0;
                }
            }

        }

        for (int i = 4; i > 1; i--) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i][j] == 0 && gs->grid[i-1][j] != 0) {
                    gs->grid[i][j] = gs->grid[i-1][j];
                    gs->grid[i-1][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;
    } else if (gs->currentMove == 's') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i+1][j] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i+1][j] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        for (int i =0; i < 3; i ++){
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i + 1][j] == gs->grid[i][j] && gs->grid[i][j] != 0) {
                    gs->grid[i+1][j] = gs->grid[i][j] *2;
                    gs->grid[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (gs->grid[i+1][j] == 0 && gs->grid[i][j] != 0) {
                    gs->grid[i+1][j] = gs->grid[i][j];
                    gs->grid[i][j] = 0;
                }
            }
        }

        gs->moveSuccessful = 0;
    } else {
        gs->moveSuccessful = 1;
    }
}
