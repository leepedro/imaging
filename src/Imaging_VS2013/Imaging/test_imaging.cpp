#include <iostream>

#include "image.h"

template <typename T>
void TestPoint2D(void)
{
	// Point2D(void)
	Imaging::Point2D<T> pt1;
	pt1.x = 1, pt1.y = 2;

	// Point2D(const Point2D<T> &)
	Imaging::Point2D<T> pt2 = pt1;

	// Point2D &operator=(const Point2D<T> &)
	pt1.x = 10;
	pt2 = pt1;

	// Point2D(const Array<T, N> &)
	// This works because Array<T, N> can take aggregate initialization.
	Imaging::Point2D<T> pt3({ 3, 4 });
	Imaging::Array<T, 2> array1{ 5, 6 };
	Imaging::Point2D<T> pt4(array1);
	Imaging::Point2D<T> pt5 = array1;

	//Imaging::Point2D<T> pt6 = { 11, 12 };	// NOT working.

	// Point2D &operator=(const Array<T, 2> &) or
	// Point2D(const Array<T, N> &) + Point2D &operator=(const Point2D<T> &)
	pt5 = array1;

	// The operators of Array<T, N> work OUTSIDE of the namespace. Great!
	// Note: Using overloaded operators of Array<T> requires a ctor with Array<T>.

	// Array<T, N> operator+(const Array<U, N> &) const +
	// Point2D(const Array<T, 2> &) +
	// Point2D &operator=(const Point2D<T> &)
	pt5 = pt1 + pt1;
}

void TestCoordinates(void)
{
	TestPoint2D<int>();
	TestPoint2D<unsigned int>();
	TestPoint2D<long long>();
	TestPoint2D<unsigned long long>();
	TestPoint2D<float>();
	TestPoint2D<double>();
}

void TestImage(void)
{
	using namespace Imaging;
	ImageFrame<unsigned char> img1;
	ImageFrame<unsigned char> img2(Size2D<SizeType<unsigned char>>({ 16, 8 }), 1);
	ImageFrame<unsigned char> img3(16, 8, 1);

	ImageFrame<unsigned char> img4(GetRangeVector<unsigned char>(300),
		Size2D<SizeType<unsigned char>>({ 30, 10 }));

	TestType<unsigned char> test1;
	//ROI<unsigned char> roi1;
}

int main(void)
{
	TestCoordinates();
	TestImage();
}