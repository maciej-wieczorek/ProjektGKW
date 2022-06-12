#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, DrawType drawType) :
    vertices{ vertices },
    indices{ indices },
    drawType{ drawType },
    texture{ nullptr },
    color{ new Color(1.0, 1.0, 1.0, 1.0) },
    material{ nullptr }
{
    setupMesh();
}

void Mesh::draw(Shader& shader)
{
    // TEMP HARD VALUES
    // ---------------------------------------------------------------------------------
    shader.setInt("drawType", static_cast<int>(drawType));
    shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.setVec3("dirLight.lightColor.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("dirLight.lightColor.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.setVec3("dirLight.lightColor.specular", glm::vec3(0.5f, 0.5f, 0.5f));

    shader.setInt("numOfPointLights", 1);
    shader.setVec3("pointLights[0].position", glm::vec3(0.5f, 0.3f, -0.3f));
    shader.setVec3("pointLights[0].lightColor.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("pointLights[0].lightColor.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader.setVec3("pointLights[0].lightColor.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09f);
    shader.setFloat("pointLights[0].quadratic", 0.032f);

    shader.setInt("numOfSpotLights", 0);

    shader.setFloat("shininess", 32.0f);
    //------------------------------------------------------------------------------------

    switch (drawType)
    {
    case Mesh::DrawType::Color:
        if (color)
            shader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
        break;
    case Mesh::DrawType::Material:
        if (material)
        {
            shader.setVec3("material.ambient", material->ambient);
            shader.setVec3("material.diffuse", material->diffuse);
            shader.setVec3("material.specular", material->specular);
        }
        break;
    case Mesh::DrawType::Texture:
        if (texture)
        {
            glActiveTexture(GL_TEXTURE0); // active texture unit before binding
            shader.setInt("textureMaterial.diffuse", 0); // set the sampler to the correct texture unit
            glBindTexture(GL_TEXTURE_2D, texture->textureID); // bind the texture
        }
        break;
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
}