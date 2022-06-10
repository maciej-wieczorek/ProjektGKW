#pragma once

#include <forward_list>
#include <string>

#include "types/Transform.h"
#include "ComponentScript.h"
#include "Mesh.h"
#include "Material.h"

class Transform;
class ComponentScript;

class SceneObject {
public:
	static unsigned int getNextId();

	Transform* transform;
	Material* material;

	unsigned int VBO[2]; //[vertices, normals]
	unsigned int VAO;

	SceneObject(std::string name, SceneObject* parent, Mesh* mesh, Material* material);
	SceneObject(std::string name, SceneObject* parent);
	SceneObject(std::string name);
	SceneObject();

	unsigned int getId();

	std::string getName();
	Transform* getTransform();
	Mesh* getMesh();
	void setMesh(Mesh* mesh);
	Material* getMaterial();

	void addComponent(ComponentScript* component);

	void Update();
private:
	static unsigned int nextId;

	unsigned int id;
	std::string name;
	std::forward_list<ComponentScript*> components;
	Mesh* mesh;

	void SetBuffers();
};