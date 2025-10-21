#ifndef GAMEENGINE_H
#define GAMEENGINE_H

typedef struct gameState {
    int** grid;           // 2D grid (allocate carefully)
    int currentMove;      // e.g., 0=up, 1=right, 2=down, 3=left
    int moveSuccessful;   // 1 if move changed the grid, else 0
    int gameIsOver;
} gameState;

void collisionDetection(gameState* gs);
void nextMoveIsPossible(gameState *gs);
int secure_rand_int(int maxRange);

#endif
