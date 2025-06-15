#include <glad/glad.h> // OpenGL loading library
#include <GLFW/glfw3.h> // OS-agnostic API for creating windows, contexts, and surfaces

#include <iostream>
#include <ostream>

#define SCREEN_W 800
#define SCREEN_H 600

// Resize viewport upon resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // Close window when pressing escape key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

// Rendering loop
void render(GLFWwindow *window)
{
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear color with specified color (state-setting)
        glClear(GL_COLOR_BUFFER_BIT); // Clear the background (state-using)

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {

    // Configure exact OpenGL specification for GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Required for MacOS

    // Create window object
    GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Terrestroid", NULL, NULL); // width, height, name, opaque monitor object, opqaue window object
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Make the context of our window the main context on the current thread
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Resize viewport upon resizing window

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;;
        return -1;
    }

    // Set size of viewport to be window size
    glViewport(0, 0, SCREEN_W, SCREEN_H); // x, y, w, h

    render(window);
    glfwTerminate();
    return 0;
}