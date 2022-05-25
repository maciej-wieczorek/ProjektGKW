#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GuiWindow.h"
#include "Vector3.h"

class TransformEditorWindow : GuiWindow {
public:
	TransformEditorWindow(std::string title, Vector3* position);
	void draw();
private:
	std::string title;
	Vector3* position;
	float** positionS;
};