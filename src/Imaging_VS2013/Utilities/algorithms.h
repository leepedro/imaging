#if !defined(ALGORITHMS_H)
#define ALGORITHMS_H

#include <stdexcept>
#if defined(WIN32)
#include <safeint.h>
using namespace msl::utilities;
#else
// Include the safeint.h here.
#endif

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
		{
			if (!::SafeAdd(*itA, *itB, *itC))
				throw std::overflow_error(
				"The result of add operation exceeds the limit of the data type.");
		}
	}

	// C = A - B
	template <typename T_ConstIterator, typename T_Iterator>
	void Subtract(T_ConstIterator itA, T_ConstIterator itA_last, T_ConstIterator itB,
		T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
		{
			if (!::SafeSubtract(*itA, *itB, *itC))
				throw std::overflow_error(
				"The result of subtract operation exceeds the limit of the data type.");
		}
	}

	// C = A * B
	template <typename T_ConstIterator, typename T_Iterator>
	void Multiply(T_ConstIterator itA, T_ConstIterator itA_last, T_ConstIterator itB,
		T_Iterator itC)
	{
		for (; itA != itA_last; ++itA, ++itB, ++itC)
		{
			if (!::SafeMultiply(*itA, *itB, *itC))
				throw std::overflow_error(
				"The result of multiply operation exceeds the limit of the data type.");
		}
	}

	// A++
	template <typename T_Iterator>
	void Increment(T_Iterator it, T_Iterator itLast)
	{
		for (; it != itLast; ++it)
		{
			if (!::SafeAdd(*it, 1, *it))
				throw std::overflow_error(
				"The result of add operation exceeds the limit of the data type.");
		}
	}
}

#endif
