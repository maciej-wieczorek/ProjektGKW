#pragma once

#include <forward_list>
#include <string>

#include "types/Transform.h"
#include "ComponentScript.h"
#include "Model.h"

class Transform;
class ComponentScript;

class SceneObject {
public:
	static unsigned int getNextId();

	Transform* transform;

	SceneObject(std::string name, SceneObject* parent);
	SceneObject(std::string name);
	SceneObject();

	unsigned int getId();

	std::string getName();
	Transform* getTransform();
	Model* getModel();
	void setModel(Model* model);
	Shader* getShader();
	void setShader(Shader* shader);

	void addComponent(ComponentScript* component);

	void Update();
private:
	static unsigned int nextId;

	unsigned int id;
	std::string name;
	std::forward_list<ComponentScript*> components;
	Model* model;
	Shader* shader;
};