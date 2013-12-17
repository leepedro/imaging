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
	RectWith2Corner: window with two corners;
	arithmetic point1({x, y}), arithmetic point2({x, y})
	RectWith1Corner: window with one corner and extension;
	integral origin({x, y}), unsigned integral size({w, h})
	RectWithCenter: window with a center and extension;
	arithmetic center({x, y}), arithmetic half_size({w, h}); 
	*/
	template <typename T>
	class RectWith2Corner
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectWith2Corner<T> &rhs) const;
		bool operator!=(const RectWith2Corner<T> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> point1, point2;
	};

	template <typename T, typename U>
	class RectWith1Corner
	{
		static_assert(std::is_integral<T>::value && std::is_integral<U>::value &&
		std::is_unsigned<U>::value,
		"origin must be integral data type and size must be unsigned integral type.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> origin;
		Size2D<U> size;
	};

	template <typename T, typename U>
	class RectWithCenter
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> center;
		Size2D<U> extension;
	};
}

#include "coordinates_inl.h"

#endif
