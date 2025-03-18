#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int main()
{
    // Initialize OpenGL context
    glfwInit();
    
    // Window configurations
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Disable window resizing
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // Maximum refresh rate

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
    //GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
    glfwSetWindowPos(window, 0, 0); // Window position

    // Assign window to OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize OpenGL wrapper
    glewExperimental = GL_TRUE;
    glewInit();

    // Vertex buffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    //printf("%u\n", vertexBuffer);

    // Loop
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Exit program when pressing Escape key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Clean up OpenGL context
    glfwTerminate();
}