#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C"
{
#include "rectSolver.h"	
#include "main.h"		// include any other .h files you would want to.
}

namespace RectanlgeTests
{
	TEST_CLASS(RectanlgeTests)
	{
	public:

		TEST_METHOD(RectSolver_Square1_1) {
			double points[8] = { 2,2,   -2,2,   -2,-2,   2,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square1_2) {
			double points[8] = { 2,2 ,-2,-2 ,-2,2 ,2,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square1_3) {
			double points[8] = { -2,-2 ,2,2 ,2,-2 ,-2,2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square1_4) {
			double points[8] = { 2,-2 ,-2,-2 ,2,2 ,-2,2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square2_1) {
			double points[8] = { 2,1 ,1,2 ,2,3 ,3,2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square2_2) {
			double points[8] = { 2,3 ,3,2 ,1,2 ,2,1 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square2_3) {
			double points[8] = { 1,2 ,2,3 ,2,1 ,3,2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Rect1_1) {
			double points[8] = { 2,2 ,2,-2 ,-5,2 ,-5,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Rect1_2) {
			double points[8] = { 3,0 ,0,3 ,-2,-5 ,-5,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Rect2_1) {
			double points[8] = { 0.3,2.1 ,-2.4,1.2 ,-0.6,-4.2 ,2.1,-3.3 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Slope1) {
			double a = calculateSlope(1,1,2,2,false);
			Assert::AreEqual(a, 1.0);
		}
		TEST_METHOD(RectSolver_Slope2) {
			double a = calculateSlope(1, 1, 4, 2, false);
			Assert::AreEqual(a, 1.0 / 3.0);
		}
		TEST_METHOD(RectSolver_Slope3) {
			double a = calculateSlope(1, 1, 2, 4, false);
			Assert::AreEqual(a, 3.0);
		}
		TEST_METHOD(RectSolver_RightAngle1) {
			Assert::IsTrue(ifRightAngles(1, -1, false));
		}
		TEST_METHOD(RectSolver_RightAngle2) {
			Assert::IsTrue(ifRightAngles(3, -0.33, false));
		}
		TEST_METHOD(RectSolver_RightAngle3) {
			Assert::IsTrue(ifRightAngles(0, -1, true));
		}
		TEST_METHOD(RectSolver_Distance1) {
			double dist = calculateDist(2,2 ,-2,2);
			Assert::AreEqual(dist, 4.0);
		}
		TEST_METHOD(RectSolver_Distance2) {
			double dist = calculateDist(-5,-5 ,5,5);
			Assert::AreEqual(dist, sqrt(200));
		}
		TEST_METHOD(RectSolver_Distance3) {
			double dist = calculateDist(2, -6, -3, 5);
			Assert::AreEqual(dist, sqrt(146));
		}
		TEST_METHOD(RectSolver_CalculateArea1) {
			double expected = 4;
			double* points = (double*)calloc(8, sizeof(double));
			*(points + 0) = 1;
			*(points + 1) = 1;
			*(points + 2) = 1;
			*(points + 3) = -1;
			*(points + 4) = -1;
			*(points + 5) = -1;
			*(points + 6) = -1;
			*(points + 7) = 1;
			double area = calculateArea(points);
			Assert::AreEqual(expected, area);
		}
		TEST_METHOD(RectSolver_CalculateArea2) {
			double expected = 16;
			double* points = (double*)calloc(8, sizeof(double));
			*(points + 0) = 2;
			*(points + 1) = 2;
			*(points + 2) = 2;
			*(points + 3) = -2;
			*(points + 4) = -2;
			*(points + 5) = -2;
			*(points + 6) = -2;
			*(points + 7) = 2;
			double area = calculateArea(points);
			Assert::AreEqual(expected, area);
		}
	};
}
