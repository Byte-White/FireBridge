#include "application.h"
#include "FiraCode.embed"
#include "configini.embed"

#include <iostream>
#include <fstream>



FireBridgeApplication::FireBridgeApplication()
{
    m_startupTime = GetLocalTime();
}

FireBridgeApplication::~FireBridgeApplication()
{

}


//Crimson shadow theme
void FireBridgeApplication::SetupTheme()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.75f, 0.10f, 0.78f);
    style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.75f, 0.10f, 1.00f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.37f, 0.08f, 0.08f, 0.86f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(0.87f, 0.00f, 0.00f, 0.80f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.87f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.75f, 0.00f, 0.00f, 0.97f);
    style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.61f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.86f, 0.00f, 1.00f);
}

static bool fileExists(const std::string& filename) 
{
    std::ifstream file(filename);
    return file.good(); 
}

void FireBridgeApplication::CheckConfig()
{
    if (!fileExists("config.ini")) {
        std::ofstream file("config.ini");
        if (file.is_open())
        {
            file << g_configini;
            MAGMA_INFO("Created a 'config.ini' file.");
        }
        else MAGMA_ERROR("Unable to create 'config.ini' file.");
    } 
    else MAGMA_INFO("'config.ini' file was found.");
}

void FireBridgeApplication::Init()
{
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    SetSize(mode->width / 2 + 250, mode->height / 2 + 125);
    SetTitle("FireBridge");

    SetupTheme();
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false;
    ImFont* firacodeFont = io.Fonts->AddFontFromMemoryTTF((void*)g_FiraCode, sizeof(g_FiraCode)/ sizeof(unsigned char), 20.0f, &fontConfig);
    io.FontDefault = firacodeFont;
    io.IniFilename = "config.ini";
    
    CheckConfig();

    // get open ports
    m_serialMonitor.RefreshPorts();
}