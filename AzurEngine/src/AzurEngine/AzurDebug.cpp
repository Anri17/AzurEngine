#include "AzurDebug.h"

#include "InputHandler.h"

namespace AzurDebug
{
	bool debug_mode = false;

	void init()
	{
		// AzurDebug::debug_mode is turned on by default if _DEBUG is defined
#ifdef _DEBUG
		debug_mode = true;
#else
		debug_mode = false;
#endif
	}

	void update()
	{
		if (InputHandler::get_key_tap(InputHandler::KEY_D))
		{
			debug_mode = !debug_mode;
		}
	}
}
