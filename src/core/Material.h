#pragma once

#include <glm/vec3.hpp>

class Material {
public:
	static Material* gold;

	static void initMaterials();

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};