#ifndef SERIAL_MONITOR_H
#define SERIAL_MONITOR_H 

#include "serial/serial.h"
#include <vector>
#include <string>
#include <chrono>

enum class TimeMode
{
	OFF = 0,
	TimeHMS,				// H:M:S:ms
	RelativeToStartupHMS,	// H:M:S:ms
	SinceStartup,			// in ms
	SinceConnection,		// in ms
};

std::tm* GetLocalTime();


struct MessageData
{
	std::string content;
	std::tm* time;
};


class SerialMonitor
{
public:
	SerialMonitor()
	{
	}
	inline std::vector<MessageData>& GetMonitor() { return m_monitor; }
	
	void RefreshPorts() { m_ports = serial::list_ports(); }
	void Connect() 
	{
		if (m_serial != nullptr) delete m_serial;

		m_serial = new serial::Serial(
			m_ports[m_selectedPortIndex].port,
			m_baudRates[m_selectedBaudRateIndex],
			serial::Timeout::simpleTimeout(1000)
		);
	}

	inline std::vector<serial::PortInfo>& GetPorts() { return m_ports; }
	inline serial::PortInfo& GetSelectedPort() { return m_ports[m_selectedPortIndex]; }
	
	inline const int GetSelectedPortIndex() { return m_selectedPortIndex; }
	void SelectPort(int newPortIndex) { m_selectedPortIndex = newPortIndex; }


	inline const std::vector<int>& GetBaudRates() { return m_baudRates; }
	inline const int& GetSelectedBaudRate() { return m_baudRates[m_selectedBaudRateIndex]; }
	inline const int GetSelectedBaudRateIndex() { return m_selectedBaudRateIndex; }
	void SelectBaudRate(int newBaudRateIndex) { m_selectedBaudRateIndex = newBaudRateIndex; }

	serial::Serial* GetSerial() { return m_serial; }

	void FreeSerial() 
	{
		if (m_serial != nullptr)
		{
			delete m_serial;
			m_serial = nullptr;
		}
	}

	//GetPorts, GetSelectedPort, SelectPort, GetSelectedBaudRate, GetBaudRates, SelectBaudRate
private:
	std::vector<serial::PortInfo> m_ports;
	const std::vector<int> m_baudRates = { 4800, 9600, 19200, 38400, 57600, 115200 };
	int m_selectedPortIndex = 0;
	int m_selectedBaudRateIndex = 5; // start from 115200
	serial::Serial* m_serial = nullptr;
	std::vector<MessageData> m_monitor;
};
#endif