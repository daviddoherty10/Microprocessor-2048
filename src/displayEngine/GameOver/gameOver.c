#include "../../sound/sound.h"
#include "../utils/display.h"

void gameOver(void) {
    fillRectangle(0,0,128,160,RGBToWord(0,0,0));
    playNote(10000); 
    delay(1000);
    printTextX2("Game Over", 5, 15, RGBToWord(255, 0, 0), RGBToWord(0, 0, 0));
}
