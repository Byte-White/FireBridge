#include "Magma/Magma.h"

class MyApplication:public mg::Application
{
public:
	MyApplication()
	{
		window_width = 800;
		window_height = 600;
		window_title = "Magma Application";
	}
	~MyApplication()
	{

	}
	void Render() override
	{
		ImGui::Begin("Magma App Template");
    		if(mg::renderer->GetAPI() == mg::RenderAPI::Vulkan) ImGui::Text("Render API: Vulkan");
		else ImGui::Text("Render API: OpenGL");
		ImGui::End();
	}
};

mg::Application* CreateApplication(int argc, char** argv)
{
	return new MyApplication();
}
