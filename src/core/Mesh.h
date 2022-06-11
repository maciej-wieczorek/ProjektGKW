#pragma once

#include <vector>

#include <glad/glad.h>

#include "primitives/Cube.h"
#include "primitives/Teapot.h"


class Mesh {
public:
	enum BUFFER_TYPE {
		VERTICES = 0,
		NORMALS = 1,
		COLORS = 2
	};

	static Mesh* cube;
	static Mesh* teapot;

	static void initMeshes();

	unsigned int VBO[3]; //[vertices, normals, colors]
	unsigned int VAO;

	Mesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& colors, int verticesCount);

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<float> texCoords;
	int verticesCount;
	bool castShadows;

private:
	void SetBuffers();
};