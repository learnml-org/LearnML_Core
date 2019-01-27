#pragma once

#include <string>

namespace lml
{
	enum class architecture
	{
		x86,
		x64,
		arm,
		arm64,

		target =
#if defined(_M_AMD64)
		x64
#elif defined(_M_IX86)
		x86
#elif defined(_M_ARM)
		arm
#elif defined(_M_ARM64)
		arm64
#else
#	error Not supported
#endif
	};

	enum class os
	{
		windows,
		
		target = windows
	};

	std::string get_os_name();
	std::string get_windows_name();
}