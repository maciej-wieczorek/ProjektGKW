#include "TransformEditorWindow.h"

TransformEditorWindow::TransformEditorWindow(std::string title, Vector3* position)
{
    this->title = title;
    this->position = position;
    this->positionS = new float*[3];
    this->positionS[0] = &(position->x);
    this->positionS[1] = &(position->y);
    this->positionS[2] = &(position->z);
}

void TransformEditorWindow::draw()
{
    ImGui::Begin(title.c_str());
    //ImGui::SliderFloat3("position", *positionS, -2, 2);
    //ImGui::InputFloat3("position", *positionS);
    ImGui::DragFloat3("position", *positionS, 0.1, -5, 5);
    ImGui::End();
}