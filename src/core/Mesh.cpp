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
}

Mesh::Mesh(std::vector<float>& vertices, int verticesCount)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;
}

Mesh::Mesh()
{
}
