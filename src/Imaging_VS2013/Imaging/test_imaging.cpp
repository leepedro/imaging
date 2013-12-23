#include <iostream>

#include "image.h"

template <typename T>
void TestPoint2D_imp(void)
{
	std::cout << "Testing constructors of Point2D<" << typeid(T).name() << ">." << std::endl;

	// (default) Point2D(void)
	Imaging::Point2D<T> pt1;			// NON-ZERO!
	pt1.x = 1, pt1.y = 2;

	// (default) Point2D(const Point2D<T> &)
	Imaging::Point2D<T> pt2 = pt1;

	Imaging::Point2D<T> pt3;
	// (default) Point2D &operator=(const Point2D<T> &)
	pt3 = pt1;

	// Point2D(const Array<T, N> &)
	Imaging::Array<T, 2> array1{ 5, 6 };
	Imaging::Point2D<T> pt4(array1);
	Imaging::Point2D<T> pt5 = array1;

	// Point2D<T>(T, T) though uniform initialization.
	Imaging::Point2D<T> pt6({ static_cast<T>(5), static_cast<T>(6) });
	Imaging::Point2D<T> pt7 = { 7, 8 };
	Imaging::Point2D<T> pt8{ 9, 10 };
	Imaging::Point2D<T> pt9(11, 12);

	Imaging::Point2D<T> pt10;
	// Point2D(const Array<T, 2> &) + (default) Point2D &operator=(const Point2D<T> &)
	pt10 = array1;

	// The operators of Array<T, N> work OUTSIDE of the namespace. Great!
	// Note: Using overloaded operators of Array<T> requires a ctor with Array<T>.
	std::cout << "Testing with the operators of Array<" << typeid(T).name() << ", 2>." <<
		std::endl;

	Imaging::Point2D<int> ptInt = { 1, 2 };
	Imaging::Point2D<T> pt11 = pt1 + ptInt;	// {2, 4}
	Imaging::Point2D<T> pt12 = pt1 - ptInt;	// {0, 0}
	Imaging::Point2D<T> pt13 = pt1 * ptInt;	// {1, 4}

	Imaging::Point2D<T> pt14(1, 2), pt15(1, 2), pt16(1, 2);
	pt14 += ptInt;	// {2, 4}
	pt15 -= ptInt;	// {0, 0}
	pt16 *= ptInt;	// {1, 4}

	Imaging::Point2D<T> pt17 = pt1 + static_cast<int>(1);	// {2, 3}
	Imaging::Point2D<T> pt18 = pt1 - static_cast<int>(1);	// {0, 1}
	Imaging::Point2D<T> pt19 = pt1 * static_cast<int>(1);	// {1, 2}

	Imaging::Point2D<T> pt20(1, 2), pt21(1, 2), pt22(1, 2);
	pt20 += static_cast<int>(1);	// {2, 3}
	pt21 -= static_cast<int>(1);	// {0, 1}
	pt22 *= static_cast<int>(1);	// {1, 2}

	Imaging::Point2D<T> pt23(1, 2), pt24(1, 2), pt25(1, 2), pt26(1, 2);
	++pt23;	// {2, 3}
	pt24++;	// {2, 3}
	--pt25;	// {0, 1}
	pt26--;	// {0, 1}

	std::cout << "Completed testing Poinr2D<" << typeid(T).name() << ">." << std::endl;
}

void TestPoint2D(void)
{
	TestPoint2D_imp<int>();
	TestPoint2D_imp<unsigned int>();
	TestPoint2D_imp<long long>();
	TestPoint2D_imp<unsigned long long>();
	TestPoint2D_imp<float>();
	TestPoint2D_imp<double>();
}

void TestCoordinates(void)
{
	TestPoint2D();
}

template <typename T>
void TestImage_imp(void)
{
	using namespace Imaging;

	// (default) ImageFrame(void)
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