#pragma once
#include <math.h>

#define PI 3.14159265358979323846
#define SUM_OF_ANGLES_IN_TRIANGLE 180
#define NUM_OF_TRIANGLE_SIDES 3

char* analyzeTriangle(double* sides);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);