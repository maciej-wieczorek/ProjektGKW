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

Quaternion Transform::getParentRotation(Space space)
{
	if (parent == NULL) {
		return Quaternion::identity;
	}
	return parent->getRotation(space);
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

Vector3 Transform::getPosition(Space space)
{
	if (space == Space::LOCAL) {
		return position;
	}
	else {
		glm::vec4 posGlobal = getParentMatrix() * glm::vec4(position.x, position.y, position.z, 1);
		return Vector3(posGlobal.x, posGlobal.y, posGlobal.z);
	}
}

Quaternion Transform::getRotation(Space space)
{
	if (space == Space::LOCAL) {
		return rotation;
	}
	else {
		glm::quat rotGlobal = getParentRotation(Space::GLOBAL).q * rotation.q;
		return Quaternion(rotGlobal);
	}
}

Vector3 Transform::getScale(Space space)
{
	if (space == Space::LOCAL) {
		return scale;
	}
	else {
		glm::vec4 scaleGlobal = getParentMatrix() * glm::vec4(scale.x, scale.y, scale.z, 1);
		return Vector3(scaleGlobal.x, scaleGlobal.y, scaleGlobal.z);
	}
}

void Transform::setPosition(Vector3 position, Space space)
{
	if (space == Space::LOCAL) {
		this->position = position;
	}
	else {
		glm::vec4 newPos = glm::inverse(getParentMatrix()) * glm::vec4(position.x, position.y, position.z, 1);
		this->position = Vector3(newPos.x, newPos.y, newPos.z);
	}
}

void Transform::setRotation(Quaternion rotation, Space space)
{
	if (space == Space::LOCAL) {
		this->rotation = rotation;
	}
	else {
		this->rotation = glm::inverse(getParentRotation(Space::GLOBAL).q) * rotation.q;
	}
}

void Transform::setScale(Vector3 scale, Space space)
{
	if (space == Space::LOCAL) {
		this->scale = scale;
	}
	else {
		glm::vec4 scaleGlobal = glm::inverse(getParentMatrix()) * glm::vec4(scale.x, scale.y, scale.z, 1);
		this->scale = Vector3(scaleGlobal.x, scaleGlobal.y, scaleGlobal.z);
	}
}

void Transform::rotateAround(Vector3 axis, float angles, Space space)
{
	if (space == Space::LOCAL) {
		rotation.rotateAround(axis, angles);
	}
	else {
		glm::vec4 axisLocal = glm::inverse(getMatrix()) * glm::vec4(axis.x, axis.y, axis.z, 0);
		rotation.rotateAround(Vector3(axisLocal.x, axisLocal.y, axisLocal.z), angles);
	}
}

Vector3 Transform::getForward(Space space)
{
	if (space == Space::LOCAL) {
		return Vector3::forward;
	}
	else {
		glm::vec4 forw = getMatrix() * glm::vec4(Vector3::forward.x, Vector3::forward.y, Vector3::forward.z, 0);
		return Vector3(forw.x, forw.y, forw.z);
	}
}

Vector3 Transform::getUp(Space space)
{
	if (space == Space::LOCAL) {
		return Vector3::up;
	}
	else {
		glm::vec4 up = getMatrix() * glm::vec4(Vector3::up.x, Vector3::up.y, Vector3::up.z, 0);
		return Vector3(up.x, up.y, up.z);
	}
}

Vector3 Transform::getRight(Space space)
{
	if (space == Space::LOCAL) {
		return Vector3::right;
	}
	else {
		glm::vec4 right = getMatrix() * glm::vec4(Vector3::right.x, Vector3::right.y, Vector3::right.z, 0);
		return Vector3(right.x, right.y, right.z);
	}
}

void Transform::move(Vector3 movement, Space space)
{
	if (space == Space::LOCAL) {
		position += movement;
	}
	else {
		glm::vec4 mov = glm::inverse(getParentMatrix()) * glm::vec4(movement.x, movement.y, movement.z, 0);
		position += Vector3(mov.x, mov.y, mov.z);
	}
}

void Transform::moveTo(Vector3 position, Space space)
{
	setPosition(position, space);
}
