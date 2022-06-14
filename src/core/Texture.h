#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>

class Texture {
public:
	static std::vector<Texture*> textures;

	static void initTextures(std::string directory);

	GLuint getID();
	std::string name;
	
	Texture(std::string filePath, std::string name = "");
private:
	std::string filePath;
	bool isLoaded;
	GLuint textureID;

	void loadTexture();
};