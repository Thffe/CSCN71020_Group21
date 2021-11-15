#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "triangleSolver.h"

char* analyzeTriangle(double* sides) {
	double side1 = *(sides + 0);
	double side2 = *(sides + 1);
	double side3 = *(sides + 2);
	char* result = "";
	if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
		result = "Not a triangle";
	}
	else if (side1 == side2 && side1 == side3) {
		result = "Equilateral triangle";
	}
	else if ((side1 == side2 && side1 != side3) || (side1 == side3 && side1 != side2)) {
		result = "Isosceles triangle";
	}
	else {
		result = "Scalene triangle";
	}

	return result;
}