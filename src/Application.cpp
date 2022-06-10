#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ApplicationWindow.h";
#include "ImGuiHandler.h"
#include "GUI/TransformEditorWindow.h"
#include "GUI/HierarchyEditorWindow.h"
#include "Camera.h"
#include "CameraRenderer.h"
#include "Scene.h"
#include "Shader.h"
#include "Components/RotatorComponent.h"
#include "core/FrameStats.h"


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

    Mesh::initMeshes();
    Shader::initShaders();

    Scene scene;
    SceneObject cubeObj("root");
    cubeObj.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    scene.setRootObject(&cubeObj);

    SceneObject cube2("cube2", &cubeObj, Mesh::cube, new Material(Shader::lambert));
    SceneObject cube3("cube3", &cubeObj, Mesh::cube, new Material(Shader::lambert));
    SceneObject cube4("cube4", &cubeObj, Mesh::cube, new Material(Shader::lambert));
    SceneObject cube5("cube5", &cube3, Mesh::cube, new Material(Shader::lambert));
    SceneObject cube6("cube6", &cube3, Mesh::cube, new Material(Shader::lambert));

    SceneObject teapot1("teapot", &cube5, Mesh::teapot, new Material(Shader::lambert));

    ComponentScript* rotator = (ComponentScript*)(new RotatorComponent());
    cube5.addComponent(rotator);

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
    CameraRenderer cameraRenderer(mainWindow.getWindow(), &camera, &scene);

    float value = 1;
    HierarchyEditorWindow hierarchyEditorWindow = HierarchyEditorWindow("Hierarchy", scene.getRootObject()->transform);
    TransformEditorWindow transformEditorWindow = TransformEditorWindow("Transform", cubeObj.getTransform());

    while (!mainWindow.shouldClose()) {
        //PRE-UPDATE

        FrameStats::registerFrame();

        //UPDATE

        scene.Update();
        mainWindow.setTitle("Projekt GKW    FPS: " + std::to_string(FrameStats::getCurrentFrameRate()));

        //RENDER

        mainWindow.beginFrame();
        ImGuiHandler::startFrame();

        hierarchyEditorWindow.draw();
        transformEditorWindow.bindTransform(hierarchyEditorWindow.getSelected());
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

void init() {

}