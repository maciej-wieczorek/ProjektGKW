#include "Transform.h"

Transform::Transform(SceneObject* sceneObject, Transform* parent)
{
	this->sceneObject = sceneObject;
	this->setParent(parent);
	this->children = {};

	this->position = Vector3(0, 0, 0);
	this->rotation = Quaternion(0, 0, 0);
	this->scale = Vector3(1, 1, 1);
}

Transform::Transform(SceneObject* sceneObject) : Transform(sceneObject, NULL)
{

}

SceneObject* Transform::getSceneObject() {
	return sceneObject;
}

Transform* Transform::getParent() {
	return parent;
}

void Transform::setParent(Transform* parent)
{
	this->parent = parent;
	if (parent != NULL) {
		parent->appendChild(this);
	}
}

std::vector<Transform*>* Transform::getChildren()
{
	return &children;
}

int Transform::getChildrenCount()
{
	return children.size();
}

Transform* Transform::getChild(int index)
{
	//TODO: add some range validation
	return children[index];
}

void Transform::appendChild(Transform* child)
{
	children.push_back(child);
}

glm::mat4 Transform::getMatrix()
{
	glm::mat4 parentMatrix;

	if (parent == NULL) {
		parentMatrix = glm::mat4(1.0f);
	}
	else {
		parentMatrix = parent->getMatrix();
	}

	if (isDirty()) {
		localMatrix = glm::mat4(1.0f);

		localMatrix = glm::translate(localMatrix, position.toVec3());

		localMatrix = localMatrix * rotation.getRotationMatrix();

		localMatrix = glm::scale(localMatrix, scale.toVec3());
	}

	if ((parent != NULL && parent->isDirty()) || isDirty()) {
		worldMatrix = parentMatrix * localMatrix;
	}
	
	calcualted = true;

	return worldMatrix;
}

bool Transform::isDirty() {
	return dirty;
}
