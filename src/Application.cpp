#include <iostream>
#include <fstream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

#include "ApplicationWindow.h";
#include "ImGuiHandler.h"
#include "GUI/TransformEditorWindow.h"
#include "GUI/HierarchyEditorWindow.h"
#include "GUI/MaterialEditorWindow.h"
#include "GUI/ObjectInstantiateWindow.h"
#include "GUI/LightEditorWindow.h"
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
    // enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    ImGuiHandler::init();

    ImGuiHandler::setContext(mainWindow.getWindow(), GLSL_VERSION);

    stbi_set_flip_vertically_on_load(true);

    Shader::initShaders();

    Material::initMaterials();
    Texture::initTextures();

    Model chairModel(ROOT_DIR "res/models/chair.obj");
    Model bathModel(ROOT_DIR "res/models/bath.obj");
    Model aquariumModel(ROOT_DIR "res/models/aquarium.obj");
    Model bookcaseModel(ROOT_DIR "res/models/bookcase.obj");
    Model chestModel(ROOT_DIR "res/models/chest.obj");

    Scene scene;
    scene.setBackgroundColor(Color(0.1, 0.1, 0.1, 1));
    SceneObject root("root");
    scene.setRootObject(&root);

    SceneObject camera("camera", &root);
    CameraComponent* myCamera = new CameraComponent();
    camera.addComponent(dynamic_cast<ComponentScript*>(myCamera));
    camera.transform->setPosition(Vector3(0, 0, 15), Transform::Space::GLOBAL);

    SceneObject directionalLight("directional light", &root);
    directionalLight.transform->setRotation(Quaternion(155, 0, 10), Transform::Space::GLOBAL);
    SceneObject pointLight("point light", &root);

    DirectionalLightComponent* dirLightC = new DirectionalLightComponent();
    PointLightComponent* pointLightC = new PointLightComponent();

    directionalLight.addComponent(dirLightC);
    pointLight.addComponent(pointLightC);

    scene.addDirectionalLight(dirLightC);
    scene.addPointLight(pointLightC);

    CameraRenderer cameraRenderer(mainWindow.getWindow(), myCamera, &scene);

    float value = 1;
    HierarchyEditorWindow hierarchyEditorWindow = HierarchyEditorWindow("Scena", scene.getRootObject()->transform);
    TransformEditorWindow transformEditorWindow = TransformEditorWindow("Transform", root.getTransform());
    MaterialEditorWindow materialEditorWindow = MaterialEditorWindow("Material", root.getTransform());
    ObjectInstantiateWindow objectInstantiateWindow = ObjectInstantiateWindow("Meble", &scene,  &hierarchyEditorWindow);
    LightEditorWindow lightEditorWindow = LightEditorWindow("Oswietlenie");

    std::vector<std::pair<Model*, std::string>> models = {
        {&chairModel, "Krzeslo"},
        {&bathModel, "Wanna"},
        {&aquariumModel, "akwarium"},
        {&bookcaseModel, "biblioteczka"},
        {&chestModel, "skrzynia"}
    };
    objectInstantiateWindow.setModelsList(models);

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

        materialEditorWindow.bindTransform(hierarchyEditorWindow.getSelected());
        materialEditorWindow.draw();

        objectInstantiateWindow.draw();

        if (hierarchyEditorWindow.getSelected() != NULL) {
            if (hierarchyEditorWindow.getSelected()->getSceneObject()->getComponent<DirectionalLightComponent*>() != NULL) {
                lightEditorWindow.bindDirectional(hierarchyEditorWindow.getSelected()->getSceneObject()->getComponent<DirectionalLightComponent*>());
            }
            else if (hierarchyEditorWindow.getSelected()->getSceneObject()->getComponent<PointLightComponent*>() != NULL) {
                lightEditorWindow.bindPoint(hierarchyEditorWindow.getSelected()->getSceneObject()->getComponent<PointLightComponent*>());
            }
        }
        else {
            lightEditorWindow.bindDirectional(NULL);
        }
        lightEditorWindow.draw();


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