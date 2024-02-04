#define MAGMA_ENTRYPOINT
#include "application.h"
#include "Magma/Magma.h"


mg::Application* CreateApplication(int argc, char** argv)
{
	return new FireBridgeApplication();
}
