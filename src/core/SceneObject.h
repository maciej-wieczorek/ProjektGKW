#pragma once

#include <forward_list>
#include <string>

#include "types/Transform.h"
#include "ComponentScript.h"
#include "Mesh.h"
#include "Material.h"

class Transform;

class SceneObject {
public:
	Mesh* mesh;
	Transform* transform;
	Material* material;

	SceneObject(std::string name, SceneObject* parent);
	SceneObject(std::string name);
	SceneObject();

	unsigned int getId();

	std::string getName();
	Transform* getTransform();
	Mesh* getMesh();
	void setMesh(Mesh* mesh);
	Material* getMaterial();

	void Update();
private:
	unsigned int id;
	std::string name;
	std::forward_list<ComponentScript*> components;
};