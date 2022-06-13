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
	ShadingInfo& getShadingInfo();

	void addComponent(ComponentScript* component);
	template<class T> T getComponent();

	void Update();
private:
	static unsigned int nextId;

	unsigned int id;
	std::string name;
	std::forward_list<ComponentScript*> components;
	Model* model;
	Shader* shader;
	ShadingInfo shadingInfo;
	
};

template<class T>
inline T SceneObject::getComponent()
{
	T result = NULL;
	for (ComponentScript* component : components) {
		result = dynamic_cast<T>(component);
		if (result != NULL) {
			return result;
		}
	}
	return NULL;
}
