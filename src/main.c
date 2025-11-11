#include <stm32f031x6.h>
#include <stdint.h>

#include "./gameEngine/gameEngine.h"
#include "./displayEngine/Game/gameDisplayEngine.h"
#include "./displayEngine/Menu/menuDisplayEngine.h"
#include "./displayEngine/utils/display.h"
#include "./sound/sound.h"
#include "./displayEngine/GameOver/gameOver.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef* Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef* Port, uint32_t BitNumber, uint32_t Mode);
void initSerial(void);
void eputchar(char c);
char egetchar(void);
void eputs(char *String);
void printDecimal(int32_t Value);
volatile uint32_t milliseconds;


int main() {
    int highScore = 0;
    initClock();
    initSysTick();
    setupIO();
    int pressed = 0;

    while (1) {
        struct gameState* gs = newGame();
        // Menu To choose Single or Multiplayer and Shows high score
        int mode = showMenu(highScore);

        if (mode == 1) {
            fillRectangle(0, 0, 128, 160, RGBToWord(0, 0,0));
            drawGrid(gs);

            while (1){
                while(1) {
                    if ((GPIOA->IDR & (1 << 8)) == 0) {
                        gs->currentMove = 'w';
                        delay(100);
                        break;
                    }
                    if ((GPIOA->IDR & (1 << 11)) == 0) {
                        gs->currentMove = 's';
                        delay(100);
                        break;
                    }
                    if ((GPIOB->IDR & (1 << 5)) == 0) {
                        gs->currentMove = 'a';
                        delay(100);
                        break;
                    }
                    if ((GPIOB->IDR & (1 << 4)) == 0) {
                        gs->currentMove = 'd';
                        delay(100);
                        break;
                    }
                    delay(100);
                }
                drawGrid(gs);
                collisionDetection(gs);
                nextMoveIsPossible(gs);
                addNumberToRandomLocation(gs);
            }
        }else {
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
                    // Get the next move from the PC player
                    pcNextMove(gs);
                }
                whichPlayersMove++;

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
                        gameOver();
                        playNote(1000);
                        freeGameState(gs);
                        delay(3000);
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

void initSerial()
{
    /* On the nucleo board, TX is on PA2 while RX is on PA15 */
    RCC->AHBENR |= (1 << 17); // enable GPIOA
    RCC->APB2ENR |= (1 << 14); // enable USART1
    pinMode(GPIOA,2,2); // enable alternate function on PA2
    pinMode(GPIOA,15,2); // enable alternate function on PA15
                         // AF1 = USART1 TX on PA2
    GPIOA->AFR[0] &= 0xfffff0ff;
    GPIOA->AFR[0] |= (1 << 8);
    // AF1 = USART1 RX on PA15
    GPIOA->AFR[1] &= 0x0fffffff;
    GPIOA->AFR[1] |= (1 << 28);
    // De-assert reset of USART1 
    RCC->APB2RSTR &= ~(1u << 14);

    USART1->CR1 = 0; // disable before configuration
    USART1->CR3 |= (1 << 12); // disable overrun detection
    USART1->BRR = 48000000/9600; // assuming 48MHz clock and 9600 bps data rate
    USART1->CR1 |= (1 << 2) + (1 << 3); // enable Transmistter and receiver
    USART1->CR1 |= 1; // enable the UART

}

