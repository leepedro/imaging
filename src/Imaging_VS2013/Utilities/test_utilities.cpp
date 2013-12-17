#include <iostream>

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
void TestArray_imp(void)
{	// Test operators of Array<T, N>.

	// Default ctor with list initialization.
	Imaging::Array<T, 3> array1 = { 1, 2, 3 };
	Imaging::Array<T, 3> array2{ { 4, 5, 6 } };

	// Elements with missing initialization list is initialized with 0.
	Imaging::Array<T, 3> array3{ 7, 8 };

	// Following generates "C2078: too many initializers". Good!
	//Imaging::Array<T, 3> array4{ 7, 8, 9, 10 };
	
	Imaging::Array<int, 3> arrayInt = { 1, 2, 3 };
	Imaging::Array<T, 3> array4 = array1 + arrayInt;	// {2, 4, 6}
	Imaging::Array<T, 3> array5 = array1 - arrayInt;	// {0, 0, 0}
	Imaging::Array<T, 3> array6 = array1 * arrayInt;	// {1, 4, 9}

	Imaging::Array<T, 3> array7 = { 1, 2, 3 }, array8 = { 1, 2, 3 }, array9 = { 1, 2, 3 };
	array7 += arrayInt;	// {2, 4, 6}
	array8 -= arrayInt;	// {0, 0, 0}
	array9 *= arrayInt; // {1, 4, 9}

	Imaging::Array<T, 3> array10 = array1 + static_cast<int>(2);	// {3, 4, 5}
	Imaging::Array<T, 3> array11 = array1 - static_cast<int>(1);	// {0, 1, 2}
	Imaging::Array<T, 3> array12 = array1 * static_cast<int>(2);	// {2, 4, 6}

	Imaging::Array<T, 3> array13 = { 1, 2, 3 }, array14 = { 1, 2, 3 }, array15 = { 1, 2, 3 };
	array13 += static_cast<int>(2);	// {3, 4, 5}
	array14 -= static_cast<int>(1);	// {0, 1, 2}
	array15 *= static_cast<int>(2);	// {2, 4, 6}

	Imaging::Array<T, 3> array16 = { 1, 2, 3 }, array17 = { 1, 2, 3 }, array18 = { 1, 2, 3 },
		array19 = { 1, 2, 3 };
	++array16;	// {2, 3, 4}
	array17++;	// {2, 3, 4}
	--array18;	// {0, 1, 2}
	array19--;	// {0, 1, 2}
}

template <typename T>
void TestArrayException_imp(void)
{	// Test overflow exceptions of Array<T, N>.

	try
	{
		Imaging::Array<T, 1> array1 = { std::numeric_limits<T>::max() };	
		++array1;
		std::cout << array1.data[0] << " is a valid value." << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected exception!" << std::endl;
	}

	try
	{
		Imaging::Array<T, 1> array1 = { std::numeric_limits<T>::min() };
		--array1;
		std::cout << array1.data[0] << " is a valid value." << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected exception!" << std::endl;
	}
}

void TestArray(void)
{
	TestArray_imp<char>();					// T = char, U = int
	TestArray_imp<signed char>();			// T = signed char, U = int
	TestArray_imp<unsigned char>();			// T = unsigned char, U = int
	TestArray_imp<short>();					// T = short, U = int
	TestArray_imp<unsigned short>();		// T = unsigned short, U = int
	TestArray_imp<int>();					// T = int, U = int
	TestArray_imp<unsigned int>();			// T = unsigned int, U = int
	TestArray_imp<long long>();				// T = long long, U = int
	TestArray_imp<unsigned long long>();	// T = unsigned long long, U = int
	TestArray_imp<float>();					// T = float, U = int
	TestArray_imp<double>();				// T = double, U = int
	TestArrayException_imp<char>();
	TestArrayException_imp<signed char>();
	TestArrayException_imp<unsigned char>();
	TestArrayException_imp<short>();
	TestArrayException_imp<unsigned short>();
	TestArrayException_imp<int>();
	TestArrayException_imp<unsigned int>();
	TestArrayException_imp<long long>();
	TestArrayException_imp<unsigned long long>();
}

void TestContainers(void)
{
	TestArraySimple();
	TestArray();
}

int main(void)
{
	TestStdArray();
	TestContainers();
}
