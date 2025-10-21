#include "gameEngine.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 4

struct gameState* newGame(){
    struct gameState *gs = malloc(sizeof(gameState));
    if (!gs){
        perror("Unable to allocate gameState");
        exit(1);
    }

    // allocate rows
    gs->grid = malloc(SIZE * sizeof(int*));
    if (!gs->grid) {
        perror("Failed to allocate grid rows");
        exit(1);
    }

    // allocate columns for each row
    for (int i = 0; i < SIZE; i++) {
        gs->grid[i] = calloc(SIZE, sizeof(int)); // initialize to 0
        if (!gs->grid[i]) {
            perror("Failed to allocate grid columns");
            exit(1);
        }
    }

    gs->moveSuccessful=-1;
    gs->gameIsOver = 0;
    gs->currentMove = -1;
    gs->biggestSquare= 2;
    return gs;
}

void freeGameState(gameState* gs) {
    for (int i = 0; i < SIZE; i++) {
        free(gs->grid[i]);
    }
    free(gs->grid);
    free(gs);
}
