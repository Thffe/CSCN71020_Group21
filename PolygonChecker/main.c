#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"

#define STRAIGHT_ANGLE 90
#define NUM_OF_RECTANGLE_SIDES 4

//Rectangle calculations block
double* getRectPoints(double* points);

//Triangle calculations block
void getTriangleSides(double* triangleSides);
double scanCheckSide(int i);
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

				if (strcmp(res, "Points DO NOT form a rectangle.") == 0) {
					printf("Shape perimeter = %f\n", calculatePerimeter(rectanglePointsPtr));
					printf("%s\n", res);
					rectanglePointsPtr = NULL;
					free(rectanglePointsPtr);
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