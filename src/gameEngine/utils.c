#include <stdlib.h>
#include "gameEngine.h"

int secure_rand_int(int maxRange) {
    return rand() % maxRange;
}
