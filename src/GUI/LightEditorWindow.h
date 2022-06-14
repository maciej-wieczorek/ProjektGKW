#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GuiWindow.h"
#include "Transform.h"

#include "../core/Components/DirectionalLightComponent.h"
#include "../core/Components/PointLightComponent.h"

class LightEditorWindow : GuiWindow
{
public:
	LightEditorWindow(std::string title);
	void bindDirectional(DirectionalLightComponent* light);
	void bindPoint(PointLightComponent* light);
	void draw();
private:
	std::string title;
	DirectionalLightComponent* directionalLight;
	PointLightComponent* pointLight;

	ImVec4 ambient = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	ImVec4 diffuse = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	ImVec4 specular = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	void readValues();
	void applyValues();
};

