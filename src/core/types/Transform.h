#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Vector3.h"
#include "Quaternion.h"
#include "../SceneObject.h"

class SceneObject;

class Transform {
public:
	Transform(SceneObject* sceneObject, Transform* parent);
	Transform(SceneObject* sceneObject);

	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	SceneObject* getSceneObject();

	Transform * getParent();
	void setParent(Transform* parent);

	std::vector<Transform*>* getChildren();
	int getChildrenCount();
	Transform* getChild(int index);
	void appendChild(Transform* child);

	glm::mat4 getParentMatrix();
	glm::mat4 getMatrix();
	bool isDirty();

	Vector3 getPosition();
	Vector3 getPosition(bool local);

	Vector3 getForward();
	Vector3 getUp();
	Vector3 getRight();

	void move(Vector3 movement);
	void move(Vector3 movement, bool local);
	void moveTo(Vector3 position);
	void moveTo(Vector3 position, bool local);
private:
	SceneObject * sceneObject;

	Transform * parent;
	std::vector<Transform*> children;

	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;
	bool dirty = true; //if any property of this transform was changed in this frame
	bool calcualted = false; //if matrix was calcualted this frame
};