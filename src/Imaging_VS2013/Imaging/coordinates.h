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
		Point2D(const Array<T, 2> &srcData);
		//Point2D &operator=(const Array<T, 2> &srcData);	// optional, no need

		T &x, &y;
	};
}

#include "coordinates_inl.h"

#endif
