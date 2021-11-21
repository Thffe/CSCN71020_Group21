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

//This function transforms radians to degrees
double radToDegree(double rad) {
	double degree;
	degree = (rad * 180) / PI; //Here it uses the formula, which is used to count degrees out of radians. PI - pi number, equals to 3.14
	return degree;
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