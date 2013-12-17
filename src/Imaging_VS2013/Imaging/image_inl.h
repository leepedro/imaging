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
		if (src.data.size() == src.size.width * src.size.height * src.depth)
		{
			this->data_ = src.data;
			this->depth_ = src.depth;
			this->size_ = src.size;
		}
		else
		{
			std::ostringstream errMsg;
			errMsg << "The size of source image (" << src.size.width << " x " <<
				src.size.height << ") is not matched with the size of source data (" <<
				src.data.size() << ").";
			throw std::runtime_error(errMsg.str());
		}
	}

	template <typename T>
	ImageFrame<T> &ImageFrame<T>::operator=(ImageFrame<T> &&src)
	{
		if (src.data.size() == src.size.width * src.size.height * src.depth)
		{
			this->data_ = std::move(src.data_);
			this->depth_ = src.depth;
			this->size_ = src.size;
		}
		else
		{
			std::ostringstream errMsg;
			errMsg << "The size of source image (" << src.size.width << " x " <<
				src.size.height << ") is not matched with the size of its source data (" <<
				src.data.size() << ").";
			throw std::runtime_error(errMsg.str());
		}
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

	/*
	Resizes the std::vector<T> object only if necessary.
	If size is changed while the total number of elements are the same (reshaping),
	it does NOT run std::vector<T>::resize().
	*/
	template <typename T>
	void ImageFrame<T>::Reset(const Size2D<SizeType> &sz, SizeType d)
	{
		SizeType nElem = sz.width * sz.height * d;
		if (this->data.size() != nElem)
			this->data_.resize(nElem);
		this->depth_ = d;
		this->size_ = sz;
	}


	template <typename T>
	void ImageFrame<T>::Clear()
	{
		this->data_.clear();
		this->depth_ = 0;
		this->size_.width = 0;
		this->size_.height = 0;
	}
		
}

#endif
