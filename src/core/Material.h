#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

class Material {
public:
	static Material* emerald;
	static Material* jade;
	static Material* obsidian;
	static Material* pearl;
	static Material* ruby;
	static Material* turquoise;
	static Material* brass;
	static Material* bronze;
	static Material* chrome;
	static Material* copper;
	static Material* gold;
	static Material* silver;

	static void initMaterials();
	static std::vector<Material*> materials;

	Material(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};