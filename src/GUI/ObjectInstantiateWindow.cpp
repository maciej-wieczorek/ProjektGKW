#include "ObjectInstantiateWindow.h"

ObjectInstantiateWindow::ObjectInstantiateWindow(std::string title, Scene* scene, HierarchyEditorWindow* hierarchyWindow, std::vector<std::pair<Model*, std::string>> models)
{
    this->title = title;
    this->scene = scene;
    this->hierarchyWindow = hierarchyWindow;
    setModelsList(models);
}

ObjectInstantiateWindow::ObjectInstantiateWindow(std::string title, Scene* scene, HierarchyEditorWindow* hierarchyWindow) : ObjectInstantiateWindow(title, scene, hierarchyWindow, std::vector<std::pair<Model*, std::string>>())
{
}

void ObjectInstantiateWindow::setModelsList(std::vector<std::pair<Model*, std::string>> models)
{
    this->models = models;
}

void ObjectInstantiateWindow::draw()
{
    ImGui::Begin(title.c_str());

    ImGui::Text("Nazwa: "); ImGui::SameLine();
    ImGui::InputText(" ##name", name, IM_ARRAYSIZE(name));

    ImGui::Text("Ustaw: "); ImGui::SameLine();
    ImGui::RadioButton("na srodku pokoju", &spawnPlace, SpawnPlace::PLACE_CENTER); ImGui::SameLine();
    ImGui::RadioButton("przy zaznaczonym obiekcie", &spawnPlace, SpawnPlace::PLACE_SELECTED);
    ImGui::RadioButton("w punkie: ", &spawnPlace, SpawnPlace::PLACE_CUSTOM); ImGui::SameLine();
    ImGui::DragFloat3(" ##customPosition", customPosition, 0.1, -FLT_MAX, +FLT_MAX);

    ImGui::Text("Jako: "); ImGui::SameLine();
    ImGui::RadioButton("niezalezny obiekt", &spawnMode, SpawnMode::MODE_FREE); ImGui::SameLine();
    ImGui::RadioButton("potomek zaznaczonego", &spawnMode, SpawnMode::MODE_CHILD);

    for (unsigned int i = 0; i < models.size(); ++i) {
        if (ImGui::Button(models[i].second.c_str())) {
            instantiateObject(i);
        }
    }

    ImGui::End();
}

void ObjectInstantiateWindow::instantiateObject(int modelId)
{
    if (scene == NULL || hierarchyWindow == NULL) {
        return;
    }

    Transform* selected = hierarchyWindow->getSelected();

    Vector3 position(0, 0, 0);
    if (spawnPlace == SpawnPlace::PLACE_SELECTED && selected != NULL) {
        position = selected->getPosition(Transform::Space::GLOBAL);
    }
    else if (spawnPlace == SpawnPlace::PLACE_CUSTOM) {
        position = Vector3(customPosition[0], customPosition[1], customPosition[2]);
    }

    Transform* parent = scene->getRootObject()->transform;
    if (spawnMode == SpawnMode::MODE_CHILD && selected != NULL) {
        parent = selected;
    }
    
    std::string fullName = name;
    fullName += " [" + models[modelId].second + "]";
    SceneObject* newObject = new SceneObject(fullName, parent->getSceneObject());
    newObject->setModel(models[modelId].first);
    newObject->setShader(Shader::pink);

    newObject->transform->setPosition(position, Transform::Space::GLOBAL);
}
