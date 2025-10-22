#include <stm32f031x6.h>
#include <stdint.h>

#include "./gameEngine/gameEngine.h"
#include "./displayEngine/Game/gameDisplayEngine.h"
#include "./displayEngine/Menu/menuDisplayEngine.h"
#include "display.h"
void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef* Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef* Port, uint32_t BitNumber, uint32_t Mode);

volatile uint32_t milliseconds;

const uint16_t deco1[] =
{
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    248,
    65415,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    65415,
    65415,
    8068,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    4096,
    4096,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    65535,
    65535,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7940,
    7940,
    7940,
    7940,
    0,
    0,
    0,
};
const uint16_t deco2[] =
{
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    248,
    65415,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    65415,
    65415,
    8068,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    4096,
    4096,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65415,
    65415,
    65415,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    65535,
    65535,
    65535,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    7936,
    7936,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    40224,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    40224,
    40224,
    7936,
    65535,
    7936,
    0,
    0,
    0,
    0,
    0,
    0,
    65315,
    40224,
    40224,
    7936,
    65535,
    40224,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65315,
    0,
    65315,
    65315,
    65315,
    65315,
    0,
    0,
};
const uint16_t deco3[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    7936,
    7936,
    4,
    4,
    4,
    4,
    4,
    4,
    7936,
    7936,
    0,
    0,
    65535,
    65535,
    4,
    4,
    4,
    4,
    4,
    4,
    65535,
    65535,
    0,
    0,
    7936,
    7936,
    4,
    4,
    4,
    4,
    4,
    4,
    7936,
    7936,
    0,
    0,
    0,
    0,
    0,
    4,
    4,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    24327,
    24327,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
const uint16_t dg1[] =
{
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    1994,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    1994,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    1994,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    16142,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    1994,
    1994,
    1994,
    16142,
    16142,
    0,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
    0,
    0,
    0,
    16142,
    16142,
    16142,
    16142,
    16142,
    16142,
    0,
    0,
    0,
};

int main() {
    int highScore = 0;
    initClock();
    initSysTick();
    setupIO();
    putImage(20, 80, 12, 16, dg1, 0, 0);
    int pressed = 0;

    while (1) {
        struct gameState* gs = newGame();
        int mode = showMenu(highScore);

        // Menu To choose Single or Multiplayer and Shows high score
        if (mode == 0) {
            // Single Player Main Game Loop
            while (1) {
                while (pressed != 1) {
                    if ((GPIOB->IDR & (1 << 4)) == 0)  // right pressed
                    {
                        pressed=1;
                        gs->currentMove = 1;
                    }
                    if ((GPIOB->IDR & (1 << 5)) == 0)  // left pressed
                    {
                        pressed=1;
                        gs->currentMove = 3;
                    }
                    if ((GPIOA->IDR & (1 << 11)) == 0)	// down pressed
                    {
                        pressed=1;
                        gs->currentMove = 2;
                    }
                    if ((GPIOA->IDR & (1 << 8)) == 0)  // up pressed
                    {
                        pressed=1;
                        gs->currentMove = 0;
                    }

                }
                pressed=0;
                delay(50);

                collisionDetection(gs);
                nextMoveIsPossible(gs);
                if (gs->gameIsOver == 1) {
                    if (highScore < gs->biggestSquare) {
                        highScore = gs->biggestSquare;
                        // Game over screen
                        // 5 Second delay or Button press
                        // Return to main menu
                        freeGameState(gs);
                    }
                }
                largestTile(gs);
                if (gs->biggestSquare > highScore) {
                    highScore = gs->biggestSquare;
                }

                addNumberToRandomLocation(gs);
                //Update Screen
                drawGrid(gs);
            }
        } else {
            // Multiplayer Loop
            while (1) {
                int whichPlayersMove = 0;
                if (whichPlayersMove % 2 == 0) {
                    while (pressed != 1) {
                        if ((GPIOB->IDR & (1 << 4)) == 0)  // right pressed
                        {
                            pressed=1;
                            gs->currentMove = 1;
                        }
                        if ((GPIOB->IDR & (1 << 5)) == 0)  // left pressed
                        {
                            pressed=1;
                            gs->currentMove = 3;
                        }
                        if ((GPIOA->IDR & (1 << 11)) == 0)	// down pressed
                        {
                            pressed=1;
                            gs->currentMove = 2;
                        }
                        if ((GPIOA->IDR & (1 << 8)) == 0)  // up pressed
                        {
                            pressed=1;
                            gs->currentMove = 0;
                        }
                    }
                }else {
                    // Serial Input for player 2
                }

                pressed=0;
                delay(50);

                collisionDetection(gs);
                nextMoveIsPossible(gs);
                if (gs->gameIsOver == 1) {
                    if (highScore < gs->biggestSquare) {
                        highScore = gs->biggestSquare;
                        // Game over screen
                        // 5 Second delay or Button press
                        // Return to main menu
                        freeGameState(gs);
                    }
                }
                largestTile(gs);
                if (gs->biggestSquare > highScore) {
                    highScore = gs->biggestSquare;
                }

                addNumberToRandomLocation(gs);
                //Update Sceen
                drawGrid(gs);
            }
        }
        freeGameState(gs);
    }


    return 0;
}
void initSysTick(void) {
    SysTick->LOAD = 48000;
    SysTick->CTRL = 7;
    SysTick->VAL = 10;
    __asm(" cpsie i ");	 // enable interrupts
}
void SysTick_Handler(void) {
    milliseconds++;
}
void initClock(void) {
    // This is potentially a dangerous function as it could
    // result in a system with an invalid clock signal - result: a stuck system
    // Set the PLL up
    // First ensure PLL is disabled
    RCC->CR &= ~(1u << 24);
    while ((RCC->CR & (1 << 25)));	// wait for PLL ready to be cleared

    // Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
    // inserted into Flash memory interface

    FLASH->ACR |= (1 << 0);
    FLASH->ACR &= ~((1u << 2) | (1u << 1));
    // Turn on FLASH prefetch buffer
    FLASH->ACR |= (1 << 4);
    // set PLL multiplier to 12 (yielding 48MHz)
    RCC->CFGR &= ~((1u << 21) | (1u << 20) | (1u << 19) | (1u << 18));
    RCC->CFGR |= ((1 << 21) | (1 << 19));

    // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
    RCC->CFGR |= (1 << 14);

    // and turn the PLL back on again
    RCC->CR |= (1 << 24);
    // set PLL as system clock source
    RCC->CFGR |= (1 << 1);
}
void delay(volatile uint32_t dly) {
    uint32_t end_time = dly + milliseconds;
    while (milliseconds != end_time)
        __asm(" wfi ");	 // sleep
}

void enablePullUp(GPIO_TypeDef* Port, uint32_t BitNumber) {
    Port->PUPDR = Port->PUPDR & ~(3u << BitNumber * 2);	 // clear pull-up resistor bits
    Port->PUPDR = Port->PUPDR | (1u << BitNumber * 2);	 // set pull-up bit
}
void pinMode(GPIO_TypeDef* Port, uint32_t BitNumber, uint32_t Mode) {
    /*
    */
    uint32_t mode_value = Port->MODER;
    Mode = Mode << (2 * BitNumber);
    mode_value = mode_value & ~(3u << (BitNumber * 2));
    mode_value = mode_value | Mode;
    Port->MODER = mode_value;
}
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py) {
    // checks to see if point px,py is within the rectange defined by x,y,w,h
    uint16_t x2, y2;
    x2 = x1 + w;
    y2 = y1 + h;
    int rvalue = 0;
    if ((px >= x1) && (px <= x2)) {
        // ok, x constraint met
        if ((py >= y1) && (py <= y2))
            rvalue = 1;
    }
    return rvalue;
}

void setupIO() {
    RCC->AHBENR |= (1 << 18) + (1 << 17);  // enable Ports A and B
    display_begin();
    pinMode(GPIOB, 4, 0);
    pinMode(GPIOB, 5, 0);
    pinMode(GPIOA, 8, 0);
    pinMode(GPIOA, 11, 0);
    enablePullUp(GPIOB, 4);
    enablePullUp(GPIOB, 5);
    enablePullUp(GPIOA, 11);
    enablePullUp(GPIOA, 8);
}
