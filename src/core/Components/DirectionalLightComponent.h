#pragma once

#include <glm/glm.hpp>

#include "../ComponentScript.h"

class ComponentScript;

class DirectionalLightComponent : public ComponentScript
{
public:
	glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 getDirection();

	void Update();
};