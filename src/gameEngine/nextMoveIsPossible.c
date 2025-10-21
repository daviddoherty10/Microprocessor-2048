#include "collisionDetection.h"
void nextMoveIsPossible(gameState *gs){

    // If there is a 0 (a blank square) then a move is possible
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gs->grid[i][j] == 0) {
                return;
            }
        }
    }

    // Check if there are two tile that are the the same to the side of each other
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 4; j++){
            if (gs->grid[i +1][j] == gs->grid[i][j]){
                return;
            }
        }
    }

    // Check if there are two tiles that are the same above or below
    for (int i = 0; i <4; i++) {
        for (int j = 0; j< 3; j++) {
            if (gs->grid[i][j+1] == gs->grid[i][j]){
                return;
            }
        }
    }

    gs->gameIsOver = 1;
}
