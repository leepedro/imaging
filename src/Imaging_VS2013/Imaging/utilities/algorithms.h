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
}

#endif
