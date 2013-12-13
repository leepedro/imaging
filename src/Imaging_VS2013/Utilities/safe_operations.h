#if !defined(SAFE_OPERATIONS_H)
#define SAFE_OPERATIONS_H

#include <stdexcept>
#include <sstream>

#include <safeint.h>

namespace Imaging
{
	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Add(T t, U u, T &result)
	{
		if (!msl::utilities::SafeAdd(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value, void>
		Add(T t, U u, T &result)
	{
		result = t + u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		if (!msl::utilities::SafeSubtract(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of subtract operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value, void>
		Subtract(T t, U u, T &result)
	{
		result = t - u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		if (!msl::utilities::SafeMultiply(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of multiply operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value, void>
		Multiply(T t, U u, T &result)
	{
		result = t * u;
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> Increment(T &t)
	{
		if (!msl::utilities::SafeAdd(t, 1, t))
		{
			std::ostringstream errMsg;
			errMsg << "The result of increment operation exceeds the limit of " <<
				typeid(t).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T>
	std::enable_if_t<std::is_floating_point<T>::value, void> Increment(T &t)
	{
		++t;
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> Decrement(T &t)
	{
		if (!msl::utilities::SafeSubtract(t, 1, t))
		{
			std::ostringstream errMsg;
			errMsg << "The result of decrement operation exceeds the limit of " <<
				typeid(t).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T>
	std::enable_if_t<std::is_floating_point<T>::value, void> Decrement(T &t)
	{
		--t;
	}
}

#endif
