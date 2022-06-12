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
	Transform::Space space = Transform::Space::LOCAL;
	float position[3];
	float rotation[3];
	float scale[3];
	Vector3 rotationEuler;

	void readValues();
	void applyValues();
};