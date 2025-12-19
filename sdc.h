#ifndef SDC_H
#define SDC_H

void sensor_data_converter(void);
double ConvertSensorVoltage(int adc_value, int adc_max, double v_ref);
static int get_int_input(int a, int b);
static int is_integer(const char *s);
static double get_double_input(double a, double b);
static int is_double(const char *s);
double voltageToTemperature(double voltage,double sensitivity);
double voltageToGeneric(double voltage, double gradient, double offset);
#endif