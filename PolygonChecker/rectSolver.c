#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "rectSolver.h"

char* analyzeRect(double* points) {

	double left1[2] = { *(points + 0), *(points + 1) };
	double left2[2];

	int l1in = 0;
	int l2in;
	//* for points[]
	//x1 = [0], y1 = [1]
	//x2 = [2], y2 = [3]
	//x3 = [4], y3 = [5]
	//x4 = [6], y4 = [7]

	if (*(points + 2) <= left1[0]) {
		left1[0] = *(points + 2);
		left1[1] = *(points + 3);
		l1in = 2;

		left2[0] = *(points + 0);
		left2[1] = *(points + 1);
		l2in = 0;
	}
	else {
		left2[0] = *(points + 2);
		left2[1] = *(points + 3);
		l2in = 2;
	}

	if (*(points + 4) < left1[0])
	{
		left2[0] = left1[0];
		left2[1] = left1[1];
		l2in = l1in;

		left1[0] = *(points + 4);
		left1[1] = *(points + 5);
		l1in = 4;
	}
	else if (*(points + 4) < left2[0])
	{
		left2[0] = *(points + 4);
		left2[1] = *(points + 5);
		l2in = 4;
	}

	if (*(points + 6) < left1[0]) {
		left2[0] = left1[0];
		left2[1] = left1[1];
		l2in = l1in;

		left1[0] = *(points + 6);
		left1[1] = *(points + 7);
		l1in = 6;
	}
	else if (*(points + 6) < left1[0])
	{
		left2[0] = *(points + 6);
		left2[1] = *(points + 7);
		l2in = 6;
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

	int r1in;
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (i * 2 != l1in && i * 2 != l2in) {
			right[0] = *(points + i * 2);
			right[1] = *(points + i * 2 + 1);
			r1in = i * 2;
		}
	}
	for (i = 0; i < 4; i++) {
		if (i * 2 != l1in && i * 2 != l2in && i * 2 != r1in) {
			right[2] = *(points + i * 2);
			right[3] = *(points + i * 2 + 1);
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

	//printf("%f,%f\t\t%f,%f\n", topleft[0], topleft[1], topright[0], topright[1]);
	//printf("%f,%f\t\t%f,%f\n", botleft[0], botleft[1], botright[0], botright[1]);

	double side1 = calculateDist(topleft[0], topleft[1], topright[0], topright[1]);
	double side2 = calculateDist(botleft[0], botleft[1], botright[0], botright[1]);
	double side3 = calculateDist(topleft[0], topleft[1], botleft[0], botleft[1]);
	double side4 = calculateDist(topright[0], topright[1], botright[0], botright[1]);

	double slope1 = calculateSlope(topleft[0], topleft[1], topright[0], topright[1], false);
	double slope2 = calculateSlope(botleft[0], botleft[1], botright[0], botright[1], false);

	bool vert = false;
	if (topleft[0] == botleft[0]) {
		vert = true;
	}
	double slope3 = calculateSlope(topleft[0], topleft[1], botleft[0], botleft[1], vert);
	bool ang1 = ifRightAngles(slope1, slope3, vert);
	bool ang3 = ifRightAngles(slope2, slope3, vert);

	vert = false;
	if (topright[0] == botright[0]) {
		vert = true;
	}
	double slope4 = calculateSlope(topright[0], topright[1], botright[0], botright[1], vert);
	bool ang2 = ifRightAngles(slope1, slope4, vert);
	bool ang4 = ifRightAngles(slope2, slope4, vert);

	if (side1 == side2 && side3 == side4 && ang1 && ang2 && ang3 && ang4) {
		return "Points DO form a rectangle.";
	}
	else {
		return "Points DO NOT form a rectangle.";
	}
	/*
	double x1 = *(points + 0);
	double y1 = *(points + 1);
	double x2 = *(points + 2);
	double y2 = *(points + 3);
	double x3 = *(points + 4);
	double y3 = *(points + 5);
	double x4 = *(points + 6);
	double y4 = *(points + 7);
	if ((x1 != x2 || y1 != y2) && (x2 != x3 || y2 != y3) && (x3 != x4 || y3 != y4) && (x4 != x1 || y4 != y1)) {
		if ((((x3 - x2) * (x1 - x2) + (y3 - y2) * (y1 - y2)) == 0) && (((x3 - x4) * (x1 - x4) + (y3 - y4) * (y1 - y4) == 0))) {
			return "Points FORM a rectangle";
		}
		else {
			return "Points DO NOT form a rectangle";
		}
	}
	else {
		return "Points DO NOT form a rectangle";
	}*/
}

double calculateSlope(double x1, double y1, double x2, double y2, bool vert) {
	if (!vert) {
		return (y2 - y1) / (x2 - x1);
	}
	return 0;
	
}

bool ifRightAngles(double s1, double s2, bool vert) {
	// -1 * (1/s2) may produce rounding errors, I'm not sure
	if (vert && s1 == 0) {
		return true;
	}
	if (s1 == -1 * (1 / s2)) {
		return true;
	}
	else {
		return false;
	}
}