#pragma once

#include <vector>;

#include "Shader.h"
#include "Mesh.h"

class Material {
public:
	Shader* shader;

	Material(Shader* shader);
	Material();

	virtual void setUniforms() = 0;
};