#include "TexturedMaterial.h"

TexturedMaterial::TexturedMaterial(Texture* texture) : Material(Shader::texturedLambert)
{
	this->texture = texture;
}

void TexturedMaterial::setUniforms()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	shader->setInt("mtrx", 0);
	//glUniform1i(glGetUniformLocation(shader->getID(), "mtrx"), GL_TEXTURE0);
}
