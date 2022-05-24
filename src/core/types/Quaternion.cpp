#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w) {
	q = glm::quat(w, x, y, z);
}

Quaternion::Quaternion(float x, float y, float z) {
	q = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
}

Quaternion::Quaternion(Vector3 rotationAxis, float rotationAngle) {
	q = glm::angleAxis(glm::radians(rotationAngle), rotationAxis.toVec3());
}

Quaternion::Quaternion() {
	q = glm::quat();
}

glm::mat4 Quaternion::getRotationMatrix() {
	return glm::toMat4(q);
}

void Quaternion::setEuler(float x, float y, float z) {
	q = glm::quat(glm::vec3(x, y, z));
}