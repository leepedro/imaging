#if !defined(IMAGE_H)
#define IMAGE_H

#include <vector>

#include "coordinates.h"

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Forward declarations.

	template <typename T> class ImageFrame;

	// Forward declarations.
	////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////
	// Template aliases.
	/* Since template alias cannot be forward declared, all template aliases should be
	declared before any class is defined (after forward declarations). */

	template <typename T>
	using SizeT = typename ImageFrame<T>::SizeType;

	//template <typename T>
	//using IteratorT = typename ImageFrame<T>::Iterator;

	//template <typename T>
	//using ConstIteratorT = typename ImageFrame<T>::ConstIterator;

	template <typename T>
	using ROI = typename RectTypeB<SizeT<T>, SizeT<T>>;

	// Template aliases.
	////////////////////////////////////////////////////////////////////////////////////////


	/* Pixel-based bitmap (raster) image.

	This class template stores image data as a std::vector<T> object, so it does NOT need to
	release the memory at the destructor and it cannot have padding bytes.
	The value of image data can be modifed externally by references and iterators of the
	std::vector<T> object.
	The dimension of image data can be changed externally by designated member functions.
	Of course, the member functions of a different object of same class still have full
	access.

	Image pixel values are always stored in the following order.
	channel -> pixel -> line -> frame

	The terms used to describe the dimension of data are following.
	depth: number of channels per pixel
	width: number of pixels per line
	height: number of lines per frame
	length: number of frames per block (not used in this class)
	c: position of a channel at given pixel; [0 ~ depth)
	x: position of a pixel at given line; [0 ~ width)
	y: position of a line at given frame; [0 ~ height)
	*/
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
		T At(const Point2D<SizeType> &pt) const;
		ConstIterator Cbegin(const Point2D<SizeType> &pt = { 0, 0 }) const;
		Iterator Begin(const Point2D<SizeType> &pt = { 0, 0 });

		const std::vector<T> &data = this->data_;
		const SizeType &depth = this->depth_;
		const Size2D<SizeType> &size = this->size_;

		////////////////////////////////////////////////////////////////////////////////////
		// Methods.
		void Clear(void);

		/* Copies the image data within the ROI from a source image to an ROI of this image.
		Destination image must already have been allocated.
		NOTE: If destination ROI is the entire image, then call CopyTo() of the source image
		instead of this method. */
		void CopyFrom(const ImageFrame<T> &imgSrc, const ROI<T> &roiSrc,
			const Point2D<SizeType> &orgnDst = { 0, 0 });

		/* Copies image data from an std::vector<T> object.
		Destination image is resized per the size of source data. */
		void CopyFrom(const std::vector<T> &srcData, const Size2D<SizeType> &sz,
			SizeType d = 1);

		/* Copies image data from a raw pointer.
		The source data may have padding bytes.
		Destination image is resized per the size of source data.
		NOTE: Since there is no way to check the dimension of source data, users must ensure
		that the size of source data is correct. */
		void CopyFrom(const T *src, const Size2D<SizeType> &sz, SizeType d,
			std::size_t bytesPerLine);
		void CopyFrom(const T *src, const Size2D<SizeType> &sz, SizeType d = 1);

		/* Creates a seprate ImageFrame<T> object with the image data within the ROI.
		Destination image is resized per the size of source data. */
		ImageFrame<T> CopyTo(const ROI<T> &roiSrc) const;

		/* Moves image data from an std::vector<T>.
		Destination image is resized per the size of source data. */
		void MoveFrom(std::vector<T> &&srcData, const Size2D<SizeType> &sz, SizeType d = 1);

		void Reset(const Size2D<SizeType> &sz, SizeType d = 1, T value = 0);
		// Methods.
		////////////////////////////////////////////////////////////////////////////////////

	protected:
		////////////////////////////////////////////////////////////////////////////////////
		// Accessors.
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


	////////////////////////////////////////////////////////////////////////////////////////
	// Global functions.

	/* Copies image data (with padding bytes) from a raw pointer for given dimension to an
	std::vector<T>.
	Destination is resized per the size of source data.
	NOTE: Since there is no way to check the dimension of source data, users must ensure
	length is a valid value. */
	template <typename T>
	void Copy(const T *src, const Size2D<SizeT<T>> &sz, SizeT<T> d, std::size_t bytesPerLine,
		std::vector<T> &dst);

	// Global functions.
	////////////////////////////////////////////////////////////////////////////////////////
}

#include "image_inl.h"

#endif
