#include "AzurDebug.h"

#include "InputHandler.h"

namespace AzurDebug
{
	bool debug_mode = false;

	void init()
	{
		debug_mode = false;
	}

	void update()
	{
		if (InputHandler::GetKeyTap(InputHandler::KEY_D))
		{
			debug_mode = !debug_mode;
		}
	}
}
