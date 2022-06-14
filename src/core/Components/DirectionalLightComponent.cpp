#include "DirectionalLightComponent.h"

glm::vec3 DirectionalLightComponent::getDirection()
{
	return sceneObject->transform->getForward(Transform::Space::GLOBAL).toVec3();
}

void DirectionalLightComponent::Update()
{
}
