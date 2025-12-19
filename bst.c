#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "bst.h"
int basic_statistic_tool(void){
    char filename[128];
    printf("Enter file name (in xxx.txt format): \n");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\r\n")] = '\0';
    FILE *input = fopen(filename, "r");
    FILE *output = fopen("stats.txt", "w");

    if (!input || !output) {
        printf("Error opening file.\n");
        return 1;
    }
    double data[1000];
    char line[1000];
  
    fgets(line, 1000, input);

    int count = 0;
    while (fgets(line, 1000, input) && count < 1000) {
        data[count] = atof(line);
        count++;
    }

    qsort(data, count, sizeof(double), comp);

    double mean = 0.0;
    mean = calculateMean(data, count);
    fprintf(output, "statistic value\n");
    fprintf(output, "mean, %.2f\n", mean);

    double median = 0.0;
    median = calculateMedian(data, count);
    fprintf(output, "median, %.2f\n", median);

    double mode = 0.0;
    mode = calculateMode(data, count);
    fprintf(output, "mode, %.2f\n", mode);

    double range = 0.0;
    range = calculateRange(data, count);
    fprintf(output, "range, %.2f\n", range);

    double sd = 0.0;
    sd = calculateSD(mean, data, count);
    fprintf(output, "standard deviation, %.2f\n", sd);

    fclose(input);
    fclose(output);

    printf("Statistics saved to 'stats.txt'.\n");
    return 0;
}

double calculateMean(const double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += data[i];
    return ((double)sum / n);
}

int comp(const void *a, const void *b) {
    double da = *(const double *)a;
    double db = *(const double *)b;
    if (da < db) return -1;
    else if (da > db) return 1;
    else return 0;
}

double calculateMode(const double data[], int n) {
    double mode = data[0];
    int curr_count = 1;
    int max_count = 1;

    for (int i = 1; i < n; ++i) {
        if (data[i] == data[i - 1]) {
            ++curr_count;
        }
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                mode = data[i - 1];
            }
            curr_count = 1;
        }
    }
    if (curr_count > max_count) {
        mode = data[n - 1];
    }
    return mode;
}
double calculateMedian(const double data[], int n) {
    if (n % 2 == 0)
        return (data[n/2 - 1] + data[n/2]) / 2.0;
    else
        return data[n/2];
}

double calculateRange(const double data[], int n) {
    double min = data[0], max = data[n - 1];
    return max - min;
}

double calculateSD(double mean, const double data[], int n){
    double values = 0;
    for (int i = 0; i < n; i++) {
        values += pow(data[i] - mean, 2);
    }
    double variance = values / n;
    double standardDeviation = sqrt(variance);
    return standardDeviation;
}
