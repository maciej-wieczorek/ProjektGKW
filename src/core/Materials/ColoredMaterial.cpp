#include "ColoredMaterial.h"

ColoredMaterial::ColoredMaterial(Color color) : Material(Shader::lambert)
{
	this->color = color;
}

void ColoredMaterial::setUniforms()
{
	shader->setVec4("color", color.vec4);
}
