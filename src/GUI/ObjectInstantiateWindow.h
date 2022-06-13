#pragma once

#include <string>
#include <vector>
#include <utility>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Scene.h"
#include "SceneObject.h"
#include "GuiWindow.h"
#include "Transform.h"
#include "Vector3.h"
#include "HierarchyEditorWindow.h"

class ObjectInstantiateWindow : GuiWindow {
public:
	enum SpawnPlace {
		PLACE_CENTER = 0,
		PLACE_SELECTED = 1,
		PLACE_CUSTOM = 2
	};

	enum SpawnMode {
		MODE_FREE = 0,
		MODE_CHILD = 1
	};

	ObjectInstantiateWindow(std::string title, Scene* scene, HierarchyEditorWindow* hierarchyWindow, std::vector<std::pair<Model*, std::string>> models);
	ObjectInstantiateWindow(std::string title, Scene* scene, HierarchyEditorWindow* hierarchyWindow);
	void setModelsList(std::vector<std::pair<Model*, std::string>> models);
	void draw();
private:
	std::string title;
	std::vector<std::pair<Model*, std::string>> models;
	Scene* scene;
	HierarchyEditorWindow* hierarchyWindow;

	char name[128] = "Obiekt";
	int spawnPlace = SpawnPlace::PLACE_CENTER;
	int spawnMode = SpawnMode::MODE_FREE;
	float customPosition[3] = { 0,0,0 };

	void instantiateObject(int id);
};