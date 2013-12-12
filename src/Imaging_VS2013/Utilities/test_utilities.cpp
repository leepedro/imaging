#include "containers.h"

void TestStdArray(void)
{	// Test std::array features.

	// Recomended form of brace initialization.
	std::array<int, 3> stdarray1 = { 1, 2, 3 };

	// Works without an error.
	std::array<int, 3> stdarray2{ { 4, 5, 6 } };

	// Compiles with intellisense error. Ignore the intellisense error.
	std::array<int, 3> stdarray3{ 4, 5, 6 };
}

void TestArraySimple(void)
{	// Simple test.

	// Good.
	Imaging::Array<int, 3> array1 = { 1, 2, 3 };

	// Should be good. Ignore intellisense error.
	Imaging::Array<int, 3> array2{ { 4, 5, 6 } };

	// Should be good. Ignore intellisense error.
	Imaging::Array<int, 3> array3{ 7, 8, 9 };
}

template <typename T>
void TestArray(void)
{
	// Default ctor with list initialization.
	Imaging::Array<T, 3> array1 = { 1, 2, 3 };
	Imaging::Array<T, 3> array2{ { 4, 5, 6 } };
	
	// Elements with missing initialization list is initialized with 0.
	Imaging::Array<T, 3> array3{ 7, 8 };

	// Following generates "C2078: too many initializers". Good!
	//Imaging::Array<T, 3> array4{ 7, 8, 9, 10 };
	
	Imaging::Array<T, 3> array4 = array1 + array2;
	Imaging::Array<T, 3> array5 = array1 - array2;
	Imaging::Array<T, 3> array6 = array1 * array2;
	++array1;
	array1++;
}


void TestContainers(void)
{
	TestArraySimple();
	
	TestArray<int>();
	TestArray<double>();
}

int main(void)
{
	TestStdArray();
	TestContainers();
}