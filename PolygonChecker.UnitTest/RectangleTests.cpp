#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C"
{
#include "rectSolver.h"		// include any other .h files you would want to.
}

namespace RectanlgeTests
{
	TEST_CLASS(RectanlgeTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			//double points[8] = {};
			bool a = ifRightAngles(0, 0, true);
			Assert::AreEqual(a, true);
		}
		TEST_METHOD(RectSolver_Square1) {
			double points[8] = { 2,2,   -2,2,   -2,-2,   2,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square2) {
			double points[8] = { 2,2 ,-2,-2 ,-2,2 ,2,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square3) {
			double points[8] = { 2,1 ,1,2 ,2,3 ,3,2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
		TEST_METHOD(RectSolver_Square4) {
			double points[8] = { 2,3 ,3,2 ,1,2 ,2,1 };
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
			Assert::IsTrue(ifRightAngles(3.0, -1.0/3.0, false));
		}
		TEST_METHOD(RectSolver_RightAngle3) {
			Assert::IsTrue(ifRightAngles(0, -1, true));
		}
	};
}
