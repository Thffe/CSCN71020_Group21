	#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "triangleSolver.h"

#define STRAIGHT_ANGLE 90
#define NUM_OF_TRIANGLE_SIDES 3
#define NUM_OF_RECTANGLE_SIDES 4
#define SUM_OF_ANGLES_IN_TRIANGLE 180

void printWelcome();
int printShapeMenu();
void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);

int main() {
	while(1) {
		printWelcome();

		int shapeChoice = printShapeMenu();

		switch (shapeChoice) {
			case 1:
				printf_s("Triangle selected.\n");
				double triangleSides[NUM_OF_TRIANGLE_SIDES] = { 0, 0, 0 };
				double* triangleSidesPtr = &triangleSides;
				getTriangleSides(triangleSidesPtr);


				char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
				printf_s("%s\n", result);
				break;
			case 0: return 0;
			default: printf_s("Invalid value entered.\n"); break;
		}
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