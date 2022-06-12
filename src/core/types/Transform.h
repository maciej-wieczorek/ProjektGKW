#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Vector3.h"
#include "Quaternion.h"
#include "../SceneObject.h"

class SceneObject;

class Transform {
public:

	enum class Space {
		GLOBAL,
		LOCAL
	};

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

	Quaternion getParentRotation(Space space);
	glm::mat4 getParentMatrix();
	glm::mat4 getMatrix();
	bool isDirty();

	Vector3 getPosition(Space space);
	Quaternion getRotation(Space space);
	Vector3 getScale(Space space);

	void setPosition(Vector3 position, Space space);
	void setRotation(Quaternion rotation, Space space);
	void setScale(Vector3 scale, Space space);

	Vector3 getForward();
	Vector3 getUp();
	Vector3 getRight();

	void move(Vector3 movement, Space space);
	void moveTo(Vector3 position, Space space);
private:
	SceneObject * sceneObject;

	Transform * parent;
	std::vector<Transform*> children;

	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;
	bool dirty = true; //if any property of this transform was changed in this frame
	bool calcualted = false; //if matrix was calcualted this frame
};