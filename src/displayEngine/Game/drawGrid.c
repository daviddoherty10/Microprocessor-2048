#include "../../gameEngine/gameEngine.h"
#include "../../display.h"
#include <stdint.h>

//The tile size and gap
#define TILE_SIZE 30
#define TILE_GAP 5
// Where to start displaying the grid
#define GRID_ORIGIN_X 10
#define GRID_ORIGIN_Y 30


void drawGrid(gameState* gs) {
    // Setting up the backgound so that it is black and clearing it
    fillRectangle(0, 0, 160, 128, 0);  
    delay(50);

    //Map over the grip
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            //Get the current value 
            int value = gs->grid[i][j];
            // Calculate where the current tile should go and the gap for the next tile
            uint16_t x = GRID_ORIGIN_X + j * (TILE_SIZE + TILE_GAP);
            uint16_t y = GRID_ORIGIN_Y + i * (TILE_SIZE + TILE_GAP);

            // Depending on the value the tile the tile will be a different colour
            uint16_t color;
            if (value == 0){
                color = RGBToWord(30, 30, 30);
            }
            else if (value == 2){
                color = RGBToWord(200, 200, 180);
            }
            else if (value == 4){
                color = RGBToWord(220, 180, 120);
            }
            else if (value == 8){
                color = RGBToWord(255, 160, 90);
            }
            else{
                color = RGBToWord(255, 100, 60);
            }

            // Then draw the the tile with the x and y value that was a ssigned to it in the previous step with the colour
            fillRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
            drawRectangle(x, y, TILE_SIZE, TILE_SIZE, RGBToWord(255, 255, 255));

            // Don't need to print 0 values
            if (value != 0)
                printNumberX2(value, x + 6, y + 8, RGBToWord(0, 0, 0), color);
        }
    }
}
