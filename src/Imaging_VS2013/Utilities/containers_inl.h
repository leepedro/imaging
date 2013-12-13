#if !defined(CONTAINERS_INL_H)
#define CONTAINERS_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Array<T, N>

	// A = B + C
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator+(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		AddRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	// A = B - C
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator-(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		SubtractRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	// A = B * C
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator*(const Array<T, N> &rhs) const
	{
		Array<T, N> result;
		MultiplyRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	// A = B + c
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator+(T rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Add(*it, rhs, *itDst);
		return result;
	}

	// A = B - c
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator-(T rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Subtract(*it, rhs, *itDst);
		return result;
	}

	// A = B * c
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator*(T rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Multiply(*it, rhs, *itDst);
		return result;
	}

	// A += B
	template <typename T, ::size_t N>
	void Array<T, N>::operator+=(const Array<T, N> &rhs)
	{
		AddRange(this->data.begin(), this->data.end(), rhs.data.cbegin());
	}

	// A -= B
	template <typename T, ::size_t N>
	void Array<T, N>::operator-=(const Array<T, N> &rhs)
	{
		SubtractRange(this->data.begin(), this->data.end(), rhs.data.cbegin());
	}

	// A *= B
	template <typename T, ::size_t N>
	void Array<T, N>::operator*=(const Array<T, N> &rhs)
	{
		MultiplyRange(this->data.begin(), this->data.end(), rhs.data.cbegin());
	}

	// A += b
	template <typename T, ::size_t N>
	void Array<T, N>::operator+=(T rhs)
	{		
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Add(*it, rhs, *it);
	}

	// A -= b
	template <typename T, ::size_t N>
	void Array<T, N>::operator-=(T rhs)
	{
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Subtract(*it, rhs, *it);
	}

	// A *= b
	template <typename T, ::size_t N>
	void Array<T, N>::operator*=(T rhs)
	{
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Multiply(*it, rhs, *it);
	}

	// ++A
	template <typename T, ::size_t N>
	Array<T, N> &Array<T, N>::operator++(void)
	{
		IncrementRange(this->data.begin(), this->data.end());
		return *this;
	}

	// A++
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator++(int)
	{
		Array<T, N> temp = *this;
		++*this;
		return temp;
	}

	// --A
	template <typename T, ::size_t N>
	Array<T, N> &Array<T, N>::operator--(void)
	{
		DecrementRange(this->data.begin(), this->data.end());
		return *this;
	}

	// A--
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator--(int)
	{
		Array<T, N> temp = *this;
		--*this;
		return temp;
	}
}

#endif
