#include "Material.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
}

Material::Material() : Material(Shader::pink)
{
}
