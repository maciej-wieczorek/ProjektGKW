#include <iostream>
#include <fstream>

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
#include "Components/CameraComponent.h"
#include "core/FrameStats.h"
#include "core/Materials/ColoredMaterial.h"
#include "core/Materials/TexturedMaterial.h"
#include "types/Color.h"


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

    stbi_set_flip_vertically_on_load(true);

    Shader::initShaders();
    // Texture::initTextures();

    Model chairModel(ROOT_DIR "res/models/chair/chair.obj");

<<<<<<< HEAD
    //SceneObject cube2("teapot1", &cubeObj, Mesh::teapot, (Material*) new TexturedMaterial(new Texture("E:/bricks.png")));
    SceneObject cube3("cube3", &cubeObj, Mesh::cube, (Material*) new TexturedMaterial(Texture::bricks));
    SceneObject cameraObj("camera", &cubeObj, NULL, NULL);
    cameraObj.transform->moveTo(Vector3(0, 0, 8));
    //SceneObject cube5("cube5", &cube3, Mesh::cube, (Material*) new ColoredMaterial(Color::red));
    //SceneObject cube6("cube6", &cube3, Mesh::cube, (Material*) new ColoredMaterial(Color::blue));
=======
    Scene scene;
    SceneObject chair1("root");
    chair1.setModel(&chairModel);
    chair1.setShader(Shader::pink);
    scene.setRootObject(&chair1);
>>>>>>> 14f8033acba621edb5c13a0e556894b6a6b81baf

    SceneObject chair2("chair2", &chair1);
    chair2.setModel(&chairModel);
    chair2.setShader(Shader::pink);

    CameraComponent* myCamera = new CameraComponent();
    cameraObj.addComponent((ComponentScript*)myCamera);

    //ComponentScript* rotator = (ComponentScript*)(new RotatorComponent());
    //cube5.addComponent(rotator);

    //Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
    //CameraRenderer cameraRenderer(mainWindow.getWindow(), &camera, &scene);
    CameraRenderer cameraRenderer(mainWindow.getWindow(), myCamera, &scene);

    float value = 1;
    HierarchyEditorWindow hierarchyEditorWindow = HierarchyEditorWindow("Hierarchy", scene.getRootObject()->transform);
    TransformEditorWindow transformEditorWindow = TransformEditorWindow("Transform", chair1.getTransform());

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