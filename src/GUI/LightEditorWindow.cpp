#include "LightEditorWindow.h"
#include <string>

LightEditorWindow::LightEditorWindow(std::string title)
{
    this->title = title;
}

void LightEditorWindow::bindDirectional(DirectionalLightComponent* light)
{
    pointLight = NULL;
    directionalLight = light;
}

void LightEditorWindow::bindPoint(PointLightComponent* light)
{
    directionalLight = NULL;
    pointLight = light;
}

void LightEditorWindow::draw()
{
    ImGui::Begin(title.c_str());

    if (this->directionalLight != NULL || this->pointLight != NULL)
    {
        readValues();
        if (ImGui::BeginTabBar("Light", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Ambient"))
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
                ImGui::ColorPicker4("Ambient", (float*)&ambient, flags, NULL);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Diffuse"))
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
                ImGui::ColorPicker4("Ambient", (float*)&diffuse, flags, NULL);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Specular"))
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
                ImGui::ColorPicker4("Ambient", (float*)&specular, flags, NULL);
                ImGui::EndTabItem();
            }
            if (pointLight != NULL && ImGui::BeginTabItem("Material"))
            {
                ImGui::DragFloat("constatnt", &constant, 0.05f, -FLT_MAX, +FLT_MAX);
                ImGui::DragFloat("linear", &linear, 0.05f, -FLT_MAX, +FLT_MAX);
                ImGui::DragFloat("quadratic", &quadratic, 0.05f, -FLT_MAX, +FLT_MAX);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    applyValues();
    ImGui::End();
}

void LightEditorWindow::readValues()
{
    if (directionalLight != NULL) {
        ambient = ImColor(directionalLight->ambient.x, directionalLight->ambient.y, directionalLight->ambient.z, 1.0f);
        diffuse = ImColor(directionalLight->diffuse.x, directionalLight->diffuse.y, directionalLight->diffuse.z, 1.0f);
        specular = ImColor(directionalLight->specular.x, directionalLight->specular.y, directionalLight->specular.z, 1.0f);
    }
    else if (pointLight != NULL) {
        ambient = ImColor(pointLight->ambient.x, pointLight->ambient.y, pointLight->ambient.z, 1.0f);
        diffuse = ImColor(pointLight->diffuse.x, pointLight->diffuse.y, pointLight->diffuse.z, 1.0f);
        specular = ImColor(pointLight->specular.x, pointLight->specular.y, pointLight->specular.z, 1.0f);

        constant = pointLight->constant;
        linear = pointLight->linear;
        quadratic = pointLight->quadratic;
    }
}

void LightEditorWindow::applyValues()
{
    if (directionalLight != NULL) {
        directionalLight->ambient = glm::vec3(ambient.x, ambient.y, ambient.z);
        directionalLight->diffuse = glm::vec3(diffuse.x, diffuse.y, diffuse.z);
        directionalLight->specular = glm::vec3(specular.x, specular.y, specular.z);
    }
    else if (pointLight != NULL) {
        pointLight->ambient = glm::vec3(ambient.x, ambient.y, ambient.z);
        pointLight->diffuse = glm::vec3(diffuse.x, diffuse.y, diffuse.z);
        pointLight->specular = glm::vec3(specular.x, specular.y, specular.z);

        pointLight->constant = constant;
        pointLight->linear = linear;
        pointLight->quadratic = quadratic;
    }
}
