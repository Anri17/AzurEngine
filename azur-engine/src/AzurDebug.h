#ifndef _AZUR_DEBUG_H
#define _AZUR_DEBUG_H

#include <iostream>

namespace AzurDebug
{
	extern bool debug_mode;

	extern void init();
	extern void update();
}

#define DEBUG_CONSOLE_LOG(x) (std::cout << x << "\n")

#endif // _AZUR_DEBUG_H