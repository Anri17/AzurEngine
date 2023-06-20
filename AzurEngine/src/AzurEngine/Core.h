#pragma once

#ifdef AZ_PLATFORM_WINDOWS
	#ifdef AZ_BUILD_DLL
		#define AZUR_API __declspec(dllexport)
	#else
		#define AZUR_API __declspec(dllimport)
	#endif
#else
	#error Azur Engine only supports Windows!
#endif