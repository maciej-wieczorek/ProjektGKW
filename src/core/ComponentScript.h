#pragma once

#include "SceneObject.h"

class SceneObject;

class ComponentScript {
public:
	virtual void Update() = 0;
private:
	SceneObject* sceneObject;
};