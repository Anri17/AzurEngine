#include "Application.h"

#include "AzurLib.h"

int main(int argc, char* argv[])
{
	Application::Start();

	// TODO: Preload the sprites into an asset class
	// TODO: Have that asset class available for every component that needs it
	// Don't create a new sprite for each component. That allocates needless memory
	_CrtDumpMemoryLeaks();

	return 0;

}

