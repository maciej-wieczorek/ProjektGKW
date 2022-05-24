#pragma once

#include <vector>

class Mesh {
public:
	std::vector<float> vertices;
	float* normals;
	float* texCoords;
	int verticesCount;
	bool castShadows;
};