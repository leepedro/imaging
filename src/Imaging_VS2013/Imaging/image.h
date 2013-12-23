#if !defined(IMAGE_H)
#define IMAGE_H

#include <vector>

#include "coordinates.h"

namespace Imaging
{
	// Forward declarations.
	template <typename T> class ImageFrame;

	// Template aliases.
	/*
	Since template alias cannot be forward declared, all template aliases should be
	declared before any class is defined.
	*/
	template <typename T>
	using SizeT = typename ImageFrame<T>::SizeType;

	//template <typename T>
	//using IteratorT = typename ImageFrame<T>::Iterator;

	//template <typename T>
	//using ConstIteratorT = typename ImageFrame<T>::ConstIterator;

	template <typename T>
	using ROI = typename RectTypeB<SizeT<T>, SizeT<T>>;

	template <typename T>
	class ImageFrame
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Types and constants.
		typedef typename std::vector<T>::size_type SizeType;
		typedef typename std::vector<T>::const_iterator ConstIterator;
		typedef typename std::vector<T>::iterator Iterator;

		////////////////////////////////////////////////////////////////////////////////////
		// Default constructors.
		ImageFrame(void) = default;
		ImageFrame(const ImageFrame<T> &src);
		ImageFrame(ImageFrame<T> &&src);
		ImageFrame<T> &operator=(const ImageFrame<T> &src);
		ImageFrame<T> &operator=(ImageFrame<T> &&src);

		////////////////////////////////////////////////////////////////////////////////////
		// Custom constructors.
		ImageFrame(const Size2D<SizeType> &sz, SizeType d = 1);
		ImageFrame(const std::vector<T> &srcData, const Size2D<SizeType> &sz, SizeType d = 1);
		ImageFrame(std::vector<T> &&srcData, const Size2D<SizeType> &sz, SizeType d = 1);

		////////////////////////////////////////////////////////////////////////////////////
		// Accessors.
		const std::vector<T> &data = this->data_;
		const SizeType &depth = this->depth_;
		const Size2D<SizeType> &size = this->size_;

		////////////////////////////////////////////////////////////////////////////////////
		// Methods.
		void Clear(void);
		void CopyFrom(const ImageFrame<T> &imgSrc, const ROI<T> &roiSrc,
			const Point2D<SizeType> &orgnDst);
		void Reset(const Size2D<SizeType> &sz, SizeType d);

	protected:
		////////////////////////////////////////////////////////////////////////////////////
		// Accessors.
		ConstIterator GetCIterator(const Point2D<SizeType> &pt) const;
		Iterator GetIterator(const Point2D<SizeType> &pt);
		SizeType GetOffset(const Point2D<SizeType> &pt) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Methods.
		void EvalDepth(SizeType depth) const;
		void EvalPosition(const Point2D<SizeType> &pt) const;
		void EvalRoi(const ROI<T> &roi) const;
		void EvalRoi(const Point2D<SizeType> &orgn, const Size2D<SizeType> &sz) const;
		static void EvalSize(SizeType length, SizeType w, SizeType h, SizeType d);

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		std::vector<T> data_;
		SizeType depth_ = 0;
		Size2D<SizeType> size_ = Size2D<SizeType>(0, 0);
	};
}

#include "image_inl.h"

#endif
