#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GuiWindow.h"
#include "Transform.h"
#include "Color.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

class MaterialEditorWindow : GuiWindow
{
public:
	MaterialEditorWindow(std::string title, Transform* transform);
	void bindTransform(Transform* transform);
	void draw();
private:
	std::string title;
	Transform* transform;

	//Color color;
	//Material material;
	//Texture texture;
	float shininess;

	void readValues();
	void applyValues();
};

