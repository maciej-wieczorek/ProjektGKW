#pragma once

#include "Shader.h"

class Material {
public:
	Shader* shader;

	Material(Shader* shader);
	Material();
};