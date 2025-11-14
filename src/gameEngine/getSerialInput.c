#include "gameEngine.h"
#include "../utils/utils.h"

void pcNextMove(gameState* gs){
    while (1){
        char potentialNextMove = egetchar();

        // ignore CR/LF
        if (potentialNextMove == '\r' || potentialNextMove == '\n')
            continue;

        if (potentialNextMove == 'w' || potentialNextMove == 'a' ||
            potentialNextMove == 's' || potentialNextMove == 'd') {
            gs->currentMove = potentialNextMove;
            return;
        } else {
            const char returnMessage[] = "invalid Move\n\r";
            for (int i = 0; i < sizeof(returnMessage)-1; i++){
                eputchar(returnMessage[i]);
            }
        }
    }
}

