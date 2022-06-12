#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ComponentScript.h"

class CameraComponent : ComponentScript
{
public:
	float fov = 45.0f;
	float near = 0.1f;
	float far = 100.0f;

	glm::mat4 getViewMatrix();
	glm::mat4 getPerspectiveMatrix(float ratio);

	void Update();
};