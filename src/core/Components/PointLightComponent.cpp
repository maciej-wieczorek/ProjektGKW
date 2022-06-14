#include "PointLightComponent.h"

glm::vec3 PointLightComponent::getPosition()
{
	return sceneObject->transform->getPosition(Transform::Space::GLOBAL).toVec3();
}

void PointLightComponent::Update()
{
}
