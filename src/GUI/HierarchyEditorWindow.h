#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GuiWindow.h"
#include "Transform.h"

class HierarchyEditorWindow : GuiWindow {
public:
	HierarchyEditorWindow(std::string title, Transform* root);
	HierarchyEditorWindow(std::string title);
	void bindRoot(Transform* root);
	void draw();
	Transform* getSelected();
private:
	std::string title;
	Transform* root;
	Transform* selected = NULL;

	Transform* drawHierarchy(Transform* transform);
};