#if !defined(COORDINATES_H)
#define COORDINATES_H

#include "utilities/containers.h"

namespace Imaging
{
	template <typename T>
	class Point2D : public Array<T, 2>
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Default constructors.
		Point2D(void);
		Point2D(const Point2D<T> &src);
		Point2D &operator=(const Point2D<T> &src);

		////////////////////////////////////////////////////////////////////////////////////
		// Custom constructors.
		Point2D(T x, T y);
		Point2D(const Array<T, 2> &srcData);
		//Point2D &operator=(const Array<T, 2> &srcData);	// optional, no need

		T &x, &y;
	};

	template <typename T>
	class Size2D : public Array<T, 2>
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Default constructors.
		Size2D(void);
		Size2D(const Size2D<T> &src);
		Size2D &operator=(const Size2D<T> &src);

		////////////////////////////////////////////////////////////////////////////////////
		// Custom constructors.
		Size2D(T width, T height);
		Size2D(const Array<T, 2> &srcData);
		//Size2D &operator=(const Array<T, 2> &srcData);	// optional, no need

		T &width, &height;
	};

	/*
	RectTypeA: a rectangle with two corners; point1<T>({x, y}), point2<T>({x, y})
	RectTypeB: a rectangle with one corner and extension; origin<T>({x, y}), size<U>({w, h})
	RectTypeC: a rectangle with a center and extension; center<T>({x, y}), extension<U>({w, h})
	*/
	template <typename T>
	class RectTypeA
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeA<T> &rhs) const;
		bool operator!=(const RectTypeA<T> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> point1, point2;
	};

	/*
	It does NOT have any user defined ctor or protected/private members, so it can use
	aggregate initialization.
	This class template has only two data members, and they were derived from
	std::array<T, N>, so there is not much benefit by implementing custom ctors.
	*/
	template <typename T>
	class RectTypeB
	{
		static_assert(std::is_arithmetic<T>::value,
		"origin must be integral data type and size must be unsigned integral type.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeB<T> &rhs) const;
		bool operator!=(const RectTypeB<T> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> origin;
		Size2D<T> size;
	};

	template <typename T>
	class RectTypeC
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeC<T> &rhs) const;
		bool operator!=(const RectTypeC<T> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> center;
		Size2D<T> extension;
	};
}

#include "coordinates_inl.h"

#endif
