#include "../../gameEngine/gameEngine.h"
#include "../utils/display.h"
#include <stdint.h>

//The tile size and gap
#define TILE_SIZE 23
#define TILE_GAP 5
// Where to start displaying the grid
#define GRID_ORIGIN_X 10
#define GRID_ORIGIN_Y 30

void drawGrid(gameState* gs) {
    // Only clear grid area, not full screen
        for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int value = gs->grid[i][j];

            uint16_t x = GRID_ORIGIN_X + j * (TILE_SIZE + TILE_GAP);
            uint16_t y = GRID_ORIGIN_Y + i * (TILE_SIZE + TILE_GAP);

            uint16_t color;
            switch(value) {
                case 0:   color = RGBToWord(30,30,30); break;
                case 2:   color = RGBToWord(200,200,180); break;
                case 4:   color = RGBToWord(220,180,120); break;
                case 8:   color = RGBToWord(255,160,90); break;
                default:  color = RGBToWord(255,100,60); break;
            }

            fillRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
            drawRectangle(x, y, TILE_SIZE, TILE_SIZE, RGBToWord(255,255,255));

            if (value != 0)
                printNumber(value, x + 6, y + 8, RGBToWord(0,0,0), color);
        }
    }
}

