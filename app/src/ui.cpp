#include "application.h"

#define RADIO_BUTTON_TIMEMODE(msg,mode) if (ImGui::RadioButton(msg, (m_timemode == mode)))m_timemode = mode;


static bool connect_error = false;
static std::string connect_exception = "";


std::tm* GetLocalTime()
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(timepoint);
    return std::localtime(&currentTime_t);
}

void FireBridgeApplication::Render()
{
    RenderSettings();
    RenderMonitor();
}

void FireBridgeApplication::RenderConnectSettings()
{
    if (m_serialMonitor.GetPorts().size() > 0)
    {
        if (ImGui::BeginCombo("Port COM", m_serialMonitor.GetSelectedPort().port.c_str()))
        {
            for (int i = 0; i < m_serialMonitor.GetPorts().size(); ++i)
            {
                const bool isSelected = (m_serialMonitor.GetSelectedPortIndex() == i);
                if (ImGui::Selectable(m_serialMonitor.GetPorts()[i].port.c_str(), isSelected))
                {
                    m_serialMonitor.SelectPort(i);
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }
    else
    {
        ImGui::Text("NO PORTS AVAILABLE.");
    }


    if (ImGui::BeginCombo("Baud Rate", std::to_string(m_serialMonitor.GetSelectedBaudRate()).c_str()))
    {
        for (int i = 0; i < m_serialMonitor.GetBaudRates().size(); ++i)
        {
            const bool isSelected = (m_serialMonitor.GetSelectedBaudRateIndex() == i);
            if (ImGui::Selectable(std::to_string(m_serialMonitor.GetBaudRates()[i]).c_str(), isSelected))
            {
                m_serialMonitor.SelectBaudRate(i);
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::Button("Refresh"))
    {
        std::string p = m_serialMonitor.GetSelectedPort().port;
        m_serialMonitor.RefreshPorts();
        for (int i = 0; i < m_serialMonitor.GetPorts().size(); i++)
            if (p == m_serialMonitor.GetPorts()[i].port) m_serialMonitor.SelectPort(i);
    }
    ImGui::SameLine();
    if (ImGui::Button("Connect"))
    {
        connect_error = false;
        connect_exception = "";
        try
        {
            m_serialMonitor.Connect();
        }
        catch (std::exception e)
        {
            m_serialMonitor.FreeSerial();
            connect_error = true;
            connect_exception = e.what();
        }

        if (!connect_error)
            if (!m_serialMonitor.GetSerial()->isOpen())
            {
                m_serialMonitor.FreeSerial();
                connect_error = true;
            }
    }
}

void FireBridgeApplication::RenderSettings()
{
    ImGui::Begin("Settings");

    RenderConnectSettings();

    RADIO_BUTTON_TIMEMODE("display time [H:M:S]", TimeMode::TimeHMS);
    RADIO_BUTTON_TIMEMODE("display time relative to startup[H:M:S]", TimeMode::RelativeToStartupHMS);
    RADIO_BUTTON_TIMEMODE("since the program has been started [ms]", TimeMode::SinceStartup);
    RADIO_BUTTON_TIMEMODE("since connection [ms]", TimeMode::SinceConnection);
    RADIO_BUTTON_TIMEMODE("OFF", TimeMode::OFF);

    ImGui::Checkbox("New line for each read", &m_newline);
    ImGui::Separator();
    ImGui::InputTextMultiline("message", m_message, 128);
    ImGui::SameLine();
    if (ImGui::Button("Send") && m_serialMonitor.GetSerial())
    {
        m_serialMonitor.GetSerial()->write(m_message);
        memset(m_message, 0, sizeof(m_message));
    }
    ImGui::SeparatorText("Monitor");
    if (ImGui::Button("Copy monitor to clipboard"))
    {
        std::string clip = "";

        for (auto msg : m_serialMonitor.GetMonitor())
            clip += msg.content;

        ImGui::SetClipboardText(clip.c_str());
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear monitor")) m_serialMonitor.GetMonitor().clear();
    ImGui::End();

    if (m_serialMonitor.GetSerial() != nullptr)
    { // saves data if available and if connected
        if (int buff_size = m_serialMonitor.GetSerial()->available())
        {
            MessageData data;
            data.content = m_serialMonitor.GetSerial()->read(buff_size);
            data.time = GetLocalTime();
            m_serialMonitor.GetMonitor().emplace_back(data);
        }
    }
}

void FireBridgeApplication::RenderMonitor()

{
    ImGui::Begin("Monitor");
    if (m_serialMonitor.GetSerial() != nullptr)
    {
        for (auto i : m_serialMonitor.GetMonitor())
        {
            switch (m_timemode)
            {
            case TimeMode::TimeHMS:
                ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f),
                    "[%02d:%02d:%02d]", i.time->tm_hour, i.time->tm_min, i.time->tm_sec
                );
                ImGui::SameLine(0.0F, 0.0F);
                break;
            case TimeMode::RelativeToStartupHMS:
                ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f),
                    "[%02d:%02d:%02d]", i.time->tm_hour - m_startupTime->tm_hour,
                    i.time->tm_min - m_startupTime->tm_min,
                    i.time->tm_sec - m_startupTime->tm_sec
                ); // will be changed in the future
                break;
            }


            ImGui::Text(i.content.c_str());
            if (!m_newline && i.content[i.content.length() - 1] != '\n')
                ImGui::SameLine(0.0F, 0.0F);
        }
    }
    else
    {
        if (connect_error)
            ImGui::TextColored(ImVec4(0.8f, 0.f, 0.f, 1.f), "Error: Could not connect.\n%s", connect_exception.c_str());
        else
            ImGui::TextDisabled("(not connected)");
    }
    ImGui::End();
}