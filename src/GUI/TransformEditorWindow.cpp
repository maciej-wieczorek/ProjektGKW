#include "TransformEditorWindow.h"

TransformEditorWindow::TransformEditorWindow(std::string title, Transform* transform)
{
    this->title = title;
    
    bindTransform(transform);
}

TransformEditorWindow::TransformEditorWindow(std::string title) : TransformEditorWindow(title, NULL)
{
}

void TransformEditorWindow::bindTransform(Transform* transform)
{
    if (transform == this->transform) {
        return;
    }

    this->transform = transform;

    if (transform == NULL) {
        return;
    }

    readValues();
}

void TransformEditorWindow::draw()
{
    ImGui::Begin(title.c_str());

    if (this->transform != NULL) {

        std::string spaceLabel = (space == Transform::Space::GLOBAL) ? "Global" : "Local";
        if (ImGui::Button(spaceLabel.c_str())) {
            space = (space == Transform::Space::GLOBAL) ? Transform::Space::LOCAL : Transform::Space::GLOBAL;
            readValues();
        }

        //readValues();

        ImGui::DragFloat3("position", position, 0.1, -FLT_MAX, +FLT_MAX);
        ImGui::DragFloat3("rotation", rotation, 1, -360, 360);
        ImGui::DragFloat3("scale", scale, 0.1, -FLT_MAX, +FLT_MAX);

        applyValues();
    }
    
    ImGui::End();
}

void TransformEditorWindow::readValues()
{
    Vector3 pos = transform->getPosition(space);

    position[0] = pos.x;
    position[1] = pos.y;
    position[2] = pos.z;

    Vector3 rot = transform->getRotation(space).getEuler();

    rotation[0] = rot.x;
    rotation[1] = rot.y;
    rotation[2] = rot.z;

    Vector3 sca = transform->getScale(space);

    scale[0] = sca.x;
    scale[1] = sca.y;
    scale[2] = sca.z;
}

void TransformEditorWindow::applyValues()
{
    transform->setPosition(Vector3(position[0], position[1], position[2]), space);
    transform->setRotation(Quaternion(rotation[0], rotation[1], rotation[2]), space);
    transform->setScale(Vector3(scale[0], scale[1], scale[2]), space);
}
