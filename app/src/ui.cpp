#include "application.h"

void FireBridgeApplication::Render()
{
	{
		ImGui::Begin("Settings");
		
        if (ImGui::BeginCombo("Port COM", m_ports[m_currentItem].port.c_str()))
        {
            for (int i = 0; i < m_ports.size(); ++i)
            {
                const bool isSelected = (m_currentItem == i);
                if (ImGui::Selectable(m_ports[i].port.c_str(), isSelected))
                {
                    m_currentItem = i;
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
            m_ports = serial::list_ports();
        static bool is_on = false;
        ImGui::RadioButton("display time [H:M:S:ms]",is_on);
        ImGui::RadioButton("display time since the program has been started [ms]", is_on);
        ImGui::RadioButton("OFF", is_on);

		ImGui::End();
	}

	{
		ImGui::Begin("Monitor");
        
		ImGui::End();
	}
}
