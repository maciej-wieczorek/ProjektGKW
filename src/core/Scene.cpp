#include "Scene.h"

Scene::Scene(std::string name, unsigned int id) {
    this->name = name;
    this->id = id;
}

Scene::Scene(std::string name) : Scene(name, 0) {//TODO: change '0' to some id generator

}

Scene::Scene() : Scene("Scene") {//TODO add next numbers to name

}

SceneObject* Scene::getRootObject()
{
    return sceneRoot;
}

void Scene::setRootObject(SceneObject* root)
{
    sceneRoot = root;
}

void Scene::addDirectionalLight(DirectionalLightComponent* light)
{
    directionalLights.push_back(light);
}

void Scene::addPointLight(PointLightComponent* light)
{
    pointLights.push_back(light);
}

int Scene::getDirectionalsLightsCount()
{
    return directionalLights.size();
}

int Scene::getPointLightsCount()
{
    return pointLights.size();
}

DirectionalLightComponent* Scene::getDirectionalLight(int index)
{
    if (index < directionalLights.size()) {
        return directionalLights[index];
    }
    return NULL;
}

PointLightComponent* Scene::getPointLight(int index)
{
    if (index < pointLights.size()) {
        return pointLights[index];
    }
    return NULL;
}

void Scene::setBackgroundColor(Color color)
{
    backgroundColor = color;
}

Color Scene::getbackgroundColor()
{
    return backgroundColor;
}

void Scene::Update()
{
    std::stack<SceneObject*> updateStack;
    updateStack.push(getRootObject());

    SceneObject* object;
    while (!updateStack.empty()) {
        object = updateStack.top();
        updateStack.pop();
        for (auto& child : *(object->getTransform()->getChildren())) {
            updateStack.push(child->getSceneObject());
        }
        object->Update();
    }
}

unsigned int Scene::getNextId() {
    return nextId++;
}