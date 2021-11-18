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
		TEST_METHOD(test2) {
			double points[8] = { 2,2,-2,2,-2,-2,2,-2 };
			char* a = analyzeRect(points);
			int b = strncmp(a, "Points DO form a rectangle.", 60);
			Assert::AreEqual(b, 0);
		}
	};
}
