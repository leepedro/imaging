#if !defined(SAFE_OPERATIONS_H)
#define SAFE_OPERATIONS_H

#include <stdexcept>
#include <sstream>
#if defined(WIN32)
#include <safeint.h>
//using namespace msl::utilities;
#else
// Include the safeint.h here.
#endif

namespace Imaging
{
	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		SafeAdd(T t, U u, T &result)
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
		SafeAdd(T t, U u, T &result)
	{
		result = t + u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		SafeSubtract(T t, U u, T &result)
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
		SafeSubtract(T t, U u, T &result)
	{
		result = t - u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		SafeMultiply(T t, U u, T &result)
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
		SafeMultiply(T t, U u, T &result)
	{
		result = t * u;
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> SafeIncrement(T &t)
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
	std::enable_if_t<std::is_floating_point<T>::value, void> SafeIncrement(T &t)
	{
		++t;
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> SafeDecrement(T &t)
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
	std::enable_if_t<std::is_floating_point<T>::value, void> SafeDecrement(T &t)
	{
		--t;
	}
}

#endif
