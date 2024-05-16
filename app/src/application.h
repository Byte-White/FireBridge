#include "Magma/Magma.h"
#include "serial/serial.h"
#include <vector>
#include <string>
#include <chrono>


class FireBridgeApplication :public mg::Application
{
	enum class TimeMode
	{
		OFF = 0,
		TimeHMS,		 // H:M:S:ms
		SinceStartup,	 // in ms
		SinceConnection, // in ms
	}m_timemode = TimeMode::OFF;
public:
	FireBridgeApplication();
	~FireBridgeApplication();

	void Init();
	void Render();
private:
	void SetupTheme();
	void CheckConfig();
private:
	struct MessageData {
		std::string content;
		std::tm* time;
	};
	std::vector<serial::PortInfo> m_ports;
	std::vector<int> m_baudRates = { 4800, 9600, 19200, 38400, 57600, 115200 };
	int m_selectedPortIndex = 0;
	int m_selectedBaudRateIndex = 5; // start from 115200
	bool m_newline = true;
	char m_message[128] = "";
	serial::Serial* m_serial = nullptr;
	std::vector<MessageData> m_monitor;
};