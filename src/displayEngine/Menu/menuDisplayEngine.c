#include "../utils/display.h"
#include <stm32f031x6.h>

// returns 1 if single player, 2 if multi
int showMenu(uint16_t highScore) {
    int selection = 0;  
    int confirmed = 0;
    int redraw = 1;

    fillRectangle(0, 0, 128, 160, 0); // full black background

    // Print title and high score
    printTextX2("2048 Game", 10, 10, RGBToWord(0, 255, 0), 0);
    printText("High Score:", 10, 40, RGBToWord(255, 255, 255), 0);
    printNumber(highScore, 100, 40, RGBToWord(255, 255, 0), 0);

    while (!confirmed) {


        // edge detection – only react on falling edge (1 -> 0)
        if ((GPIOA->IDR & (1 << 8)) == 0) {
            selection = 0;
            redraw = 1;
        }
        if ((GPIOA->IDR & (1 << 11)) == 0) {
            selection = 1;
            redraw = 1;
        }
        if ((GPIOB->IDR & (1 << 4)) == 0) {
            confirmed = 1;
        }

        if (redraw) {
            uint16_t color1 = (selection == 0) ? RGBToWord(0, 255, 255) : RGBToWord(255, 255, 255);
            uint16_t color2 = (selection == 1) ? RGBToWord(0, 255, 255) : RGBToWord(255, 255, 255);

            fillRectangle(0, 70, 128, 60, 0); // clear section only
            printText("Single Player", 10, 80, color1, 0);
            printText("Multiplayer", 10, 110, color2, 0);

            redraw = 0;
        }

        delay(40); // debounce
    }

    // small delay so holding confirm doesn't instantly trigger in game scene
    delay(150);

    fillRectangle(0, 0, 128, 160, 0);
    printText("Loading...", 30, 150, RGBToWord(0, 255, 0), 0);
    delay(100);

    return selection;
}
