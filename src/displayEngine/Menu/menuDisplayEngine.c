#include "display.h"
#include <stm32f031x6.h>

#define BTN_UP    (1 << 8)   // GPIOA pin 8
#define BTN_DOWN  (1 << 11)  // GPIOA pin 11
#define BTN_SELECT (1 << 4)  // GPIOB pin 4 (reuse right button for "select")

// Returns: 1 = single player, 2 = multiplayer
int showMenu(uint16_t highScore) {
    int selection = 0; // 0 = single, 1 = multi
    int confirmed = 0;

    // Clear the screen
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
        if ((GPIOA->IDR & BTN_UP) == 0) {
            selection = 0;
        }
        if ((GPIOA->IDR & BTN_DOWN) == 0) {
            selection = 1;
        }

        if ((GPIOB->IDR & BTN_SELECT) == 0) {
            confirmed = 1;
        }

        delay(150); // debounce and prevent flicker
    }

    // Visual feedback for confirmation
    fillRectangle(0, 150, 128, 10, RGBToWord(0, 255, 0));
    printText("Loading...", 30, 150, RGBToWord(0, 255, 0), 0);
    delay(500);

    return (selection == 0) ? 1 : 2;
}

