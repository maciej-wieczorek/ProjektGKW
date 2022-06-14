#include "SceneObject.h"

unsigned int SceneObject::nextId = 0;

unsigned int SceneObject::getNextId() {
	return nextId++;
}

SceneObject::SceneObject(std::string name, SceneObject* parent) :
	shadingInfo{ Color::white, 0, 0, 32.0f }
{
	this->name = name;
	Transform* parentTransform = NULL;
	if (parent != NULL) {
		parentTransform = parent->getTransform();
	}
	this->transform = new Transform(this, parentTransform);
	this->model = nullptr;
	this->shader = nullptr;

	this->id = SceneObject::getNextId();
}

SceneObject::SceneObject(std::string name) : SceneObject(name, NULL)
{
}

SceneObject::SceneObject() : SceneObject("Object")
{
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

Model* SceneObject::getModel()
{
	return model;
}

void SceneObject::setModel(Model* model)
{
	this->model = model;
}

Shader* SceneObject::getShader()
{
	return shader;
}

void SceneObject::setShader(Shader* shader)
{
	this->shader = shader;
}

ShadingInfo& SceneObject::getShadingInfo()
{
	return shadingInfo;
}

void SceneObject::addComponent(ComponentScript* component)
{
	if (component == NULL) {
		return;
	}
	component->setObject(this);
	components.push_front(component);
}

void SceneObject::Update()
{
	for (auto const& i : components) {
		i->Update();
	}
}
