#include "../../gameEngine/gameEngine.h"
#include "../../display.h"
#include <stdint.h>

#define TILE_SIZE 30
#define TILE_GAP 5
#define GRID_ORIGIN_X 10
#define GRID_ORIGIN_Y 30

#define RGB(r, g, b) RGBToWord(r, g, b)

void drawGrid(gameState* gs) {
    // Setting up the backgound so that it is black and clearing it
    fillRectangle(0, 0, 160, 128, RGB(0, 0, 0));  


    // Draw tiles
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int value = gs->grid[i][j];
            uint16_t x = GRID_ORIGIN_X + j * (TILE_SIZE + TILE_GAP);
            uint16_t y = GRID_ORIGIN_Y + i * (TILE_SIZE + TILE_GAP);

            uint16_t color;
            if (value == 0)
                color = RGB(30, 30, 30);
            else if (value == 2)
                color = RGB(200, 200, 180);
            else if (value == 4)
                color = RGB(220, 180, 120);
            else if (value == 8)
                color = RGB(255, 160, 90);
            else
                color = RGB(255, 100, 60);

            fillRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
            drawRectangle(x, y, TILE_SIZE, TILE_SIZE, RGB(255, 255, 255));

            if (value != 0)
                printNumberX2(value, x + 6, y + 8, RGB(0, 0, 0), color);
        }
    }
}
