#include "CameraComponent.h"

glm::mat4 CameraComponent::getViewMatrix()
{
	Vector3 position = getPosition();

	return glm::lookAt(position.toVec3(), (position - sceneObject->transform->getForward(Transform::Space::GLOBAL)).toVec3(), sceneObject->transform->getUp(Transform::Space::GLOBAL).toVec3());
}

glm::mat4 CameraComponent::getPerspectiveMatrix(float ratio)
{
	return glm::perspective(glm::radians(fov), ratio, near, far);
}

Vector3 CameraComponent::getPosition()
{
	return sceneObject->transform->getPosition(Transform::Space::GLOBAL);
}

void CameraComponent::Update()
{
}
