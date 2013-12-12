#if !defined(CONTAINERS_INL_H)
#define CONTAINERS_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Array<T, N>

	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator+(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		Add(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(), result.data.begin());
		return result;
	}

	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator-(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		Subtract(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator*(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		Multiply(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	template <typename T, ::size_t N>
	Array<T, N> &Array<T, N>::operator++(void)
	{
		Increment(this->data.begin(), this->data.end());
		return *this;
	}

	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator++(int)
	{
		Array<T, N> temp = *this;
		++*this;
		return temp;
	}
}

#endif
