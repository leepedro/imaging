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
}

#include "coordinates_inl.h"

#endif
