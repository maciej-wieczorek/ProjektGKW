#include "Mesh.h"

Mesh* Mesh::cube = new Mesh(Cube::vertices, Cube::verticesCount);

Mesh::Mesh(std::vector<float>& vertices, int verticesCount)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;
}

Mesh::Mesh()
{
}
