#if !defined(IMAGE_INL_H)
#define IMAGE_INL_H

namespace Imaging
{
	template <typename T>
	ImageFrame<T>::ImageFrame(void) : data(data_), depth(depth_), size(size_),
		depth_(0), size_(Size2D<SizeType>({ 0, 0 })) {}

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
		ImageFrame<T>::EvaluateSize(src.data.size(), src.size.width, src.size.height, src.depth);
		this->data_ = src.data;
		this->depth_ = src.depth;
		this->size_ = src.size;
	}

	/*
	Many sources say a move constructor, which calls this operator, must guarante not to
	throw an exception.
	Visual Studio 2013 does not support noexcept specifier at this moment.
	If no exception guarantee is required later, remove EvaluateSize().
	*/
	template <typename T>
	ImageFrame<T> &ImageFrame<T>::operator=(ImageFrame<T> &&src)
	{
		ImageFrame<T>::EvaluateSize(src.data.size(), src.size.width, src.size.height, src.depth);
		this->data_ = std::move(src.data_);
		this->depth_ = src.depth;
		this->size_ = src.size;
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(const Size2D<SizeType> &sz, SizeType d) : ImageFrame<T>()
	{
		this->Reset(sz, d);
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(SizeType width, SizeType height, SizeType d) : ImageFrame<T>()
	{
		this->Reset(Size2D<SizeType>(width, height), d);
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(const std::vector<T> &srcData, const Size2D<SizeType> &sz,
		SizeType d) : ImageFrame<T>()
	{
		ImageFrame<T>::EvaluateSize(srcData.size(), sz.width, sz.height, d);
		this->data_ = srcDdata;
		this->depth_ = d;
		this->size_ = sz;
	}

	template <typename T>
	ImageFrame<T>::ImageFrame(std::vector<T> &&srcData, const Size2D<SizeType> &sz,
		SizeType d) : ImageFrame<T>()
	{
		ImageFrame<T>::EvaluateSize(srcData.size(), sz.width, sz.height, d);
		this->data_ = std::move(srcData);
		this->depth_ = d;
		this->size_ = sz;
	}

	/*
	Since this function does not actually use any class member, it is declared as a static
	function.
	It is declared as protected function for now because it is not expected to be used by
	any client.
	*/
	template <typename T>
	void ImageFrame<T>::EvaluateSize(SizeType length, SizeType w, SizeType h, SizeType d)
	{
		if (length != w * h * d)
		{
			std::ostringstream errMsg;
			errMsg << "The size of source image (" << w << " x " << h << " x " << d <<
				") is not matched with the size of its source data (" << length << ").";
			throw std::runtime_error(errMsg.str());
		}
	}

	template <typename T>
	void ImageFrame<T>::Clear()
	{
		this->data_.clear();
		this->depth_ = 0;
		this->size_.width = 0;
		this->size_.height = 0;
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


		
}

#endif
