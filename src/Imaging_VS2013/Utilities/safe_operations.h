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
		Add_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::true_type, std::true_type)
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
	void Add_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t + u;
	}

	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t + u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, void>
		Subtract(T t, U u, T &result)
	{
		Subtract_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::true_type, std::true_type)
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
	void Subtract_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t - u;
	}

	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t - u;
	}

	template <typename T, typename U>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, void>
		Multiply(T t, U u, T &result)
	{
		Multiply_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::true_type, std::true_type)
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
	void Multiply_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(false, "Unsupported scenario.");
	}

	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t * u;
	}

	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::false_type, std::false_type)
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

	template <typename T, typename U>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, T> Cast(U src)
	{
		T dst;
		Cast_imp(src, dst, std::is_integral<U>(), std::is_integral<T>());
		return dst;
	}

	// integral to integral; checking overflow
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::true_type, std::true_type)
	{
		if (!msl::utilities::SafeCast(src, dst))
		{
			std::ostringstream errMsg;
			errMsg << "The source value of cast operation exceeds the limit of " <<
				typeid(dst).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	// floating point to integral; checking overflow, suppressing data loss warning
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::false_type, std::true_type)
	{
		if (static_cast<U>(std::numeric_limits<T>::max()) < src)
			throw std::overflow_error("Source value is too high.");
		else if (static_cast<U>(std::numeric_limits<T>::min()) > src)
			throw std::overflow_error("Source value is too low.");
		else
			dst = static_cast<T>(src);
	}

	// integral to floating type; suppressing data loss warning if T is float
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::true_type, std::false_type)
	{
		dst = static_cast<T>(src);
	}

	// floating to floating; suppressing data loss warning if T is double T is float
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::false_type, std::false_type)
	{
		dst = static_cast<float>(src);
	}
}

#endif
