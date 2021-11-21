#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "main.h"
#include "triangleSolver.h"
#include "rectSolver.h"

#define STRAIGHT_ANGLE 90
#define NUM_OF_TRIANGLE_SIDES 3
#define NUM_OF_RECTANGLE_SIDES 4
#define SUM_OF_ANGLES_IN_TRIANGLE 180
#define PI 3.14159265359

//Rectangle calculations block
double* getRectPoints(double* points);
double calculatePerimeter(double* points);
double calculateDist(double x1, double y1, double x2, double y2);
double calculateArea(double* rectanglePTS);

//Triangle calculations block
void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
double* calculateInsideAngles(double* sides);
double radToDegree(double rad);
void printAngles(double* angle);

//MENU part 
void printWelcome();
char printShapeMenu();

int main() {
	while(1) {
		printWelcome();
		char shapeChoice = printShapeMenu();

		switch (shapeChoice) {
			case '1':
				printf_s("Triangle selected.\n");
				double* triangleSidesPtr = (double*)calloc(NUM_OF_TRIANGLE_SIDES, sizeof(double));

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

				free(triangleSidesPtr);
				break;
			case '2':
				printf_s("Rectangle selected.\n");
				double* rectanglePointsPtr = (double*)calloc(NUM_OF_RECTANGLE_SIDES, sizeof(double));

				getRectPoints(rectanglePointsPtr);
				char* res = (analyzeRect(rectanglePointsPtr));

				if (strcmp(res, "Points DO NOT form a rectangle") == 0) {
					printf("%s\n", res);
					break;
				}

				printf("Rectangle perimeter = %f\n", calculatePerimeter(rectanglePointsPtr));
				printf("Rectangle area = %f\n", calculateArea(rectanglePointsPtr));
				printf("%s\n", res);
				rectanglePointsPtr = NULL;
				free(rectanglePointsPtr);
			    break;
			case '0': 		
				exit(0);
			default: printf_s("Invalid value entered.\n"); break;
		}
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

//This function calculates the perimeter of 
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

//This function is needed to calculate the lenhts of the rectangle side by the points given.
double calculateDist(double x1, double y1, double x2, double y2) {
	double difX = x1 - x2;
	double difY = y1 - y2;
	double pow1 = pow(difX, 2);
	double pow2 = pow(difY, 2);
	double sum = pow1 + pow2;
	double result = sqrt(sum);
	return result;
}

//This function is needed to calculate the area of a rectangle by the formula S = a * b;
double calculateArea(double* rectanglePTS) {
	double side1 = calculateDist(*(rectanglePTS + 0), *(rectanglePTS + 1), *(rectanglePTS + 2), *(rectanglePTS + 3));
	double side2 = calculateDist(*(rectanglePTS + 0), *(rectanglePTS + 1), *(rectanglePTS + 6), *(rectanglePTS + 7));
	double side3 = calculateDist(*(rectanglePTS + 2), *(rectanglePTS + 3), *(rectanglePTS + 4), *(rectanglePTS + 5));
	double side4 = calculateDist(*(rectanglePTS + 4), *(rectanglePTS + 5), *(rectanglePTS + 6), *(rectanglePTS + 7));
	double area = -1;
	if (side1 != side2 || (side1 == side2 && side2 == side3 && side3 == side4 && side4 == side1)) {
		area = side1 * side2;
	}
	return area;
}

//TRIANGLE PART:

//This function takes user input of three double variables 
void getTriangleSides(double* triangleSides) {
	int i;
	for (i = 0; i < NUM_OF_TRIANGLE_SIDES; i++) {
		*(triangleSides + i) = scanCheckSide(i);
	}
}

//This function is needed to check user`s input of a side and ask for input again if the user fails to enter a correct value
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

//This function is neeeded to calculate the inside angles of a triangle
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
//This function transforms radians to degrees
double radToDegree(double rad) {
	double degree;
	degree = (rad * 180) / PI; //Here it uses the formula, which is used to count degrees out of radians. PI - pi number, equals to 3.14
	return degree;
}

//This function is used to print angles of the triangle
void printAngles(double* angle) {
	int i;
	printf("\n");
	for (i = 0; i < NUM_OF_TRIANGLE_SIDES; i++) {
		printf("Angle #%d = %f\n", i + 1, *(angle + i));
	}
}

//MENU part

//This function prints the invitation to the console
  void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

  //This function prints options for user to choose from and then returns the user`s choice
char printShapeMenu() {
	printf_s("1. Triangle\n");
	printf_s("2. Rectangle\n");
	printf_s("0. Exit\n");

	char shapeChoice;

	printf_s("Enter number: ");
	scanf_s(" %c", &shapeChoice, 1);

	return shapeChoice;
}

