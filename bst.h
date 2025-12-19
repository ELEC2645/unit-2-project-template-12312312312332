#ifndef BST_H
#define BST_H

int basic_statistic_tool(void);
int comp(const void *a, const void *b);
double calculateMedian(const double data[], int n);
double calculateMode(const double data[], int n);
double calculateMean(const double data[], int n);
double calculateRange(const double data[], int n);
double calculateSD(double mean,const double data[], int n);
#endif