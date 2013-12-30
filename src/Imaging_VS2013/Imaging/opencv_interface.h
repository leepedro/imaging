#if !defined(OPENCV_INTERFACE_H)
#define OPENCV_INTERFACE_H

#include "opencv2/opencv.hpp"

namespace Imaging
{
	template <typename T>
	int GetOpenCvType(std::size_t d = 1)
	{
		static_assert(std::is_arithmetic<T>::value,
			"Only arithmetic data types are supported for this function template.");		
		static_assert(!std::is_same<T, unsigned int>::value,
			"unsigned int is not supported by OpenCV.");
		static_assert(!std::is_same<T, long long>::value,
			"long long is not supported by OpenCV.");
		static_assert(!std::is_same<T, unsigned long long>::value,
			"unsigned long long is not supported by OpenCV.");
	}

	template <>
	int GetOpenCvType<char>(std::size_t d)
	{
		return CV_MAKETYPE(CV_8S, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<signed char>(std::size_t d)
	{
		return CV_MAKETYPE(CV_8S, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<unsigned char>(std::size_t d)
	{
		return CV_MAKETYPE(CV_8U, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<short>(std::size_t d)
	{
		return CV_MAKETYPE(CV_16S, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<unsigned short>(std::size_t d)
	{
		return CV_MAKETYPE(CV_16U, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<int>(std::size_t d)
	{
		return CV_MAKETYPE(CV_32S, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<float>(std::size_t d)
	{
		return CV_MAKETYPE(CV_32F, Cast<int>(d));
	}

	template <>
	int GetOpenCvType<double>(std::size_t d)
	{
		return CV_MAKETYPE(CV_64F, Cast<int>(d));
	}

	template <typename T>
	void ResetCvMat(const Size2D<SizeT<T>> &sz, std::size_t d, cv::Mat &dst)
	{
		dst.create(Cast<int>(sz.height), Cast<int>(sz.width), GetOpenCvType<T>(d));
	}

	template <typename T>
	cv::Mat CreateCvMat(const Size2D<SizeT<T>> &sz, std::size_t d)
	{
		return cv::Mat(Cast<int>(sz.height), Cast<int>(sz.width), GetOpenCvType<T>(d));
	}

	template <typename T>
	cv::Mat CreateCvMatShared(ImageFrame<T> &imgSrc)
	{
		auto it = imgSrc.Begin();
		return cv::Mat(Cast<int>(imgSrc.size.height), Cast<int>(imgSrc.size.width),
			GetOpenCvType<T>(imgSrc.depth), &(*it));
	}
}

#endif
