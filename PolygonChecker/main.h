#pragma once
void printWelcome();
int printShapeMenu();

void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);
void printAngles(double* angle);

int* getRectPoints(int*);
void calculatePerimeter(int[]);
double calculateDist(int, int, int, int);
