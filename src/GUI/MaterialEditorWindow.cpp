#include "MaterialEditorWindow.h"
#include <string>

MaterialEditorWindow::MaterialEditorWindow(std::string title, Transform* transform)
{
	this->title = title;
	bindTransform(transform);
}

void MaterialEditorWindow::bindTransform(Transform* transform)
{
	this->transform = transform;
}

void MaterialEditorWindow::draw()
{
    ImGui::Begin(title.c_str());

    if (this->transform != NULL)
    {
        ShadingInfo& shadingInfo = transform->getSceneObject()->getShadingInfo();


        glm::vec4& c = { shadingInfo.color.vec4 };
        ImVec4 color = ImVec4(c.x, c.y, c.z, c.w);
        int& item_current_idx_material = shadingInfo.materialIndex;
        int& item_current_idx_texture = shadingInfo.textureIndex;

        if (ImGui::BeginTabBar("Draw type", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Color"))
            {
                shadingInfo.drawType = DrawType::Color;
                ImGui::ColorPicker4("Color picker", (float*)&color, ImGuiColorEditFlags_None, NULL);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Material"))
            {
                shadingInfo.drawType = DrawType::Material;
                if (ImGui::BeginListBox("Materials"))
                {
                    for (int i = 0; i < Material::materials.size(); i++)
                    {
                        const bool is_selected = (item_current_idx_material == i);
                        if (ImGui::Selectable(Material::materials[i]->name.c_str(), is_selected))
                            item_current_idx_material = i;

                        if (is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                         
                    }
                ImGui::EndListBox();
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Texture"))
            {
                shadingInfo.drawType = DrawType::Texture;
                
                if (ImGui::BeginListBox("Textures"))
                {
                    for (int i = 0; i < Texture::textures.size(); i++)
                    {
                        const bool is_selected = (item_current_idx_texture == i);
                        if (ImGui::Selectable(Texture::textures[i]->name.c_str(), is_selected))
                            item_current_idx_texture = i;

                        if (is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }

                    }
                    ImGui::EndListBox();
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Shininess"))
            {
                ImGui::DragFloat("shininess", &shadingInfo.shininess, 0.1f, 0.0f, 256.0f, "%.1f", ImGuiSliderFlags_None);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        shadingInfo.color.vec4 = glm::vec4(color.x, color.y, color.z, color.w);
    }

    ImGui::End();
}

void MaterialEditorWindow::readValues()
{
}

void MaterialEditorWindow::applyValues()
{

}
