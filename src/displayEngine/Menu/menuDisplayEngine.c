#include "display.h"
#include <stm32f031x6.h>

//retruns 1 if single player and 2 if multi
int showMenu(uint16_t highScore) {
    int selection = 0;  
    int confirmed = 0;

    fillRectangle(0, 0, 128, 160, 0); // full black background

    // Print title and high score
    printTextX2("2048 Game", 20, 10, RGBToWord(0, 255, 0), 0);
    printText("High Score:", 10, 40, RGBToWord(255, 255, 255), 0);
    printNumber(highScore, 100, 40, RGBToWord(255, 255, 0), 0);

    while (!confirmed) {
        // Draw menu options
        uint16_t color1 = (selection == 0) ? RGBToWord(0, 255, 255) : RGBToWord(255, 255, 255);
        uint16_t color2 = (selection == 1) ? RGBToWord(0, 255, 255) : RGBToWord(255, 255, 255);

        // Erase previous menu area
        fillRectangle(0, 70, 128, 60, 0);

        printTextX2("Single Player", 10, 80, color1, 0);
        printTextX2("Multiplayer", 10, 110, color2, 0);

        // Handle buttons
        if ((GPIOA->IDR & (1 << 8)) == 0)  // up pressed
        {
            selection = 0;
        }
        if ((GPIOA->IDR & (1 << 11)) == 0)	// down pressed
        {
            selection = 1;
        }
        if ((GPIOB->IDR & (1 << 4)) == 0)  // right pressed
        {
            confirmed = 1;
        }
    }

    // show the user that their selection has been confirmed
    fillRectangle(0, 150, 128, 10, RGBToWord(0, 255, 0));
    printText("Loading...", 30, 150, RGBToWord(0, 255, 0), 0);

    if (selection == 0) {
        return 1;
    } else {
        return 2;
    }
}

