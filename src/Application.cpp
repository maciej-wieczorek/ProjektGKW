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

    Shader::initShaders();

    Scene scene;
    SceneObject cubeObj("cube1");
    cubeObj.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    scene.setRootObject(&cubeObj);

    SceneObject cube2("cube2", &cubeObj);
    cube2.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    SceneObject cube3("cube3", &cubeObj);
    cube3.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    SceneObject cube4("cube4", &cubeObj);
    cube4.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    SceneObject cube5("cube5", &cube3);
    cube5.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));
    SceneObject cube6("cube6", &cube3);
    cube6.setMesh(new Mesh(Cube::vertices, Cube::normals, Cube::colors, Cube::verticesCount));

    SceneObject teapot1("teapot", &cube5);
    teapot1.setMesh(new Mesh(Teapot::vertices, Teapot::normals, Teapot::colors, Teapot::verticesCount));

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
    CameraRenderer cameraRenderer(mainWindow.getWindow(), &camera, &scene);

    float value = 1;
    HierarchyEditorWindow hierarchyEditorWindow = HierarchyEditorWindow("Hierarchy", scene.getRootObject()->transform);
    TransformEditorWindow transformEditorWindow = TransformEditorWindow("Transform", cubeObj.getTransform());

    while (!mainWindow.shouldClose()) {
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