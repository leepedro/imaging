#if !defined(CONTAINERS_H)
#define CONTAINERS_H

#include <array>
#include <vector>

#include "algorithms.h"

namespace Imaging
{
	/*
	This class template expands the functionality of std::array<T, N> by overloading member
	operators so they can be used outside of the namespace.

	It does NOT have any user defined ctor or protected/private members, so it can use
	aggregate initialization.
	NOTE: Since std::array<T, N> cannot be used with a move ctor,
	there is not much benefit to implement them for its derived classes.
	*/
	template <typename T, std::size_t N>
	class Array
	{
		static_assert(std::is_arithmetic<T>::value,
			"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Overloaded operators.

		// A = B + C
		template <typename U>
		Array<T, N> operator+(const Array<U, N> &rhs) const;

		// A = B - C
		template <typename U>
		Array<T, N> operator-(const Array<U, N> &rhs) const;

		// A = B * C
		template <typename U>
		Array<T, N> operator*(const Array<U, N> &rhs) const;

		// A = B + c
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator+(U rhs) const;

		// A = B - c
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator-(U rhs) const;

		// A = B * c
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator*(U rhs) const;

		// A += B
		template <typename U>
		void operator+=(const Array<U, N> &rhs);

		// A -= B
		template <typename U>
		void operator-=(const Array<U, N> &rhs);

		// A *= B
		template <typename U>
		void operator*=(const Array<U, N> &rhs);

		// A += b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator+=(U rhs);

		// A -= b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator-=(U rhs);

		// A *= b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator*=(U rhs);

		Array<T, N> &operator++(void);	// ++A
		Array<T, N> operator++(int);	// A++
		Array<T, N> &operator--(void);	// --A
		Array<T, N> operator--(int);	// A--

		////////////////////////////////////////////////////////////////////////////////////
		// Members.
		std::array<T, N> data;
	};

	template <typename T>
	std::vector<T> GetRangeVector(std::size_t length);
}

#include "containers_inl.h"

#endif
