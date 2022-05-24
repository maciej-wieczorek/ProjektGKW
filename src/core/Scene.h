#pragma once

#include <string>

#include "SceneObject.h"
#include "types/Color.h"

class Scene {
public:
	unsigned int getNextId();

	Scene(std::string name, unsigned int id);
	Scene(std::string name);
	Scene();

	SceneObject* getRootObject();
	void setRootObject(SceneObject* root);

	void Update();
private:
	unsigned int nextId = 0;

	unsigned int id;
	std::string name;
	SceneObject* sceneRoot;
	Color backgroundColor;
};
