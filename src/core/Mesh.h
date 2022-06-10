#pragma once

#include <vector>

#include "primitives/Cube.h"
#include "primitives/Teapot.h"

class Mesh {
public:
	static Mesh* cube;

	Mesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& colors, int verticesCount);
	Mesh(std::vector<float>& vertices, int verticesCount);
	Mesh();

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<float> texCoords;
	int verticesCount;
	bool castShadows;
};