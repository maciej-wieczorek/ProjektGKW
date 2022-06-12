#include "CameraComponent.h"

glm::mat4 CameraComponent::getViewMatrix()
{
	Vector3 position = sceneObject->transform->getPosition(Transform::Space::GLOBAL);

	return glm::lookAt(position.toVec3(), (position - sceneObject->transform->getForward()).toVec3(), sceneObject->transform->getUp().toVec3());
}

glm::mat4 CameraComponent::getPerspectiveMatrix(float ratio)
{
	return glm::perspective(glm::radians(fov), ratio, near, far);
}

void CameraComponent::Update()
{
}
