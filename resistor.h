#ifndef RESISTOR_H
#define RESISTOR_H

enum colour_code {
    BLACK = 0,
    BROWN = 1,
    RED = 2,
    ORANGE = 3,
    YELLOW = 4,
    GREEN = 5,
    BLUE = 6,
    VIOLET = 7,
    GREY = 8,
    WHITE = 9,
    GOLD = -1,   
    SILVER = -2
};

static const int multipliers[] = {
    1,       // BLACK
    10,      // BROWN
    100,     // RED
    1000,    // ORANGE
    10000,   // YELLOW
    100000,  // GREEN
    1000000, // BLUE
    10000000, // VIOLET
};

#endif