#if !defined(ALGORITHMS_H)
#define ALGORITHMS_H

#include <stdexcept>

#include "safe_operations.h"

/*
Defines common operations for containers as non-member functions.
The arguments are defined as iterators instead of containers, so these functions can be
shared by multiple container classes.
*/
namespace Imaging
{
	// C = A + B
	template <typename InputIteratorA, typename InputIteratorB, typename OutputIterator>
	void AddRange(InputIteratorA itA, InputIteratorA itA_last, InputIteratorB itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Add(*itA, *itB, *itC);
	}

	// C = A - B
	template <typename InputIteratorA, typename InputIteratorB, typename OutputIterator>
	void SubtractRange(InputIteratorA itA, InputIteratorA itA_last, InputIteratorB itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Subtract(*itA, *itB, *itC);
	}

	// C = A * B
	template <typename InputIteratorA, typename InputIteratorB, typename OutputIterator>
	void MultiplyRange(InputIteratorA itA, InputIteratorA itA_last, InputIteratorB itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Multiply(*itA, *itB, *itC);
	}

	// B += A
	template <typename InputIterator, typename InOutputIterator>
	void AddRange(InputIterator itA, InputIterator itA_last, InOutputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Add(*itB, *itA, *itB);
	}

	// B -= A
	template <typename InputIterator, typename InOutputIterator>
	void SubtractRange(InputIterator itA, InputIterator itA_last, InOutputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Subtract(*itB, *itA, *itB);
	}

	// B *= A
	template <typename InputIterator, typename InOutputIterator>
	void MultiplyRange(InputIterator itA, InputIterator itA_last, InOutputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Multiply(*itB, *itA, *itB);
	}

	// ++A
	template <typename Iterator>
	void IncrementRange(Iterator it, Iterator itLast)
	{
		for (; it != itLast; ++it)
			Increment(*it);
	}

	// --A
	template <typename Iterator>
	void DecrementRange(Iterator it, Iterator itLast)
	{
		for (; it != itLast; ++it)
			Decrement(*it);
	}

	/*
	Fill the integral range value in an ascending order while preventing overflow by
	comparing the range value with the maximum value at each iteration. (inefficient)
	*/
	template <typename Iterator, typename T>
	std::enable_if_t<std::is_integral<T>::value, void>
		FillRange(Iterator it, Iterator itLast, T initValue)
	{
		for (auto value = initValue, limitMax = std::numeric_limits<T>::max(),
			limitMin = std::numeric_limits<T>::min(); it != itLast; ++it)
		{
			*it = value;
			if (value == limitMax)
				value = limitMin;
			else
				++value;
		}
	}

	/*
	Fill the floating point range value in an ascending order without the range check.
	*/
	template <typename Iterator, typename T>
	std::enable_if_t<std::is_floating_point<T>::value, void>
		FillRange(Iterator it, Iterator itLast, T initValue)
	{
		for (auto value = initValue; it != itLast; ++it, ++value)
			*it = value;
	}

	/*
	Iterators must NOT be be incremented because it will go beyond range at the final loop.
	Instead, compute the current position at each loop.
	*/
	template <typename InputIterator, typename OutputIterator, typename SizeType>
	void CopyLines(InputIterator itSrc, SizeType stepSrc, OutputIterator itDst,
		SizeType stepDst, SizeType nElemPerLine, SizeType nLines)
	{
		//for (auto H = 0; H != nLines; ++H, itSrc += stepSrc, itDst += stepDst)
		//	std::copy_n(itSrc, nElemPerLine, itDst);
		for (auto H = 0; H != nLines; ++H)
			std::copy_n(itSrc + H * stepSrc, nElemPerLine, itDst + H * stepDst);
	}
}

#endif
