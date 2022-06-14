#pragma once

#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <stack> 
#include <iostream>

#include "Components/CameraComponent.h"
#include "core/Scene.h"
#include "core/SceneObject.h"
#include "helpers/RootDir.h"
#include "Shader.h"

#include "LightStructs.h"

class CameraRenderer {
public:
	CameraRenderer(GLFWwindow* window, CameraComponent* camera, Scene* scene);
	void render();
private:
	GLFWwindow* window;
	CameraComponent* camera;
	Scene* scene;

	void renderObject(const glm::mat4 &M, const glm::mat4 &P, SceneObject* object);
};