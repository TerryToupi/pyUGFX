#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

namespace setup
{
	enum Platforms : unsigned int
	{
		UNDEFINED = 0,
		VULKAN = 1,
		METAL = 2
	};

	// initializing the platform context based on OS!
	void ContextInit(Platforms platform = Platforms::UNDEFINED);

	// destroy the platform context
	void ContextShutDown();
}

#endif // !__CONTEXT_HPP__
