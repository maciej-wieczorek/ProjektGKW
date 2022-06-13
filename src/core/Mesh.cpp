#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, DrawType drawType) :
    vertices{ vertices },
    indices{ indices },
    drawType{ drawType }
{
    setupMesh();
}

void Mesh::draw(Shader& shader, ShadingInfo& shadingInfo)
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

    shader.setFloat("shininess", shadingInfo.shininess);
    //------------------------------------------------------------------------------------

    switch (drawType)
    {
    case Mesh::DrawType::Color:
        shader.setVec3("color", shadingInfo.color.getVec3());
        shader.setFloat("alpha", shadingInfo.color.vec4.w);
        break;
    case Mesh::DrawType::Material:
        shader.setVec3("material.ambient", shadingInfo.material->ambient);
        shader.setVec3("material.diffuse", shadingInfo.material->diffuse);
        shader.setVec3("material.specular", shadingInfo.material->specular);
        break;
    case Mesh::DrawType::Texture:
        glActiveTexture(GL_TEXTURE0); // active texture unit before binding
        shader.setInt("textureMaterial.diffuse", 0); // set the sampler to the correct texture unit
        glBindTexture(GL_TEXTURE_2D, shadingInfo.texture->textureID); // bind the texture
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