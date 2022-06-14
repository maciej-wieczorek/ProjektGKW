#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
    vertices{ vertices },
    indices{ indices }
{
    setupMesh();
}

void Mesh::draw(Shader& shader, ShadingInfo& shadingInfo, DirectionalLightS& directioanlLight, std::vector<PointLightS> pointLights)
{
    shader.setVec3("dirLight.direction", directioanlLight.direction);
    shader.setVec3("dirLight.lightColor.ambient", directioanlLight.ambient);
    shader.setVec3("dirLight.lightColor.diffuse", directioanlLight.diffuse);
    shader.setVec3("dirLight.lightColor.specular", directioanlLight.specular);

    shader.setInt("numOfPointLights", pointLights.size());
    for (int i = 0; i < pointLights.size(); ++i) {
        PointLightS pointLight = pointLights[i];
        std::string pref = "pointLights[" + std::to_string(i);

        shader.setVec3(pref + "].position", pointLight.position);
        shader.setVec3(pref + "].lightColor.ambient", pointLight.ambient);
        shader.setVec3(pref + "].lightColor.diffuse", pointLight.diffuse);
        shader.setVec3(pref + "].lightColor.specular", pointLight.specular);
        shader.setFloat(pref + "].constant", pointLight.constant);
        shader.setFloat(pref + "].linear", pointLight.linear);
        shader.setFloat(pref + "].quadratic", pointLight.quadratic);
    }
    // TEMP HARD VALUES
    // ---------------------------------------------------------------------------------
    /*shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.setVec3("dirLight.lightColor.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("dirLight.lightColor.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.setVec3("dirLight.lightColor.specular", glm::vec3(0.5f, 0.5f, 0.5f));*/

    /*shader.setInt("numOfPointLights", 1);
    shader.setVec3("pointLights[0].position", glm::vec3(0.5f, 0.3f, -0.3f));
    shader.setVec3("pointLights[0].lightColor.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("pointLights[0].lightColor.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader.setVec3("pointLights[0].lightColor.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09f);
    shader.setFloat("pointLights[0].quadratic", 0.032f);*/

    shader.setInt("numOfSpotLights", 0);
    //------------------------------------------------------------------------------------
    shader.setInt("drawType", static_cast<int>(shadingInfo.drawType));

    switch (shadingInfo.drawType)
    {
    case DrawType::Color:
    {
        shader.setVec3("color", shadingInfo.color.getVec3());
        shader.setFloat("alpha", shadingInfo.color.vec4.w);
        shader.setFloat("shininess", shadingInfo.shininess);
    }
    break;
    case DrawType::Material:
    {
        Material* material = Material::materials[shadingInfo.materialIndex];
        shader.setVec3("material.ambient", material->ambient);
        shader.setVec3("material.diffuse", material->diffuse);
        shader.setVec3("material.specular", material->specular);
    }
    break;
    case DrawType::Texture:
    {
        Texture* texture = Texture::textures[shadingInfo.textureIndex];
        int textureID = texture->getID(); // get texture id and load texture from file
        glActiveTexture(GL_TEXTURE0); // active texture unit before binding
        shader.setInt("textureMaterial.diffuse", 0); // set the sampler to the correct texture unit
        glBindTexture(GL_TEXTURE_2D, textureID); // bind the texture
        shader.setFloat("shininess", shadingInfo.shininess);
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