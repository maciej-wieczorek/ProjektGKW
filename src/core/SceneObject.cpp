#include "SceneObject.h"

SceneObject::SceneObject(std::string name, SceneObject* parent)
{
	this->name = name;
	Transform* parentTransform = NULL;
	if (parent != NULL) {
		parentTransform = parent->getTransform();
	}
	this->transform = new Transform(this, parentTransform);
	this->mesh = new Mesh();
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
