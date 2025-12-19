#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"
#include "rcc.h"
#include "sdc.h"
#include "bst.h"
void menu_item_1(void) {
    resistor_colour_calc();
}

void menu_item_2(void) {
    sensor_data_converter();
}

void menu_item_3(void) {
    basic_statistic_tool();
}
