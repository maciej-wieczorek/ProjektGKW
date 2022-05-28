#pragma once

#include <string>
#include <glm.hpp>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;

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