#include "application.h"

#define RADIO_BUTTON_TIMEMODE(msg,mode) if (ImGui::RadioButton(msg, (m_timemode == mode)))m_timemode = mode;




void FireBridgeApplication::Render()
{
    static bool connect_error = false;
    static std::string connect_exception = "";
	{
		ImGui::Begin("Settings");
		
        if (ImGui::BeginCombo("Port COM", m_ports[m_selectedPortIndex].port.c_str()))
        {
            for (int i = 0; i < m_ports.size(); ++i)
            {
                const bool isSelected = (m_selectedPortIndex == i);
                if (ImGui::Selectable(m_ports[i].port.c_str(), isSelected))
                {
                    m_selectedPortIndex = i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("baudrate", std::to_string(m_baudRates[m_selectedBaudRateIndex]).c_str())) {
            for (int i = 0; i < m_baudRates.size(); ++i) {
                bool isSelected = (m_selectedBaudRateIndex == i);
                if (ImGui::Selectable(std::to_string(m_baudRates[i]).c_str(), isSelected)) {
                    m_selectedBaudRateIndex = i;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if (ImGui::Button("Refresh"))
        {
            std::string p = m_ports[m_selectedPortIndex].port;
            m_ports = serial::list_ports();
            for (int i = 0; i < m_ports.size(); i++)
                if (p == m_ports[i].port) m_selectedPortIndex = i;
        }
        ImGui::SameLine();
        if (ImGui::Button("Connect"))
        {
            connect_error = false;
            connect_exception = "";
            if (m_serial != nullptr) delete m_serial;
            try {

            m_serial = new serial::Serial(
                m_ports[m_selectedPortIndex].port,
                m_baudRates[m_selectedBaudRateIndex],
                serial::Timeout::simpleTimeout(1000)
            );
            }
            catch (std::exception e)
            {
                //delete m_serial;
                m_serial = nullptr;
                connect_error = true;
                connect_exception = e.what();
            }

            if(!connect_error) 
                if (!m_serial->isOpen())
                {
                    delete m_serial;
                    m_serial = nullptr;
                    connect_error = true;
                }
        }
        RADIO_BUTTON_TIMEMODE("display time [H:M:S]", TimeMode::TimeHMS);
        RADIO_BUTTON_TIMEMODE("since the program has been started [ms]", TimeMode::SinceStartup);
        RADIO_BUTTON_TIMEMODE("OFF", TimeMode::OFF);
        ImGui::Checkbox("New line for each read", &m_newline);
        ImGui::Separator();
        ImGui::InputTextMultiline("message", m_message, 128);
        ImGui::SameLine();
        if (ImGui::Button("Send") && m_serial)
        {
            m_serial->write(m_message);
            memset(m_message, 0, sizeof(m_message));
        }
        ImGui::SeparatorText("Monitor");
        if (ImGui::Button("Copy monitor to clipboard"))
        {
            std::string clip = "";

            for each (auto msg in m_monitor)
                clip += msg.content;

            ImGui::SetClipboardText(clip.c_str());
        }
        ImGui::SameLine();
        if(ImGui::Button("Clear monitor")) m_monitor.clear();
		ImGui::End();
	}

    if (m_serial != nullptr)
    { // saves data if available and if connected
        if (int buff_size = m_serial->available())
        {
            MessageData data;
            data.content = m_serial->read(buff_size);
            auto timepoint = std::chrono::system_clock::now();
            std::time_t currentTime_t = std::chrono::system_clock::to_time_t(timepoint);
            data.time = std::localtime(&currentTime_t);
            m_monitor.emplace_back(data);
        }
    }

	{
		ImGui::Begin("Monitor");
        if (m_serial != nullptr)
        {
            for (auto i : m_monitor)
            {
                if (m_timemode == TimeMode::TimeHMS)
                {
                    ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f),
                        "[%02d:%02d:%02d]", i.time->tm_hour, i.time->tm_min, i.time->tm_sec
                    );

                    ImGui::SameLine(0.0F, 0.0F);
                }
                ImGui::Text(i.content.c_str());
                if(!m_newline && i.content[i.content.length()-1] != '\n')
                    ImGui::SameLine(0.0F,0.0F);
            }
        }
        else
        {
            if(connect_error)
            ImGui::TextColored(ImVec4(0.8f,0.f,0.f,1.f), "Error: Could not connect.\n%s", connect_exception.c_str());
            else
            ImGui::TextDisabled("(not connected)");
        }
		ImGui::End();
	}
}
