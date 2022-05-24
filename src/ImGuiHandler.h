#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class ImGuiHandler {
public:
	static void init();
	static void setContext(GLFWwindow* window, const char* glsl_version);
	static void startFrame();
	static void render();
	static void endFrame();
	static void close();

private:
	static ImGuiIO& io;
};