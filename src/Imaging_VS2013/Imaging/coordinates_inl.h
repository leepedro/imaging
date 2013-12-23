#if !defined(COORDINATES_INL_H)
#define COORDINATES_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////
	// Point2D<T>

	template <typename T>
	Point2D<T>::Point2D(T x, T y) : Point2D<T>()
	{
		this->x = x;
		this->y = y;
	}

	template <typename T>
	Point2D<T>::Point2D(const Array<T, 2> &srcData) : Array<T, 2>(srcData) {}

	// Point2D<T>
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	// Size2D<T>

	template <typename T>
	Size2D<T>::Size2D(T width, T height) : Size2D<T>()
	{
		this->width = width;
		this->height = height;
	}

	template <typename T>
	Size2D<T>::Size2D(const Array<T, 2> &srcData) : Array<T, 2>(srcData) {}

	// Size2D<T>
	////////////////////////////////////////////////////////////////////////////////////
}

#endif
