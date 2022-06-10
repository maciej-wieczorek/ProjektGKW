#include "CameraRenderer.h"

CameraRenderer::CameraRenderer(GLFWwindow* window, Camera* camera, Scene* scene) :
    window{ window },
    camera{ camera },
    scene{ scene }
{
    glEnable(GL_DEPTH_TEST);
}

void CameraRenderer::render()
{
    int frame_width, frame_height;
    glfwGetFramebufferSize(window, &frame_width, &frame_height);

    glViewport(0, 0, frame_width, frame_height);
    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 V = camera->GetViewMatrix();

    glm::mat4 P = glm::perspective(glm::radians(camera->Zoom), (float)frame_width / (float)frame_height, 0.1f, 100.0f); //TODO: move clipping values to camera

    std::stack<SceneObject*> renderStack;
    renderStack.push(scene->getRootObject());

    SceneObject* object;
    while (!renderStack.empty()) {
        object = renderStack.top();
        renderStack.pop();
        for (auto& child : *(object->getTransform()->getChildren())) {
            renderStack.push(child->getSceneObject());
        }
        renderObject(V, P, object);
    }
}

void CameraRenderer::renderObject(const glm::mat4& V, const glm::mat4& P, SceneObject* object)
{  
    Shader* shader = object->material->shader;

    shader->use();

    glBindVertexArray(object->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, object->VBO[0]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


    /*glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object->getMesh()->verticesCount * 4, &(object->getMesh()->colors[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);*/

    glBindBuffer(GL_ARRAY_BUFFER, object->VBO[1]);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glm::mat4 M = object->getTransform()->getMatrix();

    shader->setMat4("P", P); //TODO: change to work with pointer (glm::f32*)
    shader->setMat4("V", V);
    shader->setMat4("M", M);

    glDrawArrays(GL_TRIANGLES, 0, object->getMesh()->verticesCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
