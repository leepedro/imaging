#if !defined(CONTAINERS_H)
#define CONTAINERS_H

#include <array>

#include "algorithms.h"

namespace Imaging
{
	/*
	This class template expands the functionality of std::array<T, N> by overloading member
	operators so they can be used outside of the namespace.

	It does NOT have any user defined ctor or protected/private members, so it can use
	aggregate initialization.
	NOTE: std::array<T, N> cannot be used with std::initialization_list<T>.
	*/
	template <typename T, ::size_t N>
	class Array
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Overloaded operators.
		Array<T, N> operator+(const Array<T, N> &rhs) const;	// A = B + C
		Array<T, N> operator-(const Array<T, N> &rhs) const;	// A = B - C
		Array<T, N> operator*(const Array<T, N> &rhs) const;	// A = B * C
		Array<T, N> operator+(T rhs) const;			// A = B + c
		Array<T, N> operator-(T rhs) const;			// A = B - c
		Array<T, N> operator*(T rhs) const;			// A = B * c
		void operator+=(const Array<T, N> &rhs);	// A += B
		void operator-=(const Array<T, N> &rhs);	// A -= B
		void operator*=(const Array<T, N> &rhs);	// A *= B
		void operator+=(T rhs);			// A += b
		void operator-=(T rhs);			// A -= b
		void operator*=(T rhs);			// A *= b
		Array<T, N> &operator++(void);	// ++A
		Array<T, N> operator++(int);	// A++
		Array<T, N> &operator--(void);	// --A
		Array<T, N> operator--(int);	// A--

		////////////////////////////////////////////////////////////////////////////////////
		// Members.
		std::array<T, N> data;
	};
}

#include "containers_inl.h"

#endif
