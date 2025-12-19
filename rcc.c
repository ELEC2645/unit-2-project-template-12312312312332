#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "rcc.h"
#include "resistor.h"
void resistor_colour_calc(void){
    int resistor_bands = 0;
    printf("\n>> Resistor values calculator\n");
    printf("\nHow many bands does your resistor have? Enter between 3,4,5 and 6\n");
    resistor_bands = get_int_input(3,6); //check if integer
    int band1=0, band2=0, band3=0, multiplier=0, tol=0, temp=0,tempval=0;
    double resistance = 0, toleranceval=0;
    switch (resistor_bands) {
        case 3:     
            printf("\n3 band resistor:\n");
            printf("Enter first band colour: ");
            band1 = getColourInput();
            printf("Enter second band colour: ");
            band2 = getColourInput();
            printf("Enter third band colour: ");
            multiplier = getColourInput();
            resistance = calculateResistance34(band1, band2, multiplier);
            if (resistance < 1000) {
                printf("Resistance: %.2f Ω\n", resistance);
            }
            else if (resistance < 1000000) {
                printf("Resistance: %.2f kΩ\n", resistance / 1000.0);
            }
            else {
                printf("Resistance: %.2f MΩ\n", resistance / 1000000.0);
            }
            break;
        case 4:
            printf("\n4 band resistor:\n");
            printf("Enter first band colour: ");
            band1 = getColourInput();
            printf("Enter second band colour: ");
            band2 = getColourInput();
            printf("Enter third band colour: ");
            multiplier = getColourInput();
            printf("Enter fourth band colour: ");
            tol = getColourInput();  
            resistance = calculateResistance34(band1, band2, multiplier);
            toleranceval = tolerancechart(tol);
            if (toleranceval < 0){
                printf("Invalid tolerance colour code.\n");
            }
            else if (resistance < 1000 && toleranceval > 0) {
                printf("Resistance: %.2f Ω ± %.2f%%\n", resistance, toleranceval);
            }
            else if (resistance < 1000000 && toleranceval > 0) {
                printf("Resistance: %.2f kΩ ± %.2f%%\n", resistance / 1000.0, toleranceval);
            }
            else {
                printf("Resistance: %.2f MΩ ± %.2f%%\n", resistance / 1000000.0, toleranceval);
            }
            break;
        case 5:
            printf("\n5 band resistor:\n");
            printf("Enter first band colour: ");
            band1 = getColourInput();
            printf("Enter second band colour: ");
            band2 = getColourInput();
            printf("Enter third band colour: ");
            band3 = getColourInput();
            printf("Enter fourth band colour: ");
            multiplier = getColourInput();
            printf("Enter fifth band colour: ");
            tol = getColourInput();    
            resistance = calculateResistance56(band1, band2, band3, multiplier);
            toleranceval = tolerancechart(tol);
            if (toleranceval < 0){
                printf("Invalid tolerance colour code.\n");
            }
            else if (resistance < 1000) {
                printf("Resistance: %.2f Ω ± %.2f%%\n", resistance, toleranceval);
            }
            else if (resistance < 1000000) {
                printf("Resistance: %.2f kΩ ± %.2f%%\n", resistance / 1000.0, toleranceval);
            }
            else {
                printf("Resistance: %.2f MΩ ± %.2f%%\n", resistance / 1000000.0, toleranceval);
            }
            break;
        case 6:
            printf("\n6 band resistor:\n");
            printf("Enter first band colour: ");
            band1 = getColourInput();
            printf("Enter second band colour: ");
            band2 = getColourInput();
            printf("Enter third band colour: ");
            band3 = getColourInput();
            printf("Enter fourth band colour: ");
            multiplier = getColourInput();
            printf("Enter fifth band colour: ");
            tol = getColourInput();
            printf("Enter sixth band colour: ");
            temp = getColourInput();     
            resistance = calculateResistance56(band1, band2, band3, multiplier);
            toleranceval = tolerancechart(tol);
            tempval = tempcoeffchart(temp);
            if (toleranceval < 0){
                printf("Invalid tolerance colour code.\n");
            }
            else if (tempval < 0){
                printf("Invalid temperature coefficient colour code.\n");
            }
            else if (resistance < 1000) {
                printf("Resistance: %.2f Ω ± %.2f%%, Temp. Coeff.: %d ppm/K\n", resistance, toleranceval, tempval);
            }
            else if (resistance < 1000000) {
                printf("Resistance: %.2f kΩ ± %.2f%%, Temp. Coeff.: %d ppm/K\n", resistance / 1000.0, toleranceval, tempval);
            }
            else {
                printf("Resistance: %.2f MΩ ± %.2f%%, Temp. Coeff.: %d ppm/K\n", resistance / 1000000.0, toleranceval, tempval);
            }
            break;
        default:
            printf("Error\n");
    }
}

 
static int get_int_input(int a, int b){
    char buf[128];
    int valid_input = 0;
    int value = 0;
    do {
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        } 

        // strip trailing newline   
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter valid input!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= a && value <= b) {
                valid_input = 1;
            } else {
                printf("Invalid option!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static int is_integer(const char *s){
    if (!s || !*s) return 0;

    if (*s == '+' || *s == '-') s++;

    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

int getColourInput(void) {
    char input[20];
    int code;

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        // Convert to uppercase
        for (int i = 0; input[i] != '\0'; i++)
            input[i] = toupper((unsigned char)input[i]);

        // Convert string to colour code
        if (strcmp(input, "BLACK") == 0)  code = BLACK;
        else if (strcmp(input, "BROWN") == 0)  code = BROWN;
        else if (strcmp(input, "RED") == 0)    code = RED;
        else if (strcmp(input, "ORANGE") == 0) code = ORANGE;
        else if (strcmp(input, "YELLOW") == 0) code = YELLOW;
        else if (strcmp(input, "GREEN") == 0)  code = GREEN;
        else if (strcmp(input, "BLUE") == 0)   code = BLUE;
        else if (strcmp(input, "VIOLET") == 0) code = VIOLET;
        else if (strcmp(input, "GREY") == 0)   code = GREY;
        else if (strcmp(input, "WHITE") == 0)  code = WHITE;
        else if (strcmp(input, "GOLD") == 0)   code = GOLD;
        else if (strcmp(input, "SILVER") == 0) code = SILVER;
        else {
            printf("Please enter a valid resistor colour.\n");
            continue;
        }

        return code;
    }

}int calculateResistance34(int band1, int band2, int multiplier) {
    if (band1 == GOLD || band1 == SILVER || band2 == GOLD || band2 == SILVER) {
        printf("First and second bands cannot be gold or silver.\n");
        return -1;  
    }

    double multValue = 0;
    if (multiplier >= 0 && multiplier <= 7) {
        multValue = multipliers[multiplier];  
    } else if (multiplier == -1) { // GOLD
        multValue = 0.1;
    } else if (multiplier == -2) { // SILVER
        multValue = 0.01;
    } else {
        printf("Invalid multiplier colour.\n");
        return -1;
    }
    return (band1 * 10 + band2) * multValue;
}
double calculateResistance56(int band1, int band2, int band3, int multiplier) {
    if (band1 == GOLD || band1 == SILVER ||
        band2 == GOLD || band2 == SILVER ||
        band3 == GOLD || band3 == SILVER) {
        printf("First three bands cannot be GOLD or SILVER.\n");
        return -1;
    }

    double multValue = 0;
    if (multiplier >= 0 && multiplier <= 7) {
        multValue = multipliers[multiplier];
    } else if (multiplier == GOLD) {
        multValue = 0.1;
    } else if (multiplier == SILVER) {
        multValue = 0.01;
    } else {
        printf("Invalid multiplier colour.\n");
        return -1;
    }

    return (band1 * 100 + band2 * 10 + band3) * multValue;
}

void formatResistance(double resistance) {
    if (resistance < 1000) {
        printf("%.2f Ω\n", resistance);
    }
    else if (resistance < 1000000) {
        printf("%.2f kΩ\n", resistance / 1000.0);
    }
    else {
        printf("%.2f MΩ\n", resistance / 1000000.0);
    }
}
double tolerancechart (int tolerance) {
    if (tolerance == GOLD) {
        return 5.0;
    } else if (tolerance == SILVER) {
        return 10.0;
    } else if (tolerance == BROWN) {
        return 1.0; 
    } else if (tolerance == RED) {
        return 2.0; 
    } else if (tolerance == GREEN) {
        return 0.5; 
    } else if (tolerance == BLUE) {
        return 0.25; 
    } else if (tolerance == VIOLET) {
        return 0.1; 
    } else if (tolerance == GREY) {
        return 0.05; 
    } else {
        return -1; 
    }
}
int tempcoeffchart (int tempcoeff) {
    if (tempcoeff == BROWN) {
        return 100; 
    } else if (tempcoeff == RED) {
        return 50; 
    } else if (tempcoeff == ORANGE) {
        return 15; 
    } else if (tempcoeff == YELLOW) {
        return 25; 
    } else if (tempcoeff == BLUE) {
        return 10; 
    } else if (tempcoeff == VIOLET) {
        return 5; 
    } else {
        return -1; 
    }
}