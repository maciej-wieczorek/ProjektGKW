#pragma once

#include <string>
#include <stack>
#include <vector>

#include "SceneObject.h"
#include "types/Color.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/PointLightComponent.h"

class Scene {
public:
	unsigned int getNextId();

	Scene(std::string name, unsigned int id);
	Scene(std::string name);
	Scene();

	SceneObject* getRootObject();
	void setRootObject(SceneObject* root);

	void addDirectionalLight(DirectionalLightComponent* light);
	void addPointLight(PointLightComponent* light);

	int getDirectionalsLightsCount();
	int getPointLightsCount();

	DirectionalLightComponent* getDirectionalLight(int index);
	PointLightComponent* getPointLight(int index);

	void setBackgroundColor(Color color);
	Color getbackgroundColor();

	void Update();
private:
	unsigned int nextId = 0;

	unsigned int id;
	std::string name;
	SceneObject* sceneRoot;
	std::vector<DirectionalLightComponent*> directionalLights;
	std::vector<PointLightComponent*> pointLights;
	Color backgroundColor = Color::black;
};
