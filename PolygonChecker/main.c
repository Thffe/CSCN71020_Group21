#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "main.h"
#include "triangleSolver.h"

int side = 0;

int main() {
	bool continueProgram = true;
	while (continueProgram) {
		printWelcome();

		int shapeChoice = printShapeMenu();

		switch (shapeChoice)
		{
		case 1:
			printf_s("Triangle selected.\n");
			int triangleSides[3] = { 0, 0, 0 };
			int* triangleSidesPtr = getTriangleSides(triangleSides);
			//printf_s("! %d\n", triangleSidesPtr[0]);
			char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
			printf_s("%s\n", result);
			break;
		case 2:
			printf_s("Rectangle selected.\n");
			int rect[8];
			int* rectPtr = getRectPoints(rect);
			break;
		case 0:
			continueProgram = false;
			break;
		default:
			printf_s("Invalid value entered.\n");
			break;
		}
	}
	return 0;
}

int* getRectPoints(int points[]) {
	int gotten = 0;
	int arg, inX, inY;
	char c[10];
	printf_s("Enter 4 points of a rectangle:  (x y)\n");
	while (gotten < 4) {
		printf_s("Point %d:\n", gotten + 1);
		arg = scanf_s("%d %d", &inX, &inY);

		if (arg == 2) {
			points[gotten*2] = inX;
			points[gotten * 2 + 1] = inY;
			gotten++;
		}
		else {
			printf_s("bad input\n");
			scanf_s("%s", c, 100);//without this line, the program breaks. IDK why
		}
	}
	return points;
}

void calculatePerimeter(int rect[]) {
	double perimeter = 0;
	/*
	* for rect[]
	x1 = [0], y1 = [1]
	x2 = [2], y2 = [3]
	x3 = [4], y3 = [5]
	x4 = [6], y4 = [7]
	*/
							//	  x1	  y1		x2		y2
	perimeter += calculateDist(rect[0], rect[1], rect[2], rect[3]);
							//	  x1	  y1		x4		y4
	perimeter += calculateDist(rect[0], rect[1], rect[6], rect[7]);
							//	  x2	  y2		x3		y3
	perimeter += calculateDist(rect[2], rect[3], rect[4], rect[5]);
							//	  x3	  y3		x4		y4
	perimeter += calculateDist(rect[4], rect[5], rect[6], rect[7]);

	printf_s("The perimeter of your shape is %f units", perimeter);
}

double calculateDist(int x1, int y1, int x2, int y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}


//WIP
int* getTriangleSides(int* triangleSides) {
	int sides = 0;
	printf_s("Enter the three sides of the triangle:\n");
	int arg, in;
	char c[10];
	while (sides < 3) {
		printf_s("Side %d:\n", sides + 1);
		arg = scanf_s("%d", &in);

		if (arg && in > 0) {
			triangleSides[sides] = in;
			sides++;
		}
		else {
			printf_s("bad input\n");
			scanf_s("%s", c, 100);//without this line, the program breaks. IDK why
		}
	}
	return triangleSides;
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
	printf_s("2. Rectangle\n");
	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}

