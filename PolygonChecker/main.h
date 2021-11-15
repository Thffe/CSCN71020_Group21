#pragma once
double* getRectPoints(double* points);
double calculateDist(double x1, double y1, double x2, double y2);
double calculatePerimeter(double* points);

void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);
void printAngles(double* angle);

void printWelcome();
char printShapeMenu();