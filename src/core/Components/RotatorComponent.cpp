#include "RotatorComponent.h"

void RotatorComponent::Update()
{
	sceneObject->transform->move(Vector3::right * FrameStats::getDeltaTime());
}
