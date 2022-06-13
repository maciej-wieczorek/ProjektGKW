#include "Scene.h"

Scene::Scene(std::string name, unsigned int id) {
	this->name = name;
	this->id = id;
}

Scene::Scene(std::string name) : Scene(name, 0){//TODO: change '0' to some id generator

}

Scene::Scene() : Scene("Scene"){//TODO add next numbers to name

}

SceneObject* Scene::getRootObject()
{
	return sceneRoot;
}

void Scene::setRootObject(SceneObject* root)
{
	sceneRoot = root;
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