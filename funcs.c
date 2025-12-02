#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"
void menu_item_1(void) {
    int resistor_bands = 0;
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
        WHITE = 9
    };
    enum colour_multiplier {
        BLACKM = 1,
        BROWNM = 10,
        REDM = 100,
        ORANGEM = 1000,
        YELLOWM = 10000,
        GREENM = 100000,
        BLUEM = 1000000,
        VIOLETM = 10000000,
        GOLDM = 10,
        SILVERM = 100
    };
    printf("\n>> Resistor values calculator\n");
    printf("\nHow many bands does your resistor have? Enter between 3,4,5 and 6\n");
    resistor_bands = get_input(3,6); //check if integer
    switch (resistor_bands) {
    case 3:
        char band_colour[100];
        printf("Enter first band colour:\n");
        get_str_input(band_colour,sizeof(band_colour));       
        break;
    case 4:
        char band_colour[100];
        printf("Enter first band colour:\n");
        get_str_input(band_colour,sizeof(band_colour));       
        break;
    case 5:
        printf("456");
        break;
    case 6:
        printf("789");
        break;
    default:
        printf("Looking forward to the Weekend");
    }
}

void menu_item_2(void) {
    printf("\n>> Menu 2\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 2 */
}

void menu_item_3(void) {
    printf("\n>> Menu 3\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 3 */
}

void menu_item_4(void) {
    printf("\n>> Menu 4\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 4 */
}

static int is_integer(const char *s)
{
    if (!s || !*s) return 0;

    if (*s == '+' || *s == '-') s++;

    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static int get_input(int a, int b)
{
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

void get_str_input(char *output, int size) {
    int valid;

    do {
        valid = 1;
        printf("Enter band colour: ");
        fgets(output, size, stdin);

        output[strcspn(output, "\n")] = '\0';

        for (int i = 0; output[i] != '\0'; i++) {
            if (!isalpha((unsigned char)output[i])) {
                valid = 0;
                break;
            }
            output[i] = toupper(output[i]); 
        }

        if (!valid)
            printf("Invalid input. Letters only.\n");

    } while (!valid);
}

void test(void){
    char band_colour[100];
    printf("Enter first band colour:\n");
    get_str_input(band_colour,sizeof(band_colour));
         
}