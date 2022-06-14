#include <filesystem>

#include "Texture.h"
#include "stb_image.h"
#include "helpers/RootDir.h"

namespace fs = std::filesystem;

std::vector<Texture*> Texture::textures{};

void Texture::initTextures(std::string directory){
	textures.push_back(new Texture(ROOT_DIR "res/textures/bricks.png", "bricks"));

    // scan directory for textures
    for (const auto& entry : fs::directory_iterator(directory))
    {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file())
        {
            int findExt = filenameStr.find_last_of(".");
            std::string ext = filenameStr.substr(findExt + 1);
            if (ext == "png" || ext == "jpg")
            {
                std::string name = filenameStr.substr(0, findExt);
                textures.push_back(new Texture(directory + filenameStr, name));
            }
        }
    }
}

GLuint Texture::getID()
{
    if (!isLoaded)
        loadTexture();
    return textureID;
}

Texture::Texture(std::string filePath, std::string name) :
    filePath{ filePath },
    isLoaded{ false },
    name{ name },
    textureID{ 0 }
{
}

void Texture::loadTexture()
{
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        isLoaded = true;
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }
}
