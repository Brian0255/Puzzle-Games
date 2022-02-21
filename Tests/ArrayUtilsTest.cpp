
#include "pch.h"
#include "CppUnitTest.h"
#include "ArrayUtils.h"
#include<array>

#define arrSize3 3

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(Tests) {
public:
	TEST_METHOD(TestArrayAdding){ 

		std::array<int, arrSize3> arr1 = { 4,3,3 };
		std::array<int, arrSize3> arr2 = { 1,2,2 };

		std::array<int, arrSize3> expectedAdditionResult = { 5,5,5 };
		std::array<int, arrSize3> actualAdditionResult = ArrayUtils::addIntArrays(arr1, arr2);

		Assert::IsTrue(expectedAdditionResult == actualAdditionResult);

	}

	TEST_METHOD(TestArraySubtracting) {
		std::array<int, arrSize3> arr1 = { 1,3,0 };
		std::array<int, arrSize3> arr2 = { 3,2,4 };

		std::array<int, arrSize3> expectedSubtractionResult = { -2,1,-4 };
		std::array<int, arrSize3> actualSubtractionResult = ArrayUtils::subtractIntArrays(arr1, arr2);
		
		Assert::IsTrue(expectedSubtractionResult == actualSubtractionResult);
	}
	};
}
