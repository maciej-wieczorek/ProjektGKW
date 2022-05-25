#pragma once

#include <vector>

#include "primitives/Cube.h"

class Mesh {
public:
	static Mesh* cube;

	Mesh(std::vector<float>& vertices, int verticesCount);
	Mesh();

	std::vector<float> vertices;
	float* normals;
	float* texCoords;
	int verticesCount;
	bool castShadows;
};