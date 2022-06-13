#include "MaterialEditorWindow.h"
#include <string>

MaterialEditorWindow::MaterialEditorWindow(std::string title, Transform* transform) :
    shininess{ 0 }
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
        std::vector<Mesh>* meshes = transform->getSceneObject()->getModel()->getMeshes();
        if (meshes != nullptr)
        {
            if (ImGui::CollapsingHeader("All Meshes", ImGuiTreeNodeFlags_None))
            {
                glm::vec4 c = { meshes->at(0).color->vec4 };
                ImVec4 color = ImVec4(c.x, c.y, c.z, c.w);

                if (ImGui::BeginTabBar("Draw type", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("Color"))
                    {
                        static bool alpha_preview = true;
                        static bool alpha_half_preview = false;
                        static bool drag_and_drop = true;
                        static bool options_menu = true;
                        static bool hdr = false;
                        static bool alpha = true;
                        static bool alpha_bar = true;
                        static bool side_preview = true;
                        static bool ref_color = false;
                        static int display_mode = 0;
                        static int picker_mode = 0;
                        ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
                        ImGuiColorEditFlags flags = misc_flags;

                        if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
                        if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
                        if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
                        if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
                        if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
                        if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
                        if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
                        if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
                        if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
                        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, NULL);
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Material"))
                    {
                        ImGui::Text("Material item");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Texture"))
                    {
                        ImGui::Text("Texture item");
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                float shininess{ meshes->at(0).shininess };
                ImGui::DragFloat("shininess", &shininess, 0.1f, 0.0f, 256.0f, "%.1f", ImGuiSliderFlags_None);
                for (auto& mesh : *meshes)
                {
                    mesh.shininess = shininess;
                    mesh.color->vec4 = glm::vec4(color.x, color.y, color.z, color.w);
                }
            }
            if (ImGui::CollapsingHeader("Single mesh", ImGuiTreeNodeFlags_None))
            {
                for (int i = 0; i < meshes->size(); i++)
                {
                    if (ImGui::CollapsingHeader(("Mesh" + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_None))
                    {
                        if (ImGui::BeginTabBar("Draw type", ImGuiTabBarFlags_None))
                        {
                            if (ImGui::BeginTabItem("Color"))
                            {
                                ImGui::Text("Color item");
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Material"))
                            {
                                ImGui::Text("Material item");
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Texture"))
                            {
                                ImGui::Text("Texture item");
                                ImGui::EndTabItem();
                            }
                            ImGui::EndTabBar();
                        }
                        ImGui::DragFloat("shininess", &(meshes->at(i).shininess), 0.1f, 0.0f, 256.0f, "%.1f", ImGuiSliderFlags_None);
                    }
                }
            }
        }
    }

    ImGui::End();
}

void MaterialEditorWindow::readValues()
{
}

void MaterialEditorWindow::applyValues()
{

}
