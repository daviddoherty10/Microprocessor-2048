#include <stdint.h>
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define GRID_SIZE 4
typedef struct gameState {
    uint8_t** grid;			 // 2D grid (allocate carefully)
    uint8_t currentMove;	 // e.g., 0=up, 1=right, 2=down, 3=left
    uint8_t moveSuccessful;	 // 1 if move changed the grid, else 0
    uint8_t gameIsOver;
    uint8_t biggestSquare;
} gameState;

struct gameState* newGame();
void collisionDetection(gameState* gs);
void nextMoveIsPossible(gameState* gs);
int secure_rand_int(int maxRange);
void freeGameState(gameState* gs);
void addNumberToRandomLocation(gameState *gs);
void largestTile(gameState *gs);
void pcNextMove(gameState* gs);

#endif
