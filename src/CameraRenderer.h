#pragma once

#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <stack> 
#include <iostream>

#include "Camera.h"
#include "core/Scene.h"
#include "core/SceneObject.h"
#include "helpers/RootDir.h"
#include "Shader.h"


class CameraRenderer {
public:
	CameraRenderer(GLFWwindow* window, Camera* camera, Scene* scene);
	void render();
private:
	GLFWwindow* window;
	Camera* camera;
	Scene* scene; //tmp, move to Camera

	void renderObject(const glm::mat4 &M, const glm::mat4 &P, SceneObject* object);
};