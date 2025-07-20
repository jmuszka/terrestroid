#include <glad/glad.h> // OpenGL loading library
#include <GLFW/glfw3.h> // OS-agnostic API for creating windows, contexts, and surfaces

#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>

#include "shader.hpp"
#include "stb_image.h"

#define SCREEN_W 600
#define SCREEN_H 600

#define N 3

// Window object
GLFWwindow* window;

// Triangle
float vertices[] = {
    // position,        color,      texture coordinates

    // Triangle 1, red
    0.0f, 0.625f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f,
    -0.35355f, 0.125f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.35355f, 0.125f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

    // Triangle 2, green
    0.35355f, 0.125f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f,
    0.70712f, -0.375, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.375, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    // Triangle 3, blue
    -0.35355f, 0.125f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
    -0.70712f, -0.375, 0.0f, 0.0f, 0.0f, 1.0f, 0.2f, 0.6f,
    0.0f, -0.375, 0.0f, 0.0f, 1.0f, 1.0f, 0.8f, 0.6f,
};

// Object IDs
unsigned int VBO[N];
unsigned int VAO[N];

Shader *shader;

// image
int width, height, nrChannels;
unsigned char *data = stbi_load("linus.jpeg", &width, &height, &nrChannels, 0);

// texture
unsigned int texture;

// Resize viewport upon resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Handle keyboard input
void processInput()
{
    // Close window when pressing escape key or 'q'
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

// Initialize GLFW and GLAD; create window
void init()
{
    // Configure exact OpenGL specification for GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Required for MacOS

    // Create window object
    window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Terrestroid", NULL, NULL); // width, height, name, opaque monitor object, opqaue window object
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window); // Make the context of our window the main context on the current thread
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Resize viewport upon resizing window

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;;
        exit(-1);
    }

    // Set size of viewport to be window size
    glViewport(0, 0, SCREEN_W, SCREEN_H); // x, y, w, h
}

// Compile GLSL code
void compileShaders()
{
    shader = new Shader("shaders/vertex_shader.glsl", "shaders/frag_shader.glsl");
}

// Drawing commands
void draw()
{
    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color with specified color (state-setting)
    glClear(GL_COLOR_BUFFER_BIT); // Clear the background (state-using)

    for (int i = 0; i < N; i++)
    {
        // Use the shader program and bind vertex array each time we draw
        glBindVertexArray(VAO[i]);
        shader->use();
        shader->setFloat("x_offset", 1.0f-0.70712f);

        // Draw triangle
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 3*i, 3); // OpenGL primitive type, starting index of the vertex array, how many vertices to draw
    }
}

// Rendering loop
void render()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    for (int i = 0; i < N; i++)
    {
        // Set up buffers
        glGenBuffers(1, &VBO[i]);
        glGenVertexArrays(1, &VAO[i]);

        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // TODO: surely we don't need to pass in ALL the vertex data each time

        // Tell OpenGL how to interpret vertex data 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0); // 0 related to first 0 above
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3*sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    // Rendering loop
    while (!glfwWindowShouldClose(window))
    {
        processInput();   
        draw();

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    init();

    compileShaders();
    render();

    free(shader);
    glfwTerminate();
    return 0;
}