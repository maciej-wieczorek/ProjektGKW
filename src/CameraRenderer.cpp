#include "CameraRenderer.h"

CameraRenderer::CameraRenderer(GLFWwindow* window, CameraComponent* camera, Scene* scene) :
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

    /*glm::mat4 V = camera->GetViewMatrix();

    glm::mat4 P = glm::perspective(glm::radians(camera->Zoom), (float)frame_width / (float)frame_height, 0.1f, 100.0f); //TODO: move clipping values to camera
    */

    glm::mat4 V = camera->getViewMatrix();
    glm::mat4 P = camera->getPerspectiveMatrix((float)frame_width / (float)frame_height);

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
    Shader* shader = object->getShader();
    shader->use();

    shader->setVec3("viewPos", camera->Position);

    glm::mat4 M = object->getTransform()->getMatrix();

    shader->setMat4("P", P); //TODO: change to work with pointer (glm::f32*)
    shader->setMat4("V", V);
    shader->setMat4("M", M);

    object->getModel()->draw(*shader);
}
