#include "Magma/Magma.h"
#include "serial/serial.h"


class FireBridgeApplication :public mg::Application
{
public:
	FireBridgeApplication();
	~FireBridgeApplication();

	void Init();
	void Render();
private:
	void SetupTheme();
	void CheckConfig();
private:
	std::vector<serial::PortInfo> m_ports;
	std::vector<int> m_baudRates = { 4800, 9600, 19200, 38400, 57600, 115200 };
	int m_currentItem = 0;
	int m_selectedBaudRateIndex = 5; // start from 115200
};