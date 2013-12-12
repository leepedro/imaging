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
	template <typename T_ConstIterator, typename T_Iterator>
	void Add(T_ConstIterator itA, T_ConstIterator itA_last, T_ConstIterator itB,
		T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			SafeAdd(*itA, *itB, *itC);
	}

	// C = A - B
	template <typename T_ConstIterator, typename T_Iterator>
	void Subtract(T_ConstIterator itA, T_ConstIterator itA_last, T_ConstIterator itB,
		T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			SafeSubtract(*itA, *itB, *itC);
	}

	// C = A * B
	template <typename T_ConstIterator, typename T_Iterator>
	void Multiply(T_ConstIterator itA, T_ConstIterator itA_last, T_ConstIterator itB,
		T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
			SafeMultiply(*itA, *itB, *itC);
	}

	// C = A + b
	template <typename T_ConstIterator, typename T, typename T_Iterator>
	void Add(T_ConstIterator itA, T_ConstIterator itA_last, T b, T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itC)
			SafeAdd(*itA, b, *itC);
	}

	// C = A - b
	template <typename T_ConstIterator, typename T, typename T_Iterator>
	void Subtract(T_ConstIterator itA, T_ConstIterator itA_last, T b, T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, b, ++itC)
			SafeSubtract(*itA, b, *itC);
	}

	// C = A * b
	template <typename T_ConstIterator, typename T, typename T_Iterator>
	void Multiply(T_ConstIterator itA, T_ConstIterator itA_last, T b, T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, b, ++itC)
			SafeMultiply(*itA, b, *itC);
	}

	// ++A
	template <typename T_Iterator>
	void Increment(T_Iterator it, T_Iterator itLast)
	{
		for (; it != itLast; ++it)
			SafeIncrement(*it);
	}

	// --A
	template <typename T_Iterator>
	void Decrement(T_Iterator it, T_Iterator itLast)
	{
		for (; it != itLast; ++it)
			SafeDecrement(*it);
	}
}

#endif
