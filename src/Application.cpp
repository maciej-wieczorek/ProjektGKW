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

    Scene scene;
    SceneObject chair1("root");
    chair1.setModel(&chairModel);
    chair1.setShader(Shader::pink);
    scene.setRootObject(&chair1);

    SceneObject chair2("camera", &chair1);
    chair2.setModel(&chairModel);
    chair2.setShader(Shader::pink);

    CameraComponent* myCamera = new CameraComponent();
    chair2.addComponent((ComponentScript*)myCamera);
    chair2.transform->setPosition(Vector3(0, 0, 5), Transform::Space::GLOBAL);

    SceneObject chair3("chair3", &chair1);
    chair3.setModel(&chairModel);
    chair3.setShader(Shader::pink);

    SceneObject chair4("chair4", &chair3);
    chair4.setModel(&chairModel);
    chair4.setShader(Shader::pink);

    SceneObject chair5("chair5", &chair3);
    chair5.setModel(&chairModel);
    chair5.setShader(Shader::pink);

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

        /*/
        bool show_demo_window = true;
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        /*/

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