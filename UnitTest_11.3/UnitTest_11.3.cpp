#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_11.3/lab_11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest113
{
	TEST_CLASS(UnitTest113)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(4, calc_n(1000));
		}
	};
}
