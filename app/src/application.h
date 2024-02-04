#include "Magma/Magma.h"


class FireBridgeApplication :public mg::Application
{
public:
	FireBridgeApplication();
	~FireBridgeApplication();

	void SetupTheme();
	void Init();
	void Render();
};