#pragma once
#include "triangleSolver.h"
#include "rectSolver.h"

double* getRectPoints(double* points);

void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
void printAngles(double* angle);

void printWelcome();
char printShapeMenu();