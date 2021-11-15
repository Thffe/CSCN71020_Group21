#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "main.h"
#include "triangleSolver.h"

#define STRAIGHT_ANGLE 90
#define NUM_OF_TRIANGLE_SIDES 3
#define NUM_OF_RECTANGLE_SIDES 4
#define SUM_OF_ANGLES_IN_TRIANGLE 180
#define PI 3.14159265359

void printWelcome();
int printShapeMenu();
void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);
void printAngles(double* angle);

int main() {
	while(1) {
		printWelcome();

		int shapeChoice = printShapeMenu();
		double* triangleSidesPtr = (double*) calloc(NUM_OF_TRIANGLE_SIDES, sizeof(double));

		switch (shapeChoice) {
			case 1:
				printf_s("Triangle selected.\n");

				getTriangleSides(triangleSidesPtr);
				char* result = analyzeTriangle(triangleSidesPtr);

				if (strcmp(result, "Not a triangle") == 0) {
					printf_s("%s\n", result);
					break;
				}
				else {
					double* angles = calculateInsideAngles(triangleSidesPtr);

					printAngles(angles);
					printf_s("%s\n", result);
				}
				break;
			case 0: return 0;
			default: printf_s("Invalid value entered.\n"); break;
		}
		free(triangleSidesPtr);
	}
	return 0;
}

void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

int printShapeMenu() {
	printf_s("1. Triangle\n");
	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

//WIP
void getTriangleSides(double* triangleSides) {
	int i;
	for (i = 0; i < NUM_OF_TRIANGLE_SIDES; i++) {
		*(triangleSides + i) = scanCheckSide(i);
	}
}

double scanCheckSide(int i) {
	double side, temp; //temp is temporary variable
	bool correctnessIndicator = false;
	printf("Input side #%d of the triangle: ", i + 1);
	scanf_s("%lf", &side);
	do {
		if (side < 1) {
			printf("Incorrect, try entering side #%d again: ", i + 1);
			scanf_s("%lf", &temp);
			side = temp;
		}
		else correctnessIndicator = true;
	} while (correctnessIndicator == false);
	return side;
}

double* calculateInsideAngles(double* sides) {
	double* resultPTR = (double*)calloc(NUM_OF_TRIANGLE_SIDES, sizeof(double));

	double pow0 = pow(*(sides + 0), 2);
	double pow1 = pow(*(sides + 1), 2);
	double pow2 = pow(*(sides + 2), 2);
	*(resultPTR + 0) = radToDegree(acos((pow1 + pow2 - pow0) / (2 * *(sides + 1) * *(sides + 2))));
	*(resultPTR + 1) = radToDegree(acos((pow0 + pow1 - pow2) / (2 * *(sides + 0) * *(sides + 1))));
	*(resultPTR + 2) = SUM_OF_ANGLES_IN_TRIANGLE - *(resultPTR + 0) - *(resultPTR + 1);
	return resultPTR;
}

double radToDegree(double rad) {
	double degree;
	degree = (rad * 180) / PI;
	return degree;
}

void printAngles(double* angle) {
	int i;
	for (i = 0; i < NUM_OF_TRIANGLE_SIDES; i++) {
		printf("Angle #%d = %f\n", i, *(angle + i));
	}
}