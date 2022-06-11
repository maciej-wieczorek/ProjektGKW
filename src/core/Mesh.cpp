#include "Mesh.h"

Mesh* Mesh::cube = NULL;
Mesh* Mesh::teapot = NULL;

void Mesh::initMeshes()
{
	cube = new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount);
	teapot = new Mesh(Teapot::vertices, Teapot::normals, Teapot::colors, Teapot::verticesCount);
}

Mesh::Mesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& colors, int verticesCount)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colors = colors;
	this->verticesCount = verticesCount;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, &VBO[0]);

	SetBuffers();
}

void Mesh::SetBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount * 4, &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount * 4, &(normals[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount * 4, &(colors[0]), GL_STATIC_DRAW);
}
