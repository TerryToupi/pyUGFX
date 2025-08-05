#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <memory>

namespace gfx 
{
	template<typename T>
	using uPtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr uPtr <T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using sPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr sPtr <T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#endif // !__COMMON_HPP__
