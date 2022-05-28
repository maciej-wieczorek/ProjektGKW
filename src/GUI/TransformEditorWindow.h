#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GuiWindow.h"
#include "Transform.h"
#include "Vector3.h"

class TransformEditorWindow : GuiWindow {
public:
	TransformEditorWindow(std::string title, Transform* transform);
	TransformEditorWindow(std::string title);
	void bindTransform(Transform* transform);
	void draw();
private:
	std::string title;
	Transform* transform;
	float** position;
	float** rotation;
	float** scale;
	Vector3 rotationEuler;
};