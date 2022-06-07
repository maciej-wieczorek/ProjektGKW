#include "HierarchyEditorWindow.h"

HierarchyEditorWindow::HierarchyEditorWindow(std::string title, Transform* root)
{
    this->title = title;
    this->root = root;
}

HierarchyEditorWindow::HierarchyEditorWindow(std::string title) : HierarchyEditorWindow(title, NULL)
{
}

void HierarchyEditorWindow::bindRoot(Transform* root)
{
    this->root = root;
}

void HierarchyEditorWindow::draw()
{
    ImGui::Begin(title.c_str());

    Transform* newSelection = drawHierarchy(root);

    if (newSelection != NULL) {
        selected = newSelection;
    }

    if (selected != NULL) {
        ImGui::Text("Selected: %s", selected->getSceneObject()->getName().c_str());
    }

    ImGui::End();
}

Transform* HierarchyEditorWindow::getSelected()
{
    return selected;
}

Transform* HierarchyEditorWindow::drawHierarchy(Transform* transform)
{
    if (transform != NULL)
    {
        if (ImGui::TreeNodeEx(transform->getSceneObject()->getName().c_str()))
        {
            ImGui::SameLine();
            if (ImGui::SmallButton("Select")) {
                ImGui::TreePop();
                return transform;
            }
            for (int i = 0; i < transform->getChildrenCount(); ++i) {
                Transform* selectedChild = drawHierarchy(transform->getChild(i));
                if (selectedChild != NULL) {
                    ImGui::TreePop();
                    return selectedChild;
                }
            }
            ImGui::TreePop();
        }
    }
    return NULL;
}
