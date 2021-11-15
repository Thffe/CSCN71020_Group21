#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rectSolver.h"

char* analyzeRect(int points[8]) {

	int p1[2] = { points[0], points[1] };
	int p2[2] = { points[2], points[3] };
	int p3[2] = { points[4], points[5] };
	int p4[2] = { points[6], points[7] };

	int left1[2] = { points[0], points[1] };
	int left2[2];

	if (points[2] >= left1[0]) {
		left1[0] = points[2];
		left1[1] = points[3];

		left2[0] = points[0];
		left2[1] = points[1];
	}

	if (points[4] > left1[0]) {
		left2[0] = left1[0];
		left2[1] = left1[1];

		left1[0] = points[4];
		left1[1] = points[5];
	}

	if (points[6] > left1[0]) {
		left2[0] = left1[0];
		left2[1] = left1[1];

		left1[0] = points[6];
		left1[1] = points[7];
	}

	int topleft[2];
	int botleft[2];

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

	int right[4];
	int topright[2];
	int botright[2];

	for (int i = 0; i < 4; i++) {
		if (points[i * 2] != topleft[0] && points[i * 2 + 1] != topleft[1] &&
			points[i * 2] != botleft[0] && points[i * 2 + 1] != botleft[1]) {
			right[0] = points[i * 2];
			right[1] = points[i * 2 + 1];
		}
	}
	for (int i = 0; i < 4; i++) {
		if (points[i * 2] != topleft[0] && points[i * 2 + 1] != topleft[1] &&
			points[i * 2] != botleft[0] && points[i * 2 + 1] != botleft[1] &&
			points[i * 2] != right[0] && points[i * 2 + 1] != right[1]) {
			right[2] = points[i * 2];
			right[3] = points[i * 2 + 1];
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
		return "points DO form a rectangle.";
	}
	else {
		return "points DO NOT form a rectangle.";
	}
}

double calculateDist(int x1, int y1, int x2, int y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

double calculateSlope(int x1, int y1, int x2, int y2) {
	return (x2 - x1) / (y2 - y1);
}

bool ifRightAngles(double s1, double s2) {
	if (s1 == -1 * (1 / s2)) {
		return true;
	}
	else {
		return false;
	}
}

