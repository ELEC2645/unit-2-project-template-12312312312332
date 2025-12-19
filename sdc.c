#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "sdc.h"
void sensor_data_converter(void){
    int adc_value = 0;
    int adc_max = 0;
    double vref = 0.0;
    double voltage = 0.0;
    int sensor_type = 0;
    double sensitivity = 0;
    double temperature = 0;
    double gradient = 0;
    double offset = 0;
    double generic_value = 0;

    printf("\n>> Sensor Data Converter\n");
    printf("Enter number of bits for ADC (1 to 16):\n");
    adc_max = get_int_input(1, 16); 
    adc_max = (pow(2.0, adc_max)-1);

    printf("Enter ADC value (0 to ADC max):\n");
    adc_value = get_int_input(0, adc_max); 
    printf("Enter Vref in volts:\n");
    vref = get_double_input(0, 100.0);
    voltage = ConvertSensorVoltage(adc_value, adc_max, vref);
    if (voltage < 0) {
        printf("Error: Invalid ADC value or Vref.\n");
    } else {
        printf("Converted Voltage: %.4f V\n", voltage);
    }  
    printf("Enter your sensor type, 1 for temperature sensor, 2 for generic linear sensor:\n");
    sensor_type = get_int_input(1, 2);
    if (sensor_type == 1) {
        printf("Enter sensor sensitivity (mV/°C):\n");
        sensitivity = get_double_input(0, 10000.0);
        temperature = voltageToTemperature(voltage, sensitivity); 
        printf("Calculated temperature: %.2f °C\n", temperature);
    } else {
        printf("Enter sensor gradient:\n");
        gradient = get_double_input(-10000.0, 10000.0);
        printf("Enter sensor offset:\n");
        offset = get_double_input(-10000.0, 10000.0);
        generic_value = voltageToGeneric(voltage, gradient, offset);
        printf("Calculated generic sensor value: %.2f\n", generic_value);
    }
}

double ConvertSensorVoltage(int adc_value, int adc_max, double v_ref) {
    if (adc_value < 0 || adc_value > adc_max)
        return -1;  
    return ((double)adc_value / adc_max) * v_ref;
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
                printf("Invalid input!\n");
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

static double get_double_input(double a, double b){
    char buf[128];
    int valid_input = 0;
    double value = 0;
    do {
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        } 

        // strip trailing newline   
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_double(buf)) {
            printf("Enter valid input!\n");
            valid_input = 0;
        } else {
            value = (double)strtod(buf, NULL);
            if (value >= a && value <= b) {
                valid_input = 1;
            } else {
                printf("Invalid input!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static int is_double(const char *s) {
    int dot = 0;

    if (!s || !*s) return 0;

    if (*s == '+' || *s == '-') s++;

    if (!isdigit((unsigned char)*s) && *s != '.') return 0;

    while (*s) {
        if (*s == '.') {
            if (dot) return 0; 
            dot = 1;
        }
        else if (!isdigit((unsigned char)*s)) {
            return 0;
        }
        s++;
    }

    return 1;
}

double voltageToTemperature(double voltage,double sensitivity){
    return voltage / (sensitivity/1000);  
}

double voltageToGeneric(double voltage,double gradient,double offset){
    return voltage*gradient + offset;  
}