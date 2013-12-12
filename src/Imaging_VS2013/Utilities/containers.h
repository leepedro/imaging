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
	*/
	template <typename T, ::size_t N>
	class Array
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Overloaded operators.
		Array<T, N> operator+(const Array<T, N> &rhs) const;
		Array<T, N> operator-(const Array<T, N> &rhs) const;
		Array<T, N> operator*(const Array<T, N> &rhs) const;
		void operator+=(const Array<T, N> &rhs);
		void operator-=(const Array<T, N> &rhs);
		void operator*=(const Array<T, N> &rhs);
		void operator+=(T rhs);
		void operator-=(T rhs);
		void operator*=(T rhs);
		Array<T, N> &operator++(void);	// ++A
		Array<T, N> operator++(int);	// A++
		//typename std::enable_if<std::is_integral<T>::value, void>::type operator++(void);
		//typename std::enable_if<std::is_integral<T>::value, void>::type operator--(void);

		////////////////////////////////////////////////////////////////////////////////////
		// Members.
		std::array<T, N> data;
	};


}

#include "containers_inl.h"

#endif
