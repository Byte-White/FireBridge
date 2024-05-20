#include "Magma/Magma.h"

#include "SerialMonitor.h"


class FireBridgeApplication :public mg::Application
{
public:
	FireBridgeApplication();
	~FireBridgeApplication();

	void Init();
	void Render();
private:
	void RenderConnectSettings();

	void RenderSettings();
	void RenderMonitor();
private:
	void SetupTheme();
	void CheckConfig();
private:
	SerialMonitor m_timemode = TimeMode::OFF;
	
	bool m_newline = true;
	char m_message[128] = "";

	SerialMonitor m_serialMonitor;
};