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

	std::cout << "Testing constructors of Array<" << typeid(T).name() << ", N>." <<
		std::endl;

	// (default) Array<T, N>(void)
	Imaging::Array<T, 3> array1;	// NON-ZERO!
	array1.data[0] = 0;

	// Brace/Aggregate initialization.
	Imaging::Array<T, 3> array2 = { 1, 2, 3 };
	Imaging::Array<T, 3> array3{ 4, 5, 6 };
	Imaging::Array<T, 3> array4{ { 7, 8, 9 } };

	// Elements with missing initialization list is initialized with 0.
	Imaging::Array<T, 3> array5{ 7, 8 };

	// Following generates "C2078: too many initializers". Good!
	//Imaging::Array<T, 3> array4{ 7, 8, 9, 10 };
	
	std::cout << "Testing operators of Array<" << typeid(T).name() << ", N>." <<	std::endl;

	Imaging::Array<int, 3> arrayInt = { 1, 2, 3 };
	Imaging::Array<T, 3> array6 = array2 + arrayInt;	// {2, 4, 6}
	Imaging::Array<T, 3> array7 = array2 - arrayInt;	// {0, 0, 0}
	Imaging::Array<T, 3> array8 = array2 * arrayInt;	// {1, 4, 9}

	Imaging::Array<T, 3> array9 = { 1, 2, 3 }, array10 = { 1, 2, 3 }, array11 = { 1, 2, 3 };
	array9 += arrayInt;		// {2, 4, 6}
	array10 -= arrayInt;	// {0, 0, 0}
	array11 *= arrayInt;	// {1, 4, 9}

	Imaging::Array<T, 3> array12 = array2 + static_cast<int>(2);	// {3, 4, 5}
	Imaging::Array<T, 3> array13 = array2 - static_cast<int>(1);	// {0, 1, 2}
	Imaging::Array<T, 3> array14 = array2 * static_cast<int>(2);	// {2, 4, 6}

	Imaging::Array<T, 3> array15 = { 1, 2, 3 }, array16 = { 1, 2, 3 }, array17 = { 1, 2, 3 };
	array15 += static_cast<int>(2);	// {3, 4, 5}
	array16 -= static_cast<int>(1);	// {0, 1, 2}
	array17 *= static_cast<int>(2);	// {2, 4, 6}

	Imaging::Array<T, 3> array18 = { 1, 2, 3 }, array19 = { 1, 2, 3 }, array20 = { 1, 2, 3 },
		array21 = { 1, 2, 3 };
	++array18;	// {2, 3, 4}
	array19++;	// {2, 3, 4}
	--array20;	// {0, 1, 2}
	array21--;	// {0, 1, 2}

	// operator Array<U, N>()
	//Imaging::Array<T, 3> array22 = arrayInt;
	//arrayInt = array22;

	std::cout << "Completed testing Array<" << typeid(T).name() << ", N>." << std::endl;
}

template <typename T>
void TestArrayException_imp(void)
{	// Test overflow exceptions of Array<T, N>.

	std::cout << "Testing overflow exceptions of Array<" << typeid(T).name() << ", N>" <<
		std::endl;

	try
	{
		Imaging::Array<T, 1> array1 = { std::numeric_limits<T>::max() };	
		++array1;
		std::cout << array1.data[0] << " is a valid value." << std::endl;
	}
	catch (const std::overflow_error &ex)
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
	catch (const std::overflow_error &ex)
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
	Imaging::Array<double, 2> arrayd = { 2.5, 3.1 };
	Imaging::Array<long long, 2> array1 = Imaging::RoundAs<long long>(arrayd);
}

void TestRangeVector(void)
{
	std::vector<char> v1 = Imaging::GetRangeVector<char>(256);
	std::vector<signed char> v2 = Imaging::GetRangeVector<signed char>(256);
	std::vector<unsigned char> v3 = Imaging::GetRangeVector<unsigned char>(256);
	std::vector<short> v4 = Imaging::GetRangeVector<short>(256);
	std::vector<unsigned short> v5 = Imaging::GetRangeVector<unsigned short>(256);
	std::vector<int> v6 = Imaging::GetRangeVector<int>(256);
	std::vector<unsigned int> v7 = Imaging::GetRangeVector<unsigned int>(256);
	std::vector<long long> v8 = Imaging::GetRangeVector<long long>(256);
	std::vector<unsigned long long> v9 = Imaging::GetRangeVector<unsigned long long>(256);
	std::vector<float> v10 = Imaging::GetRangeVector<float>(256);
	std::vector<double> v11 = Imaging::GetRangeVector<double>(256);
}

void TestContainers(void)
{
	TestArraySimple();
	TestArray();
	TestRangeVector();
}

int main(void)
{
	TestStdArray();
	TestContainers();
}
