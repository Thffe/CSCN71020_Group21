#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "rectSolver.h"

char* analyzeRect(double* points) {

	double left1[2] = {*(points + 0), *(points + 1)};
	double left2[2];

	/*
	* for points[]
	x1 = [0], y1 = [1]
	x2 = [2], y2 = [3]
	x3 = [4], y3 = [5]
	x4 = [6], y4 = [7]
	*/

	//doesnt acount for all cases
	if (*(points + 2) <= left1[0]) {
		left1[0] = *(points + 2);
		left1[1] = *(points + 3);

		left2[0] = *(points + 0);
		left2[1] = *(points + 1);
	}
	else {
		left2[0] = points[2];
		left2[1] = points[3];
	}

	if (*(points + 4) < left1[0]) 
	{
		left2[0] = left1[0];
		left2[1] = left1[1];

		left1[0] = *(points + 4);
		left1[1] = *(points + 5);
	}
	else if (*(points + 4) < left2[0]) 
	{
		left2[0] = points[4];
		left2[1] = points[5];
	}

	if (*(points + 6) < left1[0]) {
		left2[0] = left1[0];
		left2[1] = left1[1];

		left1[0] = *(points + 6);
		left1[1] = *(points + 7);
	}
	else if (*(points + 6) < left1[0]) 
		{
		left2[0] = points[6];
		left2[1] = points[7];
	}

	double topleft[2];
	double botleft[2];

	if (left1[1] > left2[1]) {
		topleft[0] = left1[0];
		topleft[1] = left1[1];

		botleft[0] = left2[0];
		botleft[1] = left2[1];
	}
	else {
		topleft[0] = left2[0];
		topleft[1] = left2[1];

		botleft[0] = left1[0];
		botleft[1] = left1[1];
	}

	double right[4];
	double topright[2];
	double botright[2];
	int i;
	for (i = 0; i < 4; i++) {
		int i2 = i * 2;
		int i2_1 = i * 2 + 1;
		if (*(points + i2) != topleft[0] && *(points + i2_1) != topleft[1] && *(points + i2) != botleft[0] && *(points + i2_1) != botleft[1]) {
			right[0] = *(points + i2);
			right[1] = *(points + i2_1);
		}
	}
	for (int i = 0; i < 4; i++) {
		int i2 = i * 2;
		int i2_1 = i * 2 + 1;
		if (*(points + i2) != topleft[0] && *(points + i2_1) != topleft[1] && *(points + i2) != botleft[0] && *(points + i2_1) != botleft[1] && *(points + i2) != right[0] && *(points + i2_1) != right[1]) {
			right[2] = *(points + i2);
			right[3] = *(points + i2_1);
		}
	}
	if (right[1] > right[3]) {
		topright[0] = right[0];
		topright[1] = right[1];

		botright[0] = right[2];
		botright[1] = right[3];
	}
	else {
		topright[0] = right[2];
		topright[1] = right[3];

		botright[0] = right[0];
		botright[1] = right[1];
	}
	
	double side1 = calculateDist(topleft[0], topleft[1], topright[0], topright[1]);
	double side2 = calculateDist(botleft[0], botleft[1], botright[0], botright[1]);
	double side3 = calculateDist(topleft[0], topleft[1], botleft[0], botleft[1]);
	double side4 = calculateDist(topright[0], topright[1], botright[0], botright[1]);

	double slope1 = calculateSlope(topleft[0], topleft[1], topright[0], topright[1]);
	double slope2 = calculateSlope(botleft[0], botleft[1], botright[0], botright[1]);
	double slope3 = calculateSlope(topleft[0], topleft[1], botleft[0], botleft[1]);
	double slope4 = calculateSlope(topright[0], topright[1], botright[0], botright[1]);

	bool ang1 = ifRightAngles(slope1, slope3);
	bool ang2 = ifRightAngles(slope1, slope4);
	bool ang3 = ifRightAngles(slope2, slope3);
	bool ang4 = ifRightAngles(slope2, slope4);

	if (side1 == side2 && side3 == side4 && ang1 && ang2 && ang3 && ang4) {
		return "Points DO form a rectangle.";
	}
	else {
		return "Points DO NOT form a rectangle.";
	}
}

double calculateSlope(double x1, double y1, double x2, double y2) {
	return (x2 - x1) / (y2 - y1);
	//ISSUE: will divide by zero if y2 == y1
}

bool ifRightAngles(double s1, double s2) {
	// -1 * (1/s2) may produce rounding errors
	if (s1 == -1 * (1 / s2)) {
		return true;
	}
	else {
		return false;
	}
}

