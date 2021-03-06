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

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    Transform* newSelection = drawHierarchy(root);

    if (newSelection != NULL) {
        selected = newSelection;
    }

    if (selected != NULL) {
        ImGui::Text("Selected: %s", selected->getSceneObject()->getName().c_str());
        ImGui::Text("forward: %s", selected->getForward(Transform::Space::GLOBAL).toString().c_str());
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
        Transform* toReturn = NULL;
        
        std::string treeLabel = transform->getSceneObject()->getName();
        treeLabel += "##" + transform->getSceneObject()->getId();
        std::string buttonLabel = "Select##";
        buttonLabel += transform->getSceneObject()->getId();

        bool open = ImGui::TreeNode(transform->getSceneObject()->getName().c_str());
        ImGui::SameLine();
        if (ImGui::SmallButton(buttonLabel.c_str())) {
            toReturn = transform;
        }
        if (selected == transform) {
            ImGui::SameLine();
            if (ImGui::SmallButton((std::string("remove##") + std::to_string(transform->getSceneObject()->getId())).c_str())) {
                transform->setParent(NULL);
            }
        }
        if (open)
        {
            for (int i = 0; i < transform->getChildrenCount(); ++i) {
                Transform* selectedChild = drawHierarchy(transform->getChild(i));
                if (selectedChild != NULL) {
                    toReturn = selectedChild;
                }
            }
            ImGui::TreePop();
        }
        return toReturn;
    }
    return NULL;
}
