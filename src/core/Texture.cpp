#include "Texture.h"

Texture* Texture::bricks;

void Texture::initTextures(){
	bricks = new Texture("E:/bricks.png");
}

Texture::Texture(std::string filePath)
{
	this->filePath = filePath;
	loadTexture();
}

void Texture::loadTexture()
{
	glActiveTexture(GL_TEXTURE0);

	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filePath);
	std::cout << "loadtexture(): error " << error << std::endl;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
