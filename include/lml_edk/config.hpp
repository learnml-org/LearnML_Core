#pragma once

#ifdef LML_EDK_DYNAMIC
#	ifdef LML_EDK_INTERNAL
#		define LML_EDK_EXPORT __declspec(dllexport)
#	else
#		define LML_EDK_IMPORT __declspec(dllimport)
#	endif
#else
#	define LML_EDK_IMPORT
#endif