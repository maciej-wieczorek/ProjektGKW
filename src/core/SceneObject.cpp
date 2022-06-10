#include "SceneObject.h"

unsigned int SceneObject::nextId = 0;

unsigned int SceneObject::getNextId() {
	return nextId++;
}

SceneObject::SceneObject(std::string name, SceneObject* parent)
{
	this->name = name;
	Transform* parentTransform = NULL;
	if (parent != NULL) {
		parentTransform = parent->getTransform();
	}
	this->transform = new Transform(this, parentTransform);
	this->mesh = new Mesh();
	this->material = new Material(Shader::lambert);

	this->id = SceneObject::getNextId();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, &VBO[0]);
}

SceneObject::SceneObject(std::string name) : SceneObject(name, NULL)
{
	
}

SceneObject::SceneObject() : SceneObject("Object") {

}

unsigned int SceneObject::getId()
{
	return id;
}

std::string SceneObject::getName()
{
	return name;
}

Transform* SceneObject::getTransform()
{
	return transform;
}

Mesh* SceneObject::getMesh()
{
	return mesh;
}

void SceneObject::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
	SetBuffers();
}

Material* SceneObject::getMaterial()
{
	return material;
}

void SceneObject::Update()
{
	for (auto const& i : components) {
		i->Update();
	}
}

void SceneObject::SetBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->verticesCount * 4, &(mesh->vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->verticesCount * 4, &(mesh->normals[0]), GL_STATIC_DRAW);
}
