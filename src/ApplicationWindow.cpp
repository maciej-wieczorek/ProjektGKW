#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(int width, int height, std::string title)
{
    //glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
        exit(1);
}

ApplicationWindow::ApplicationWindow(int width, int height) : ApplicationWindow(width, height, "Application")
{
    
}

ApplicationWindow::ApplicationWindow() : ApplicationWindow(800, 600)
{
}

void ApplicationWindow::setActive()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync TODO:optionally enable vsync
}

GLFWwindow* ApplicationWindow::getWindow()
{
	return window;
}

void ApplicationWindow::getSize(int& width, int& height)
{

}

bool ApplicationWindow::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void ApplicationWindow::setTitle(std::string title)
{
    glfwSetWindowTitle(window, title.c_str());
}

void ApplicationWindow::beginFrame()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();
    processInput();
}

void ApplicationWindow::endFrame()
{
    glfwSwapBuffers(window);
}

void ApplicationWindow::close()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void ApplicationWindow::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    /*speed_x = 0.f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        speed_x = PI;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        speed_x = -PI;*/
}

void ApplicationWindow::glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
