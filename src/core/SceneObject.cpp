#include "SceneObject.h"

unsigned int SceneObject::nextId = 0;

unsigned int SceneObject::getNextId() {
	return nextId++;
}

SceneObject::SceneObject(std::string name, SceneObject* parent, Mesh* mesh, Material* material)
{
	this->name = name;
	Transform* parentTransform = NULL;
	if (parent != NULL) {
		parentTransform = parent->getTransform();
	}
	this->transform = new Transform(this, parentTransform);
	this->mesh = mesh;
	this->material = material;

	this->id = SceneObject::getNextId();
}

SceneObject::SceneObject(std::string name, SceneObject* parent) : SceneObject(name, parent, NULL, NULL)
{
	
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

void SceneObject::addComponent(ComponentScript* component)
{
	component->setObject(this);
	components.push_front(component);
}

void SceneObject::Update()
{
	for (auto const& i : components) {
		i->Update();
	}
}
