#ifndef SERIAL_MONITOR_H
#define SERIAL_MONITOR_H 

#include "serial/serial.h"
#include <vector>
#include <string>
#include <chrono>

enum class TimeMode
{
	OFF = 0,
	TimeHMS,		 // H:M:S:ms
	SinceStartup,	 // in ms
	SinceConnection, // in ms
};

struct MessageData
{
	std::string content;
	std::tm* time;
};

class SerialMonitor
{
public:
	void ClearMonitor();
	void Write(const char* message);
	inline std::vector<MessageData>& GetMonitor() { return m_monitor; }
	
	void RefreshPorts() { m_ports = serial::list_ports(); }

	inline std::vector<serial::PortInfo>& GetPorts() { return m_ports; }
	inline serial::PortInfo& GetSelectedPort() { return m_ports[m_selectedPortIndex]; }
	inline const int GetSelectedPortIndex() { return m_selectedPortIndex; }
	void SelectPort(int newPortIndex) { m_selectedPortIndex = newPortIndex; }


	inline const std::vector<int>& GetBaudRates() { return s_baudRates; }
	inline const int& GetSelectedBaudRates() { return s_baudRates[m_selectedBaudRateIndex]; }
	inline const int GetSelectedBaudRatesIndex() { return m_selectedBaudRateIndex; }
	void SelectBaudRate(int newBaudRateIndex) { m_selectedPortIndex = newBaudRateIndex; }

	//GetPorts, GetSelectedPort, SelectPort, GetSelectedBaudRate, GetBaudRates, SelectBaudRate
private:
	std::vector<serial::PortInfo> m_ports;
	static std::vector<int> s_baudRates = { 4800, 9600, 19200, 38400, 57600, 115200 };
	int m_selectedPortIndex = 0;
	int m_selectedBaudRateIndex = 5; // start from 115200
	serial::Serial* m_serial = nullptr;
	std::vector<MessageData> m_monitor;
};

#endif