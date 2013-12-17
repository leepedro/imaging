#if !defined(COORDINATES_INL_H)
#define COORDINATES_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////
	// Point2D<T>

	template <typename T>
	Point2D<T>::Point2D(void) : Array<T, 2>(), x(this->data.at(0)), y(this->data.at(1)) {}

	template <typename T>
	Point2D<T>::Point2D(const Point2D<T> &src) :
		Array<T, 2>(src), x(this->data.at(0)), y(this->data.at(1)) {}

	template <typename T>
	Point2D<T> &Point2D<T>::operator=(const Point2D<T> &src)
	{
		this->data = src.data;
		return *this;
	}

	template <typename T>
	Point2D<T>::Point2D(T x, T y) : Point2D<T>()
	{
		this->x = x;
		this->y = y;
	}

	template <typename T>
	Point2D<T>::Point2D(const Array<T, 2> &srcData) :
		Array<T, 2>(srcData), x(this->data.at(0)), y(this->data.at(1)) {}


	////////////////////////////////////////////////////////////////////////////////////
	// Size2D<T>

	template <typename T>
	Size2D<T>::Size2D(void) :
		Array<T, 2>(), width(this->data.at(0)), height(this->data.at(1)) {}

	template <typename T>
	Size2D<T>::Size2D(const Size2D<T> &src) :
		Array<T, 2>(src), width(this->data.at(0)), height(this->data.at(1)) {}

	template <typename T>
	Size2D<T> &Size2D<T>::operator=(const Size2D<T> &src)
	{
		this->data = src.data;
		return *this;
	}

	template <typename T>
	Size2D<T>::Size2D(T width, T height) : Size2D<T>()
	{
		this->width = width;
		this->height = height;
	}

	template <typename T>
	Size2D<T>::Size2D(const Array<T, 2> &srcData) :
		Array<T, 2>(srcData), width(this->data.at(0)), height(this->data.at(1)) {}
}

#endif
