#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "triangleSolver.h"	
}

namespace triangleSolverTests
{
	TEST_CLASS(triangleSolverTests)
	{
	public:
		//Tests T001, T002, T003, T004, T005 test if function analyzeTriangle from triangleSolver.c do produce a correct result
		TEST_METHOD(T001_analyzeTriangle_4and4and4)
		{
			char* expected = "Equilateral triangle";	
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 4;
			*(sides + 1) = 4;
			*(sides + 2) = 4;
			char* res = analyzeTriangle(sides);
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(T002_analyzeTriangle_25and25and25)
		{
			char* expected = "Equilateral triangle";
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 25.5;
			*(sides + 1) = 25.5;
			*(sides + 2) = 25.5;
			char* res = analyzeTriangle(sides);
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(T003_analyzeTriangle_3andm5and4)
		{
			char* expected = "Not a triangle";
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 3;
			*(sides + 1) = -5;
			*(sides + 2) = 4;
			char* res = analyzeTriangle(sides);
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(T004_analyzeTriangle_4and4and5)
		{
			char* expected = "Isosceles triangle";
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 4;
			*(sides + 1) = 4;
			*(sides + 2) = 5;
			char* res = analyzeTriangle(sides);
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(T005_analyzeTriangle_3and4and5)
		{
			char* expected = "Scalene triangle";
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 3;
			*(sides + 1) = 4;
			*(sides + 2) = 5;
			char* res = analyzeTriangle(sides);
			Assert::AreEqual(expected, res);
		}

		//Tests T006, T007 test if radToDegree function produces a correct result
		TEST_METHOD(T006_radToDegree_1)
		{
			//Assert::AreEqual compared expected with the actual result and told that 57.2958 is not equal to 57.2958
			//So to compare double variables we need to add tolerance
			double tolerance = 0.0001;
			double expected = 57.2958;
			double res = radToDegree(1);
		
			Assert::AreEqual(expected, res, tolerance);	
		}
		TEST_METHOD(T007_radToDegree_m1)
		{
			//Assert::AreEqual compared expected with the actual result and told that -57.2958 is not equal to -57.2958
			//So to compare double variables we need to add tolerance
			double tolerance = 0.0001;
			double expected = -57.2958;
			double res = radToDegree(-1);
			
			Assert::AreEqual(expected, res, tolerance);
		}
		
		//Tests T008, T009, T010 check if at least one angle is counted correctly
		TEST_METHOD(T008_calculateInsideAngles_3and4and5_angle2)
		{
			double expected = 90;
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 3;
			*(sides + 1) = 4;
			*(sides + 2) = 5;
			double* angles = calculateInsideAngles(sides);
			Assert::AreEqual(expected, *(angles + 1));
		}
		TEST_METHOD(T009_calculateInsideAngles_4and4and4_angle3)
		{
			double tolerance = 0.01;
			double expected = 60;
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 4;
			*(sides + 1) = 4;
			*(sides + 2) = 4;
			double* angles = calculateInsideAngles(sides);
			Assert::AreEqual(expected, *(angles + 2), tolerance);
		}
		TEST_METHOD(T010_calculateInsideAngles_4and4and5_angle1)
		{
			double tolerance = 0.00001;
			double expected = 51.317813;
			double* sides = (double*)calloc(3, sizeof(double));
			*(sides + 0) = 4;
			*(sides + 1) = 4;
			*(sides + 2) = 5;
			double* angles = calculateInsideAngles(sides);
			Assert::AreEqual(expected, *(angles + 0), tolerance);
		}
	};
}