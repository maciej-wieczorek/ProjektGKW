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

        if (ImGui::BeginTabBar("Draw type", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Color"))
            {
                shadingInfo.drawType = DrawType::Color;

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
                shadingInfo.drawType = DrawType::Material;
                ImGui::Text("Material item");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Texture"))
            {
                shadingInfo.drawType = DrawType::Texture;
                ImGui::Text("Texture item");
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
