#pragma once

#include <glad/glad.h>

#include "../Material.h"
#include "../Texture.h"
#include "../types/Color.h"

class TexturedMaterial : Material {
public:
	TexturedMaterial(Texture* texture);
	void setUniforms();
private:
	Texture* texture;
};