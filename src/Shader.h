#pragma once

#include <string>
#include <glm.hpp>

#include <glad/glad.h>

#include "helpers/RootDir.h"


class Shader
{
public:
    static Shader* lambert;
    static Shader* simplest;
    static Shader* texturedLambert;
    static Shader* pink;
    static void Shader::initShaders();

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setVec4(const std::string& name, glm::vec4 value) const;

    void setVertexAttrib(const std::string& name, float* value);

    unsigned int getID() const;

    void disableVertexAttrib(const std::string& name) {
        GLuint loc = glGetAttribLocation(ID, name.c_str());
        glDisableVertexAttribArray(loc);
    }

private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type);

    unsigned int ID;
};