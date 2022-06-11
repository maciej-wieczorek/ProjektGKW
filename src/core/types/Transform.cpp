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

glm::mat4 Transform::getParentMatrix()
{
	if (parent == NULL) {
		return glm::mat4(1.0f);
	}
	else {
		return parent->getMatrix();
	}
}

glm::mat4 Transform::getMatrix()
{
	glm::mat4 parentMatrix = getParentMatrix();

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

Vector3 Transform::getPosition()
{
	return position;
}

Vector3 Transform::getPosition(bool local)
{
	if (local) {
		return getPosition();
	}
	else {
		glm::vec4 posGlobal = getParentMatrix() * glm::vec4(position.x, position.y, position.z, 1);
		return Vector3(posGlobal.x, posGlobal.y, posGlobal.z);
	}
}

void Transform::move(Vector3 movement)
{
	position += movement;
}

void Transform::move(Vector3 movement, bool local)
{
	if (local) {
		move(movement);
	}
	else {
		glm::vec4 mov = glm::inverse(getParentMatrix()) * glm::vec4(movement.x, movement.y, movement.z, 0);
		this->position += Vector3(mov.x, mov.y, mov.z);
	}
}

void Transform::moveTo(Vector3 position)
{
	this->position = position;
}

void Transform::moveTo(Vector3 position, bool local)
{
	if (local) {
		moveTo(position);
	}
	else {
		glm::vec4 newPos = glm::inverse(getParentMatrix()) * glm::vec4(position.x, position.y, position.z, 1);
		this->position = Vector3(newPos.x, newPos.y, newPos.z);
	}
}
