#include <glad/glad.h> // OpenGL loading library
#include <GLFW/glfw3.h> // OS-agnostic API for creating windows, contexts, and surfaces

#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>

#include "shader.hpp"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SCREEN_W 600
#define SCREEN_H 600

// Window object
GLFWwindow* window;

// Triangle (xyz, st)
float vertices[] = {

    // Front face
    0.5f, 0.5f, 0.0f, 1.01f, -0.01f,
    0.5f, -0.5f, 0.0f, 1.01f, 1.01f,
    -0.5f, -0.5f, 0.0f, -0.01f, 1.01f,
    -0.5f, 0.5f, 0.0f, -0.01f, -0.01f,

    // Left face
    -0.5f, 0.5f, 0.0f, 1.01f, -0.01f,
    -0.5f, -0.5f, 0.0f, 1.01f, 1.01f,
    -0.5f, 0.5f, 1.0f, -0.01f, -0.01f,
    -0.5f, -0.5f, 1.0f, -0.01f, 1.01f,

    // Right face
    0.5f, 0.5f, 0.0f, -0.01f, 1.01f,
    0.5f, -0.5f, 0.0f, -0.01f, -0.01f,
    0.5f, 0.5f, 1.0f, 1.01f, 1.01f,
    0.5f, -0.5f, 1.0f, 1.01f, -0.01f,

    // Rear face
    0.5f, 0.5f, 1.0f, -0.01f, -0.01f,
    0.5f, -0.5f, 1.0f, -0.01f, 1.01f,
    -0.5f, -0.5f, 1.0f, 1.01f, 1.01f,
    -0.5f, 0.5f, 1.0f, 1.01f, -0.01f,
    
};

unsigned int indices[] = {



    0, 1, 3,
    1, 2, 3,

    8, 9, 10,
    9, 10, 11,


   12, 13, 14,
    12, 14, 15,

    4, 5, 6,
    5, 6, 7,
};

// Object IDs
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

Shader *shader;

int width, height, nrChannels;
unsigned char *data = stbi_load("linus.jpeg", &width, &height, &nrChannels, 0);

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
Shader* compileShaders()
{
    return new Shader("shaders/vertex_shader.glsl", "shaders/frag_shader.glsl");
}

// Drawing commands
void draw()
{
    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color with specified color (state-setting)
    glClear(GL_COLOR_BUFFER_BIT); // Clear the background (state-using)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
    model = glm::rotate(model, (float)glfwGetTime()/2, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
    model = glm::scale(model, glm::vec3(10.0, 10.0, 10.0));

    // Use the shader program and bind vertex array each time we draw
    unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    shader->use();

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Rendering loop
void render()
{
    // Create and bind
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    // Texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Textures
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

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

    shader = compileShaders();
    render();

    glfwTerminate();
    return 0;
}