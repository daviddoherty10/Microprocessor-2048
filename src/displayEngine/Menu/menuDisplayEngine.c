#include "../utils/display.h"
#include <stm32f031x6.h>

// returns 1 if single player, 2 if multi
int showMenu(uint16_t highScore) {
    int selection = 0;  
    int confirmed = 0;
    int redraw = 1;

    // previous states (for edge detection)
    int lastUp = 1;
    int lastDown = 1;
    int lastConfirm = 1;

    fillRectangle(0, 0, 128, 160, 0); // full black background

    // Print title and high score
    printTextX2("2048 Game", 20, 10, RGBToWord(0, 255, 0), 0);
    printText("High Score:", 10, 40, RGBToWord(255, 255, 255), 0);
    printNumber(highScore, 100, 40, RGBToWord(255, 255, 0), 0);

    while (!confirmed) {

        int up = (GPIOA->IDR & (1 << 8)) != 0;

        int down = (GPIOA->IDR & (1 << 11)) != 0;
        int confirmBtn = (GPIOB->IDR & (1 << 4)) != 0;

        // edge detection – only react on falling edge (1 -> 0)
        if (!up && lastUp) {
            selection = 0;
            redraw = 1;
        }
        if (!down && lastDown) {
            selection = 1;
            redraw = 1;
        }
        if (!confirmBtn && lastConfirm) {
            confirmed = 1;
        }

        lastUp = up;
        lastDown = down;
        lastConfirm = confirmBtn;

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

    return (selection == 0) ? 1 : 2;
}
