#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Color.h"
#include "Material.h"
#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    enum class DrawType
    {
        Color = 0, Material, Texture
    };


    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, DrawType drawType = DrawType::Color);

    void draw(Shader& shader);

    // mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Color* color;
    Material* material;
    Texture* texture;

    DrawType drawType;

    unsigned int VAO;

private:
    void setupMesh();

    unsigned int VBO, EBO;
};