#pragma once
double* getRectPoints(double* points);
double calculatePerimeter(double* points);
double calculateDist(double x1, double y1, double x2, double y2);
double calculateArea(double* rectanglePTS);

void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
void printAngles(double* angle);

void printWelcome();
char printShapeMenu();