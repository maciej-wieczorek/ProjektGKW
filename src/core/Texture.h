#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>

class Texture {
public:
	static Texture* bricks;
	static Texture* none;

	static void initTextures();

	GLuint textureID;
	Texture(std::string filePath);
private:
	std::string filePath;

	void loadTexture();
};