#include "gameEngine.h"
#include "../utils/utils.h"

void pcNextMove(gameState* gs){
    while (1){
        char potentialNextMove = egetchar();
        if (potentialNextMove == 'w'|| potentialNextMove == 'a'|| potentialNextMove == 's' || potentialNextMove == 'd'){
            gs->currentMove = potentialNextMove;
            return;
        } else {
            char returnMessage[14] = "invalid Move\n\r";
            for (int i = 0; i < 14; i++){
                eputchar(returnMessage[i]);
            }
        }
    }
}
