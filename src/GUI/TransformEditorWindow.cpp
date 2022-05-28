#include "TransformEditorWindow.h"

TransformEditorWindow::TransformEditorWindow(std::string title, Transform* transform)
{
    this->title = title;
    this->position = new float* [3];
    this->rotation = new float* [3];
    this->scale = new float*[3];
    
    bindTransform(transform);
}

TransformEditorWindow::TransformEditorWindow(std::string title) : TransformEditorWindow(title, NULL)
{
}

void TransformEditorWindow::bindTransform(Transform* transform)
{
    this->transform = transform;

    if (transform == NULL) {
        return;
    }

    this->position[0] = &(this->transform->position.x);
    this->position[1] = &(this->transform->position.y);
    this->position[2] = &(this->transform->position.z);


    rotationEuler = this->transform->rotation.getEuler();
    this->rotation[0] = &(rotationEuler.x);
    this->rotation[1] = &(rotationEuler.y);
    this->rotation[2] = &(rotationEuler.z);

    this->scale[0] = &(this->transform->scale.x);
    this->scale[1] = &(this->transform->scale.y);
    this->scale[2] = &(this->transform->scale.z);
}

void TransformEditorWindow::draw()
{
    ImGui::Begin(title.c_str());

    if (this->transform != NULL) {
        ImGui::DragFloat3("position", *position, 0.1, -5, 5);

        ImGui::DragFloat3("rotation", *rotation, 1, -360, 360);
        transform->rotation.setEuler(*rotation[0], *rotation[1], *rotation[2]);

        ImGui::DragFloat3("scale", *scale, 0.1, -5, 5);
    }
    
    ImGui::End();
}