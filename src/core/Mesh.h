#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Color.h"
#include "Material.h"
#include "Texture.h"

#include "LightStructs.h"

enum class DrawType
{
    Color = 0, Material, Texture
};

struct ShadingInfo
{
    Color color;
    Material* material;
    Texture* texture;
    float shininess;
    DrawType drawType;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void draw(Shader& shader, ShadingInfo& shadingInfo, DirectionalLightS& directioanlLight, std::vector<PointLightS> pointLights);

    // mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO;

private:
    void setupMesh();

    unsigned int VBO, EBO;
};