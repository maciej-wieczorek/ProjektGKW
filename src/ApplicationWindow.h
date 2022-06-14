#pragma once

#include <stdio.h>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class ApplicationWindow {
public:
	ApplicationWindow(int width, int height, std::string title, bool fullscreen);
	ApplicationWindow(int width, int height, std::string title);
	ApplicationWindow(int width, int height);
	ApplicationWindow();

	void setActive();
	GLFWwindow* getWindow();
	void getSize(int& width, int& height);
	bool shouldClose();

	void setTitle(std::string title);

	void beginFrame();
	void endFrame();
	void close();
private:
	GLFWwindow* window;

	float lastFrame = 0, deltaTime = 0;

	void processInput();
	void glfw_error_callback(int error, const char* description);
};