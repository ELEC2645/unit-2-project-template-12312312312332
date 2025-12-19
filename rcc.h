#ifndef RCC_H
#define RCC_H

void resistor_colour_calc(void);
static int is_integer(const char *s);
static int get_int_input(int a, int b);
int getColourInput(void);
int calculateResistance34(int band1, int band2, int multiplier);
double calculateResistance56(int band1, int band2, int band3, int multiplier);
double tolerancechart(int tolerance);
int tempcoeffchart(int tempcoeff);
#endif