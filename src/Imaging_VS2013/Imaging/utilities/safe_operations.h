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
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, void> 
		Add(T t, U u, T &result)
	{
		AddImp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void AddImp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeAdd(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	void AddImp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void AddImp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t + u;
	}

	template <typename T, typename U>
	void AddImp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t + u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		SubtractImp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void SubtractImp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeSubtract(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	void SubtractImp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void SubtractImp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t - u;
	}

	template <typename T, typename U>
	void SubtractImp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t - u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		MultiplyImp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void MultiplyImp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeMultiply(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	template <typename T, typename U>
	void MultiplyImp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void MultiplyImp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t * u;
	}

	template <typename T, typename U>
	void MultiplyImp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t * u;
	}

	template <typename T>
	std::enable_if_t<std::is_arithmetic<T>::value, void> Increment(T &value)
	{
		Increment_imp(value, std::is_integral<T>());
	}

	template <typename T>
	void Increment_imp(T &value, std::true_type)
	{
		Add(value, 1, value);
	}

	template <typename T>
	void Increment_imp(T &value, std::false_type)
	{
		++value;
	}

	template <typename T>
	std::enable_if_t<std::is_arithmetic<T>::value, void> Decrement(T &value)
	{
		Decrement_imp(value, std::is_integral<T>());
	}

	template <typename T>
	void Decrement_imp(T &value, std::true_type)
	{
		Subtract(value, 1, value);
	}

	template <typename T>
	void Decrement_imp(T &value, std::false_type)
	{
		--value;
	}
}

#endif
