#pragma once

#include <glm/glm.hpp>

#include "../ComponentScript.h"

class PointLightComponent : public ComponentScript
{
public:
	glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	glm::vec3 getPosition();

	void Update();
};