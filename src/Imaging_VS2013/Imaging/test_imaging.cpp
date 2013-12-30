#include <iostream>

#include "image.h"
#include "opencv_interface.h"

//#include "opencv2/opencv.hpp"

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

	bool b1 = pt23 == pt24;		// true
	bool b2 = pt25 != pt26;		// false

	// Point2D(const Point2D<U> &)
	Imaging::Point2D<T> pt27 = ptInt;

	// Point2D(const Point2D<U> &) + (default) Point2D &operator=(const Point2D<T> &)
	ptInt = pt27;

	std::cout << "Completed testing Poinr2D<" << typeid(T).name() << ">." << std::endl;

	Imaging::ROI<T> roi1;
	Imaging::ROI<T> roi2 = { { 0, 0 }, { 64, 32 } };
	Imaging::ROI<T> roi3{ { 0, 0 }, { 64, 32 } };
}

void TestPoint2D(void)
{
	TestPoint2D_imp<int>();
	TestPoint2D_imp<unsigned int>();
	TestPoint2D_imp<long long>();
	TestPoint2D_imp<unsigned long long>();
	TestPoint2D_imp<float>();
	TestPoint2D_imp<double>();

	Imaging::Point2D<double> ptD(2.5, 3.1);
	Imaging::Point2D<long long> ptL = Imaging::RoundAs<long long>(ptD);
}

void TestCoordinates(void)
{
	TestPoint2D();
}

