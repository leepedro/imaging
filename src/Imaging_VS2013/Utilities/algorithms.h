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
	template <typename InputIterator, typename OutputIterator>
	void AddRange(InputIterator itA, InputIterator itA_last, InputIterator itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Add(*itA, *itB, *itC);
	}

	// C = A - B
	template <typename InputIterator, typename OutputIterator>
	void SubtractRange(InputIterator itA, InputIterator itA_last, InputIterator itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Subtract(*itA, *itB, *itC);
	}

	// C = A * B
	template <typename InputIterator, typename OutputIterator>
	void MultiplyRange(InputIterator itA, InputIterator itA_last, InputIterator itB,
		OutputIterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			Multiply(*itA, *itB, *itC);
	}

	// A += B
	template <typename InputIterator, typename OutputIterator>
	void AddRange(OutputIterator itA, OutputIterator itA_last, InputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Add(*itA, *itB, *itA);
	}

	// A -= B
	template <typename InputIterator, typename OutputIterator>
	void SubtractRange(OutputIterator itA, OutputIterator itA_last, InputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Subtract(*itA, *itB, *itA);
	}

	// A *= B
	template <typename InputIterator, typename OutputIterator>
	void MultiplyRange(OutputIterator itA, OutputIterator itA_last, InputIterator itB)
	{
		for (; itA != itA_last; ++itA, ++itB)
			Multiply(*itA, *itB, *itA);
	}

	// ++A
	template <typename OutputIterator>
	void IncrementRange(OutputIterator it, OutputIterator itLast)
	{
		for (; it != itLast; ++it)
			Increment(*it);
	}

	// --A
	template <typename OutputIterator>
	void DecrementRange(OutputIterator it, OutputIterator itLast)
	{
		for (; it != itLast; ++it)
			Decrement(*it);
	}
}

#endif
