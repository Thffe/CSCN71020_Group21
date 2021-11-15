#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "main.h"
#include "triangleSolver.h"

#define STRAIGHT_ANGLE 90
#define NUM_OF_TRIANGLE_SIDES 3
#define NUM_OF_RECTANGLE_SIDES 4
#define SUM_OF_ANGLES_IN_TRIANGLE 180
#define PI 3.14159265359

double* getRectPoints(double* points);
double calculateDist(double x1, double y1, double x2, double y2);
double calculatePerimeter(double* points);

void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);
void printAngles(double* angle);

void printWelcome();
int printShapeMenu();

int main() {
	while(1) {
		printWelcome();

		int shapeChoice = printShapeMenu();
		double* triangleSidesPtr = (double*) calloc(NUM_OF_TRIANGLE_SIDES, sizeof(double));
		double* rectanglePointsPtr = (double*) calloc(NUM_OF_RECTANGLE_SIDES, sizeof(double));

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
			case 2:
				printf_s("Rectangle selected.\n");
				getRectPoints(rectanglePointsPtr);
				printf("Rectangle perimeter = %f", calculatePerimeter(rectanglePointsPtr));
			    break;
			case 0: return 0;
			default: printf_s("Invalid value entered.\n"); break;
		}
		free(triangleSidesPtr);
	}
	return 0;
}

//RECTANGLE part

double* getRectPoints(double* points) {
	int i, counter = 0;
	double pointX, pointY;
	printf_s("Enter 4 points of a rectangle (coordinates format x, y).\n");
	
	for (i = 0; i < NUM_OF_RECTANGLE_SIDES; i++) {
		printf("Input coordinates for point #%d: \n", i + 1);
		scanf_s("%lf", &pointX);
		scanf_s("%lf", &pointY);
		*(points + counter) = pointX;
		counter++;
		*(points + counter) = pointY;
		counter++;
	}
	return points;
}

double calculatePerimeter(double* points) {
	double perimeter = 0;
	/*
	* for rect[]
	x1 = [0], y1 = [1]
	x2 = [2], y2 = [3]
	x3 = [4], y3 = [5]
	x4 = [6], y4 = [7]
	*/
							//	  x1			y1				x2			y2
	perimeter += calculateDist(*(points + 0), *(points + 1), *(points + 2), *(points + 3));
							//	  x1			y1		x4		y4
	perimeter += calculateDist(*(points + 0), *(points + 1), *(points + 6), *(points + 7));
							//	  x2			y2				x3			y3
	perimeter += calculateDist(*(points + 2), *(points + 3), *(points + 4), *(points + 5));
							//	  x3			 y3				x4			y4
	perimeter += calculateDist(*(points + 4), *(points + 5), *(points + 6), *(points + 7));

	return perimeter;
}

double calculateDist(double x1, double y1, double x2, double y2) {
	double difX = x1 - x2;
	double difY = y1 - y2;
	double pow1 = pow(difX, 2);
	double pow2 = pow(difY, 2);
	double sum = pow1 = pow2;
	double result = sqrt(sum);
	printf("Side length = %f\n", result);
	return result;
}

//TRIANGLE PART:

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

//MENU part

  void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

int printShapeMenu() {
	printf_s("1. Triangle\n");
	printf_s("2. Rectangle\n");
	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

