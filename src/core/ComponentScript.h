#pragma once

#include "SceneObject.h"

class SceneObject;

class ComponentScript {
public:
	void setObject(SceneObject* object);
	virtual void Update() = 0;
protected:
	SceneObject* sceneObject;
};