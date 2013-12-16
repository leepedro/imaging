#if !defined(SAFE_OPERATIONS_H)
#define SAFE_OPERATIONS_H

#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <typeinfo>

#if defined(WIN32)
#include <safeint.h>
using namespace msl::utilities;
#else
namespace std
{
	template <bool B, typename T = void>
	using enable_if_t = typename enable_if<B, T>::type;
}
#include "SafeInt.hpp"
#endif

namespace Imaging
{
	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Add(T t, U u, T &result)
	{
		if (SafeAdd(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value && std::is_arithmetic<U>::value, void>
		Add(T t, U u, T &result)
	{
		result = t + u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_floating_point<U>::value, void>
		Add(T t, U u, T &result)
	{
		static_assert(!std::is_integral<T>::value || !std::is_floating_point<U>::value, "Unsupported scenario.");
	}

	template <typename T, typename U>
	std::enable_if_t<!std::is_arithmetic<T>::value || !std::is_arithmetic<U>::value, void>
		Add(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Unsupported scenario.");
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		if (!SafeSubtract(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of subtract operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value && std::is_arithmetic<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		result = t - u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_floating_point<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		static_assert(!std::is_integral<T>::value || !std::is_floating_point<U>::value, "Unsupported scenario.");
	}

	template <typename T, typename U>
	std::enable_if_t<!std::is_arithmetic<T>::value || !std::is_arithmetic<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Unsupported scenario.");
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		if (!SafeMultiply(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of multiply operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_floating_point<T>::value && std::is_arithmetic<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		result = t * u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_integral<T>::value && std::is_floating_point<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		static_assert(!std::is_integral<T>::value || !std::is_floating_point<U>::value, "Unsupported scenario.");
	}

	template <typename T, typename U>
	std::enable_if_t<!std::is_arithmetic<T>::value || !std::is_arithmetic<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Unsupported scenario.");
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> Increment(T &t)
	{
		if (!SafeAdd(t, 1, t))
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

	template <typename T, typename U>
	std::enable_if_t<!std::is_arithmetic<T>::value, void> Increment(T &t)
	{
		static_assert(std::is_arithmetic<T>::value, "Unsupported scenario.");
	}

	template <typename T>
	std::enable_if_t<std::is_integral<T>::value, void> Decrement(T &t)
	{
		if (!SafeSubtract(t, 1, t))
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

	template <typename T, typename U>
	std::enable_if_t<!std::is_arithmetic<T>::value, void> Decrement(T &t)
	{
		static_assert(std::is_arithmetic<T>::value, "Unsupported scenario.");
	}
}

#endif
