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
	Imaging::Point2D<T> pt3({ 3, 4 });	// This calls Point2D<T>(T, T). WHY?
	Imaging::Array<T, 2> array1{ 5, 6 };
	Imaging::Point2D<T> pt4(array1);
	Imaging::Point2D<T> pt5 = array1;
	Imaging::Point2D<T> pt6 = { 11, 12 };	// NOT working.

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

template <typename T>
void TestImage_imp(void)
{
	using namespace Imaging;

	// ImageFrame(void)
	ImageFrame<T> img1;						// 0 x 0 x 0

	// ImageFrame(const Size2D<SizeType> &, SizeType = 1)
	ImageFrame<T> img2({ 16, 8 }, 3);		// 16 x 8 x 3
	ImageFrame<T> img3({ 16, 8 });			// 16 x 8 x 1

	// ImageFrame(const ImageFrame<T> &)
	ImageFrame<T> img4 = img2;				// 16 x 8 x 3

	// ImageFrame(ImageFrame<T> &&)
	ImageFrame<T> imgTemp1({ 16, 8 });			// 0 x 0 x 0
	ImageFrame<T> img5 = std::move(imgTemp1);	// 16 x 8 x 1

	// ImageFrame<T> &operator=(const ImageFrame<T> &)
	ImageFrame<T> img6;
	img6 = img2;							// 16 x 8 x 3

	// ImageFrame<T> &operator=(ImageFrame<T> &&)
	ImageFrame<T> img7;
	ImageFrame<T> imgTemp2({ 16, 8 });		// 0 x 0 x 0
	img7 = imgTemp2;						// 16 x 8 x 1

	// ImageFrame(const std::vector<T> &, const Size2D<SizeType> &, SizeType = 1)
	std::vector<T> v1(128);
	ImageFrame<T> img8(v1, { 16, 8 });
	ImageFrame<T> img9(v1, { 8, 8 }, 2);

	// ImageFrame(std::vector<T> &&, const Size2D<SizeType> &, SizeType = 1)
	ImageFrame<T> img10(std::vector<T>(128), { 16, 8 });
	ImageFrame<T> img11(std::vector<T>(128), { 8, 8 }, 2);

	ROI<unsigned char> roi1;
	ROI<unsigned char> roi2 = { { 0, 0 }, { 64, 32 } };
}

void TestImage(void)
{
	TestImage_imp<char>();
	TestImage_imp<signed char>();
	TestImage_imp<unsigned char>();
	TestImage_imp<short>();
	TestImage_imp<unsigned short>();
	TestImage_imp<int>();
	TestImage_imp<unsigned int>();
	TestImage_imp<long long>();
	TestImage_imp<unsigned long long>();
	TestImage_imp<float>();
	TestImage_imp<double>();
}

int main(void)
{
	TestCoordinates();
	TestImage();
}