template <typename T>
void TestImage_imp(void)
{
	using namespace Imaging;

	std::cout << "Testing constructors of ImageFrame<" << typeid(T).name() << ">." << std::endl;

	// (default) ImageFrame(void)
	ImageFrame<T> img1;						// 0 x 0 x 0
	std::cout << img1.size.width << " X " << img1.size.height << " X " << img1.depth << std::endl;

	// ImageFrame(const Size2D<SizeType> &, SizeType = 1)
	ImageFrame<T> img2({ 16, 8 }, 3);		// 16 x 8 x 3
	std::cout << img2.size.width << " X " << img2.size.height << " X " << img2.depth << std::endl;
	ImageFrame<T> img3({ 16, 8 });			// 16 x 8 x 1
	std::cout << img3.size.width << " X " << img3.size.height << " X " << img3.depth << std::endl;

	// ImageFrame(const ImageFrame<T> &)
	ImageFrame<T> img4 = img2;				// 16 x 8 x 3
	std::cout << img4.size.width << " X " << img4.size.height << " X " << img4.depth << std::endl;

	// ImageFrame(ImageFrame<T> &&)
	ImageFrame<T> imgTemp1({ 16, 8 });			// 0 x 0 x 0
	ImageFrame<T> img5 = std::move(imgTemp1);	// 16 x 8 x 1
	std::cout << imgTemp1.size.width << " X " << imgTemp1.size.height << " X " << imgTemp1.depth << std::endl;
	std::cout << img5.size.width << " X " << img5.size.height << " X " << img5.depth << std::endl;

	// ImageFrame<T> &operator=(const ImageFrame<T> &)
	ImageFrame<T> img6;
	img6 = img2;							// 16 x 8 x 3
	std::cout << img6.size.width << " X " << img6.size.height << " X " << img6.depth << std::endl;

	// ImageFrame<T> &operator=(ImageFrame<T> &&)
	ImageFrame<T> imgTemp2({ 16, 8 });		// 0 x 0 x 0
	ImageFrame<T> img7;
	img7 = std::move(imgTemp2);				// 16 x 8 x 1
	std::cout << imgTemp2.size.width << " X " << imgTemp2.size.height << " X " << imgTemp2.depth << std::endl;
	std::cout << img7.size.width << " X " << img7.size.height << " X " << img7.depth << std::endl;

	// ImageFrame(const std::vector<T> &, const Size2D<SizeType> &, SizeType = 1)
	std::vector<T> v1 = GetRangeVector<T>(128);
	ImageFrame<T> img8(v1, { 16, 8 });		// 16 x 8 x 1
	std::cout << img8.size.width << " X " << img8.size.height << " X " << img8.depth << std::endl;
	ImageFrame<T> img9(v1, { 8, 8 }, 2);	// 8 x 8 x 2
	std::cout << img9.size.width << " X " << img9.size.height << " X " << img9.depth << std::endl;

	// ImageFrame(std::vector<T> &&, const Size2D<SizeType> &, SizeType = 1)
	ImageFrame<T> img10(std::vector<T>(128), { 16, 8 });	// 16 x 8 x 1
	std::cout << img10.size.width << " X " << img10.size.height << " X " << img10.depth << std::endl;
	ImageFrame<T> img11(std::vector<T>(128), { 8, 8 }, 2);	// 8 x 8 x 2
	std::cout << img11.size.width << " X " << img11.size.height << " X " << img11.depth << std::endl;

	std::cout << "Testing methods of ImageFrame<" << typeid(T).name() << ">." << std::endl;

	// Clear()
	ImageFrame<T> img12({ 16, 8 });
	img12.Clear();							// 0 x 0 x 0
	std::cout << img12.size.width << " X " << img12.size.height << " X " << img12.depth << std::endl;

	// void CopyFrom(const ImageFrame<T> &, const ROI<T> &, const Point2D<SizeType> & = {0, 0})
	ImageFrame<T> img13({ 16, 8 });
	img13.CopyFrom(img8, { { 0, 0 }, { 8, 8 } }, Point2D<T>(1, 0));
	std::cout << static_cast<double>(img13.At({ 1, 0 })) << std::endl;		// 0
	std::cout << static_cast<double>(img13.At({ 2, 0 })) << std::endl;		// 1
	img13.CopyFrom(img8, { { 0, 0 }, { 8, 8 } }, { 8, 0 });
	std::cout << static_cast<double>(img13.At({ 8, 0 })) << std::endl;		// 0
	std::cout << static_cast<double>(img13.At({ 9, 0 })) << std::endl;		// 1
	img13.CopyFrom(img8, { { 0, 0 }, { 8, 8 } });
	std::cout << static_cast<double>(img13.At({ 0, 0 })) << std::endl;		// 0
	std::cout << static_cast<double>(img13.At({ 1, 0 })) << std::endl;		// 1

	// void CopyFrom(const std::vector<T> &, const Size2D<SizeType> &, SizeType = 1)
	img13.CopyFrom(v1, { 16, 8 }, 1);
	std::cout << static_cast<double>(img13.At({ 1, 0 })) << std::endl;		// 1
	img13.CopyFrom(v1, { 16, 8 });
	std::cout << static_cast<double>(img13.At({ 1, 0 })) << std::endl;		// 1

	// void CopyTo(const ROI<T> &, ImageFrame<T> &) const
	ImageFrame<T> img14 = img13.CopyTo({ { 0, 0 }, { 8, 8 } });		// 8 x 8 x 1
	std::cout << img14.size.width << " X " << img14.size.height << " X " << img14.depth << std::endl;

	// void MoveFrom(std::vector<T> &&, const Size2D<SizeType> &, SizeType = 1)
	ImageFrame<T> img15;
	img15.MoveFrom(GetRangeVector<T>(128), { 16, 8 }, 1);
	std::cout << static_cast<double>(img15.At({ 1, 0 })) << std::endl;		// 1
	img15.MoveFrom(GetRangeVector<T>(128), { 16, 8 });
	std::cout << static_cast<double>(img15.At({ 2, 0 })) << std::endl;		// 2

	// void Reset(const Size2D<SizeType> &, SizeType = 1)
	img15.Reset({ 8, 8 }, 2);
	std::cout << img15.size.width << " X " << img15.size.height << " X " << img15.depth << std::endl;
	img15.Reset({ 16, 8 });
	std::cout << img15.size.width << " X " << img15.size.height << " X " << img15.depth << std::endl;

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

void TestOpenCvInterface(void)
{
	using namespace Imaging;

	int t1 = GetOpenCvType<char>();
	int t2 = GetOpenCvType<unsigned char>();
	int t3 = GetOpenCvType<unsigned char>(1);
	int t4 = GetOpenCvType<unsigned char>(3);
	int t5 = GetOpenCvType<unsigned char>(4);
	int t6 = GetOpenCvType<short>();
	int t7 = GetOpenCvType<unsigned short>();
	int t8 = GetOpenCvType<int>();
	int t9 = GetOpenCvType<float>();
	int t10 = GetOpenCvType<double>();


}

void TestImageProcessing(void)
{
	using namespace Imaging;

	// Load an image from a file.
	cv::Mat cvSrc1 = cv::imread(std::string("Lenna.png"), CV_LOAD_IMAGE_COLOR);
	cv::namedWindow(std::string("Source 1"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Source 1"), cvSrc1);
	cv::waitKey(0);

	// Copy image data from cv::Mat object to ImageFrame<T>.
	ImageFrame<unsigned char> img1;
	img1.CopyFrom(cvSrc1.ptr(), { Cast<std::size_t>(cvSrc1.cols),
		Cast<std::size_t>(cvSrc1.rows) }, cvSrc1.channels());
	std::cout << "Test value = " << img1.At({ img1.size.width - 1, 100 }) << std::endl;

	// Copy an ROI to a separate ImageFrame<T>.
	ROI<unsigned char> roiSrc1 = { { 100, 100 }, img1.size - 100 };
	ImageFrame<unsigned char> img2 = img1.CopyTo(roiSrc1);
	std::cout << "Test value = " << img2.At({ img2.size.width - 1, 0 }) << std::endl;

	// Copy image data from ImageFrame<T> to cv::Mat.
	cv::Mat cvDst1;
	ResetCvMat<unsigned char>(img2.size, img2.depth, cvDst1);
	cv::Mat cvDst2 = CreateCvMat<unsigned char>(img2.size, img2.depth);
#if defined(_MSC_VER)
	std::copy_n(img2.data.cbegin(), img2.data.size(),
		stdext::checked_array_iterator<unsigned char *>(cvDst1.ptr(), img2.data.size()));
#else
	std::copy_n(img2.data.cbegin(), img2.data.size(), cvDst1.ptr());
#endif
	cv::namedWindow(std::string("Copied memory"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Copied memory"), cvDst1);
	cv::waitKey(0);

	// Shared allocation of cv::Mat object from an ImageFrame<T>.
	cv::Mat cvDstShared = CreateCvMatShared(img1);
	cv::namedWindow(std::string("Shared memory"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Shared memory"), cvDstShared);
	cv::waitKey(0);

	// Resize the image.
	cv::Mat cvZm;
	cv::Mat cvDstShared2 = CreateCvMatShared(img2);
	cv::resize(cvDstShared2, cvZm, { 0, 0 }, 1.5, 1.5, cv::INTER_CUBIC);
	cv::namedWindow(std::string("Resized"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Resized"), cvZm);
	cv::waitKey(0);
}

int main(void)
{
	TestCoordinates();
	TestImage();
	TestOpenCvInterface();
	TestImageProcessing();
}