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
    Color backgroundColor = scene->getbackgroundColor();
    glClearColor(backgroundColor.vec4.r, backgroundColor.vec4.g, backgroundColor.vec4.b, backgroundColor.vec4.a);
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
    if (shader == nullptr)
        return;

    shader->use();
    Vector3 position = camera->getPosition();
    shader->setVec3("viewPos", position.toVec3());

    glm::mat4 M = object->getTransform()->getMatrix();

    shader->setMat4("P", P); //TODO: change to work with pointer (glm::f32*)
    shader->setMat4("V", V);
    shader->setMat4("M", M);

    DirectionalLightS dl;
    dl.direction = scene->getDirectionalLight(0)->getDirection();
    dl.ambient = scene->getDirectionalLight(0)->ambient;
    dl.specular = scene->getDirectionalLight(0)->specular;
    dl.diffuse = scene->getDirectionalLight(0)->diffuse;

    std::vector<PointLightS> pls;
    for (int i = 0; i < scene->getPointLightsCount(); ++i) {
        pls.push_back({
            scene->getPointLight(i)->getPosition(),
            scene->getPointLight(i)->ambient,
            scene->getPointLight(i)->diffuse,
            scene->getPointLight(i)->specular,
            scene->getPointLight(i)->constant,
            scene->getPointLight(i)->linear,
            scene->getPointLight(i)->quadratic,
            });
    }
    object->getModel()->draw(*shader, object->getShadingInfo(), dl, pls);
}
