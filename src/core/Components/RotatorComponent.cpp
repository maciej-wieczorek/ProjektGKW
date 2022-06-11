#include "RotatorComponent.h"

void RotatorComponent::Update()
{
	/*Vector3 movement = Vector3::right * FrameStats::getDeltaTime() * speed * dir;
	Vector3 finalPosition = sceneObject->transform->getPosition(false) + movement;
	if (finalPosition.x < minx || finalPosition.x > maxx) {
		movement *= -1;
		dir = -dir;
		finalPosition = sceneObject->transform->getPosition(false) + movement;
	}
	//sceneObject->transform->move(movement, false);
	//sceneObject->transform->moveTo(finalPosition, false);*/

	sceneObject->transform->move(Vector3::right * FrameStats::getDeltaTime(), false);
}
