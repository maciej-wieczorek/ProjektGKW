#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ApplicationWindow.h";
#include "ImGuiHandler.h"
#include "GUI/TransformEditorWindow.h"
#include "Camera.h"
#include "CameraRenderer.h"
#include "Scene.h"

const char* GLSL_VERSION = "#version 330";

void loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

int main() {
    ApplicationWindow mainWindow(1280, 720, "Projekt GKiW");
    mainWindow.setActive();
    loadGlad();
    ImGuiHandler::init();

    ImGuiHandler::setContext(mainWindow.getWindow(), GLSL_VERSION);


    Scene scene;
    SceneObject cubeObj("cube1");
    //cubeObj.setMesh(Mesh::cube);
    cubeObj.getMesh()->vertices = Cube::vertices;
    cubeObj.getMesh()->normals = Cube::normals;
    cubeObj.getMesh()->colors = Cube::colors;
    cubeObj.getMesh()->verticesCount = Cube::verticesCount;
    scene.setRootObject(&cubeObj);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    CameraRenderer cameraRenderer(mainWindow.getWindow(), &camera, &scene);

    float value = 1;
    TransformEditorWindow transformEditorWindow = TransformEditorWindow("Transform", cubeObj.getTransform());

    while (!mainWindow.shouldClose()) {
        mainWindow.beginFrame();
        ImGuiHandler::startFrame();

        transformEditorWindow.draw();

        ImGuiHandler::render();

        cameraRenderer.render();

        ImGuiHandler::endFrame();
        mainWindow.endFrame();
    }

    ImGuiHandler::close();
    mainWindow.close();

    return 0;
}