#include "RotatorComponent.h"

void RotatorComponent::Update()
{
	sceneObject->transform->move(Vector3(0.001, 0, 0));
}
