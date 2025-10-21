typedef struct gameState {
    int** grid;
    int currentMove;
    int moveSuccessful;
} gameState;
void collisionDection(gameState* gs);
