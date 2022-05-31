#include "Mesh.h"

Mesh* Mesh::cube = new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount);

Mesh::Mesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& colors, int verticesCount)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colors = colors;
	this->verticesCount = verticesCount;
}

Mesh::Mesh(std::vector<float>& vertices, int verticesCount)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;
}

Mesh::Mesh()
{
}
