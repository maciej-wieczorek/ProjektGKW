/*#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "helpers/RootDir.h"

#include "CameraRenderer.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"

// GL 3.0 + GLSL 130
const char* GLSL_VERSION = "#version 330";

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

const float PI = 3.141592653589793f;

//object properties, TMP
float speed_x, speed_y;
float pos_x, pos_y, pos_z;
float rot_x, rot_y, rot_z;
float scale_x = 1, scale_y = 1, scale_z = 1;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    speed_x = 0.f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        speed_x = PI;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        speed_x = -PI;
}

GLFWwindow* initWindow() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ProjektGKW", NULL, NULL);
    if (window == NULL)
        exit(1);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return window;
}

ImGuiIO& setupImGui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    return io;
}

void loadGlad() {
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

int main(int, char**)
{
    GLFWwindow* window = initWindow();

    loadGlad();

    ImGuiIO& io = setupImGui();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    float deltaTime{ 0.f }, lastFrame{ 0.f };
    float angle_x{ 0.f }, angle_y{ 0.f };

    Scene* scene = new Scene();
    SceneObject* sampleObject = new SceneObject("root");
    SceneObject* sampleChild = new SceneObject("child", sampleObject);
    scene->setRootObject(sampleObject);
    std::vector<float> vertices = {
        //ściana 1
        1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,1.0f,

        1.0f,-1.0f,-1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,

        //ściana 2
        -1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,

        -1.0f,-1.0f, 1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,


        //ściana 3
        -1.0f,-1.0f,-1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,
        1.0f,-1.0f,-1.0f,1.0f,

        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f,-1.0f, 1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,

        //ściana 4
        -1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,

        -1.0f, 1.0f, 1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,

        //ściana 5
        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,
        -1.0f,-1.0f, 1.0f,1.0f,

        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,

        //ściana 6
        1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        1.0f,-1.0f,-1.0f,1.0f,

        1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
    };

    sampleObject->getMesh()->vertices = vertices;
    sampleObject->getMesh()->verticesCount = 36;
    sampleObject->getTransform()->position = Vector3(0, 0, -1);
    sampleObject->getTransform()->rotation = Quaternion(45, 45, 0);
    sampleObject->getTransform()->scale = Vector3(0.5, 0.5, 0.5);

    sampleChild->getMesh()->vertices = vertices;
    sampleChild->getMesh()->verticesCount = 36;
    sampleChild->getTransform()->position = Vector3(0, 0, -2);
    sampleChild->getTransform()->rotation = Quaternion(45, 45, 0);
    sampleChild->getTransform()->scale = Vector3(0.5, 0.5, 0.5);

    CameraRenderer* renderer = new CameraRenderer(window, &camera, scene);


    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(window);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("speed_y", &speed_y, -PI, PI);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::Text("position");
            ImGui::SliderFloat("x_pos", &pos_x, -2, 2);
            ImGui::SliderFloat("y_pos", &pos_y, -2, 2);
            ImGui::SliderFloat("z_pos", &pos_z, -2, 2);

            ImGui::Text("rotation");
            ImGui::SliderFloat("x_rot", &rot_x, -360, 360);
            ImGui::SliderFloat("y_rot", &rot_y, -360, 360);
            ImGui::SliderFloat("z_rot", &rot_z, -360, 360);

            ImGui::Text("scale");
            ImGui::SliderFloat("x_scale", &scale_x, -2, 2);
            ImGui::SliderFloat("y_scale", &scale_y, -2, 2);
            ImGui::SliderFloat("z_scale", &scale_z, -2, 2);

            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Begin("Viewport");
        ImGui::End();

        // Rendering
        ImGui::Render();
        
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        sampleObject->getTransform()->position = Vector3(pos_x, pos_y, pos_z);
        sampleObject->getTransform()->rotation = Quaternion(rot_x, rot_y, rot_z);
        sampleObject->getTransform()->scale = Vector3(scale_x, scale_y, scale_z);

        renderer->render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}*/
