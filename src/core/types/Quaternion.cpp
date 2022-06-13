#include "Quaternion.h"

const Quaternion Quaternion::identity = Quaternion();

Quaternion::Quaternion(float x, float y, float z, float w) {
	q = glm::quat(w, x, y, z);
}

Quaternion::Quaternion(float x, float y, float z) {
	/*glm::quat ax = glm::angleAxis(glm::radians(x), glm::vec3(1, 0, 0));
	glm::quat ay = glm::angleAxis(glm::radians(y), glm::vec3(0, 1, 0));
	glm::quat az = glm::angleAxis(glm::radians(z), glm::vec3(0, 0, 1));
	q = az * ay * ax;*/

	q = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
	
}

Quaternion::Quaternion(Vector3 rotationAxis, float rotationAngle) {
	q = glm::angleAxis(glm::radians(rotationAngle), rotationAxis.toVec3());
}

Quaternion::Quaternion(glm::quat q)
{
	this->q = q;
}

Quaternion::Quaternion() {
	q = glm::identity<glm::quat>();
}

glm::mat4 Quaternion::getRotationMatrix() {
	return glm::toMat4(q);
}

void Quaternion::rotateAround(Vector3 axis, float angle)
{
	q = q * glm::angleAxis(glm::radians(angle), axis.toVec3());
}

void Quaternion::setEuler(float x, float y, float z) {
	q = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
}

Vector3 Quaternion::getEuler()
{
	glm::vec3 euler = glm::eulerAngles(q);
	return Vector3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z));
}
