#include "Mesh.h"

Mesh* Mesh::cube = NULL;
Mesh* Mesh::teapot = NULL;

void Mesh::initMeshes()
{
	cube = new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::texCoords, Cube::verticesCount);
	teapot = new Mesh(Teapot::vertices, Teapot::normals, Teapot::colors, Teapot::texCoords, Teapot::verticesCount);
}

Mesh::Mesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& colors, std::vector<float>& texCoords, int verticesCount)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colors = colors;
	this->texCoords = texCoords;
	this->verticesCount = verticesCount;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(4, &VBO[0]);

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

	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount * 2, &(texCoords[0]), GL_STATIC_DRAW);
}
