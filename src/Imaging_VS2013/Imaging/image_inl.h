#if !defined(IMAGE_INL_H)
#define IMAGE_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////
	// ImageFrame<T>

	////////////////////////////////////////////////////////////////////////////////////
	// Constructors.

	template <typename T>
	ImageFrame<T>::ImageFrame(const ImageFrame<T> &src) : ImageFrame<T>()
	{
		*this = src;
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(ImageFrame<T> &&src) : ImageFrame<T>()
	{
		*this = std::move(src);
	}

	template <typename T>
	ImageFrame<T> &ImageFrame<T>::operator=(const ImageFrame<T> &src)
	{
		ImageFrame<T>::EvalSize(src.data.size(), src.size.width, src.size.height, src.depth);
		this->data_ = src.data;
		this->depth_ = src.depth;
		this->size_ = src.size;
		return *this;
	}

	/*
	Many sources say a move constructor, which calls this operator, must guarante not to
	throw an exception.
	Visual Studio 2013 does not support noexcept specifier at this moment.
	If no exception guarantee is required later, remove EvalSize().
	*/
	template <typename T>
	ImageFrame<T> &ImageFrame<T>::operator=(ImageFrame<T> &&src)
	{
		ImageFrame<T>::EvalSize(src.data.size(), src.size.width, src.size.height, src.depth);
		this->data_ = std::move(src.data_);
		this->depth_ = src.depth;
		this->size_ = src.size;
		src.depth_ = 0;
		src.size_ = { 0, 0 };
		return *this;
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(const Size2D<SizeType> &sz, SizeType d) : ImageFrame<T>()
	{
		this->Reset(sz, d);
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(const std::vector<T> &srcData, const Size2D<SizeType> &sz,
		SizeType d) : ImageFrame<T>()
	{
		this->CopyFrom(srcData, sz, d);
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(std::vector<T> &&srcData, const Size2D<SizeType> &sz,
		SizeType d) : ImageFrame<T>()
	{
		this->MoveFrom(std::move(srcData), sz, d);
	}

	// Constructors.
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	// Accessors.

	template <typename T>
	T ImageFrame<T>::At(const Point2D<T> &pt) const
	{
		return *this->GetCIterator(pt);
	}

	template <typename T>
	typename ImageFrame<T>::ConstIterator ImageFrame<T>::GetCIterator(const Point2D<SizeType> &pt) const
	{
		this->EvalPosition(pt);
		return this->data.cbegin() + this->GetOffset(pt);
	}

	template <typename T>
	typename ImageFrame<T>::Iterator ImageFrame<T>::GetIterator(const Point2D<SizeType> &pt)
	{
		this->EvalPosition(pt);
		return this->data_.begin() + this->GetOffset(pt);
	}

	template <typename T>
	typename ImageFrame<T>::SizeType ImageFrame<T>::GetOffset(const Point2D<SizeType> &pt) const
	{
		return this->depth * this->size.width * pt.y + this->depth * pt.x;
	}

	// Accessors.
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	// Methods.

	template <typename T>
	void ImageFrame<T>::Clear()
	{
		this->data_.clear();
		this->depth_ = 0;
		this->size_.width = 0;
		this->size_.height = 0;
	}

	/* Throws an exception if destination image is not allocated for source ROI. */
	template <typename T>
	void ImageFrame<T>::CopyFrom(const ImageFrame<T> &imgSrc, const ROI<T> &roiSrc,
		const Point2D<SizeType> &orgnDst)
	{
		// Check ROI.
		this->EvalDepth(imgSrc.depth);
		imgSrc.EvalRoi(roiSrc);
		this->EvalRoi(orgnDst, roiSrc.size);

		// Copy line by line.
		auto itSrc = imgSrc.GetCIterator(roiSrc.origin);
		auto itDst = this->GetIterator(orgnDst);
		CopyLines(itSrc, imgSrc.size.width * imgSrc.depth, itDst,
			this->size.width * this->depth, roiSrc.size.width * imgSrc.depth,
			roiSrc.size.height);
	}

	template <typename T>
	void ImageFrame<T>::CopyFrom(const std::vector<T> &srcData, const Size2D<SizeType> &sz,
		SizeType d)
	{
		ImageFrame<T>::EvalSize(srcData.size(), sz.width, sz.height, d);
		this->data_ = srcData;
		this->depth_ = d;
		this->size_ = sz;
	}

	template <typename T>
	void ImageFrame<T>::CopyFrom(const T *src, const Size2D<SizeType> &sz, SizeType d,
		std::size_t bytesPerLine)
	{
		// Copy image data into an std::vector<T> object after taking off padding bytes.
		std::vector<T> temp;
		Copy(src, sz, d, bytesPerLine, temp);
		this->data_ = std::move(temp);
		this->size_ = sz;
		this->depth_ = d;
	}

	template <typename T>
	void ImageFrame<T>::CopyTo(const ROI<T> &roiSrc, ImageFrame<T> &imgDst) const
	{
		// Check ROI.
		this->EvalRoi(roiSrc);

		imgDst.Reset(roiSrc.size, this->depth);

		// Copy line by line.
		auto itSrc = this->GetCIterator(roiSrc.origin);
		auto itDst = imgDst.GetIterator();
		CopyLines(itSrc, this->size.width * this->depth, itDst,
			imgDst.size.width * imgDst.depth, roiSrc.size.width, roiSrc.size.height);
	}

	template <typename T>
	void ImageFrame<T>::MoveFrom(std::vector<T> &&srcData, const Size2D<SizeType> &sz,
		SizeType d)
	{
		ImageFrame<T>::EvalSize(srcData.size(), sz.width, sz.height, d);
		this->data_ = std::move(srcData);
		this->depth_ = d;
		this->size_ = sz;
	}

	template <typename T>
	void ImageFrame<T>::EvalDepth(SizeType depth) const
	{
		if (this->depth != depth)
		{
			std::ostringstream errMsg;
			errMsg << "The depth of this image frame (=" << this->depth <<
				") is not matched to " << depth << ".";
			throw std::out_of_range(errMsg.str());
		}
	}

	template <typename T>
	void ImageFrame<T>::EvalPosition(const Point2D<SizeType> &pt) const
	{
		this->EvalRoi(pt, { 1, 1 });
	}

	template <typename T>
	void ImageFrame<T>::EvalRoi(const ROI<T> &roi) const
	{
		this->EvalRoi(roi.origin, roi.size);
	}

	template <typename T>
	void ImageFrame<T>::EvalRoi(const Point2D<SizeType> &orgn, const Size2D<SizeType> &sz) const
	{
		Point2D<SizeType> ptEnd = orgn + sz;	// excluding point
		if (orgn.x < 0 || orgn.y < 0 || ptEnd.x > this->size.width ||
			ptEnd.y > this->size.height)
		{
			std::ostringstream errMsg;
			errMsg << "[" << orgn.x << ", " << orgn.y << "] ~ (" << ptEnd.x <<
				", " << ptEnd.y << ") is out of range.";
			throw std::out_of_range(errMsg.str());
		}
	}

	/*
	Since this function does not actually use any class member, it is declared as a static
	function.
	It is declared as protected function for now because it is not expected to be used by
	any client.
	*/
	template <typename T>
	void ImageFrame<T>::EvalSize(SizeType length, SizeType w, SizeType h, SizeType d)
	{
		if (length != w * h * d)
		{
			std::ostringstream errMsg;
			errMsg << "The size of source image (" << w << " x " << h << " x " << d <<
				") is not matched with the size of its source data (" << length << ").";
			throw std::runtime_error(errMsg.str());
		}
	}

	/*
	Resizes the std::vector<T> object with zero value but does it only if necessary.
	If size is changed while the total number of elements are the same (reshaping),
	it does NOT run std::vector<T>::resize().
	*/
	template <typename T>
	void ImageFrame<T>::Reset(const Size2D<SizeType> &sz, SizeType d)
	{
		SizeType nElem = sz.width * sz.height * d;
		if (this->data.size() != nElem)
			this->data_.resize(nElem, 0);
		this->depth_ = d;
		this->size_ = sz;
	}

	// Methods.
	////////////////////////////////////////////////////////////////////////////////////

	// ImageFrame<T>
	////////////////////////////////////////////////////////////////////////////////////


	template <typename T>
	void Copy(const T *src, const Size2D<SizeT<T>> &sz, SizeT<T> d, std::size_t bytesPerLine,
		std::vector<T> &dst)
	{
		std::size_t nElemPerLine = d * sz.width;
		std::size_t nElem = nElemPerLine * sz.height;
		if (bytesPerLine == nElemPerLine * sizeof(T))	// No padding bytes
			Copy(src, nElem, dst);
		else if (bytesPerLine > nElemPerLine * sizeof(T))	// padding bytes
		{
			// Resize destination for given dimension.
			if (dst.size() != nElem)
				dst.resize(nElem);

			// Copy line by line.
			// Cast source data as char to change lines according to the bytes/line.
			// Then, cast it back as given type to copy element by element.
			auto itDst = dst.begin();
			const char *itSrc = reinterpret_cast<const char *>(src);
			for (auto H = 0; H != sz.height; ++H, itSrc += bytesPerLine, itDst += nElemPerLine)
				std::copy_n(reinterpret_cast<const T *>(itSrc), nElemPerLine, itDst);
		}
		else
			throw std::invalid_argument(
			"The number of bytes per line must be equal or greater than the number of "
			"effective bytes per line.");
	}

}

#endif
