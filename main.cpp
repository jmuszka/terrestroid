#include <glad/glad.h> // OpenGL loading library
#include <GLFW/glfw3.h> // OS-agnostic API for creating windows, contexts, and surfaces

#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "shader.hpp"
#include "camera.hpp"
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
    // CUBE
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,


    // LIGHT SOURCE
    0.9f, -0.1f, 1.1f,  0.0f, 0.0f,
    1.1f, -0.1f, 1.1f,  1.0f, 0.0f,
    1.1f,  0.1f, 1.1f,  1.0f, 1.0f,
    0.9f, -0.1f, 1.1f,  0.0f, 0.0f,
    1.1f,  0.1f, 1.1f,  1.0f, 1.0f,
    0.9f,  0.1f, 1.1f,  0.0f, 1.0f,

    1.1f, -0.1f, 0.9f,  0.0f, 0.0f,
    0.9f, -0.1f, 0.9f,  1.0f, 0.0f,
    0.9f,  0.1f, 0.9f,  1.0f, 1.0f,
    1.1f, -0.1f, 0.9f,  0.0f, 0.0f,
    0.9f,  0.1f, 0.9f,  1.0f, 1.0f,
    1.1f,  0.1f, 0.9f,  0.0f, 1.0f,

    0.9f, -0.1f, 0.9f,  0.0f, 0.0f,
    0.9f, -0.1f, 1.1f,  1.0f, 0.0f,
    0.9f,  0.1f, 1.1f,  1.0f, 1.0f,
    0.9f, -0.1f, 0.9f,  0.0f, 0.0f,
    0.9f,  0.1f, 1.1f,  1.0f, 1.0f,
    0.9f,  0.1f, 0.9f,  0.0f, 1.0f,

    1.1f, -0.1f, 1.1f,  0.0f, 0.0f,
    1.1f, -0.1f, 0.9f,  1.0f, 0.0f,
    1.1f,  0.1f, 0.9f,  1.0f, 1.0f,
    1.1f, -0.1f, 1.1f,  0.0f, 0.0f,
    1.1f,  0.1f, 0.9f,  1.0f, 1.0f,
    1.1f,  0.1f, 1.1f,  0.0f, 1.0f,

    0.9f,  0.1f, 1.1f,  0.0f, 0.0f,
    1.1f,  0.1f, 1.1f,  1.0f, 0.0f,
    1.1f,  0.1f, 0.9f,  1.0f, 1.0f,
    0.9f,  0.1f, 1.1f,  0.0f, 0.0f,
    1.1f,  0.1f, 0.9f,  1.0f, 1.0f,
    0.9f,  0.1f, 0.9f,  0.0f, 1.0f,

    0.9f, -0.1f, 0.9f,  0.0f, 0.0f,
    1.1f, -0.1f, 0.9f,  1.0f, 0.0f,
    1.1f, -0.1f, 1.1f,  1.0f, 1.0f,
    0.9f, -0.1f, 0.9f,  0.0f, 0.0f,
    1.1f, -0.1f, 1.1f,  1.0f, 1.0f,
    0.9f, -0.1f, 1.1f,  0.0f, 1.0f,
};

unsigned int indices[36];
unsigned int lightIndices[36];

// Object IDs
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int lightVBO;
unsigned int lightVAO;
unsigned int lightEBO;

Shader *shader;
Shader *lightSourceShader;

// int width, height, nrChannels;
// unsigned char *data = stbi_load("linus.jpeg", &width, &height, &nrChannels, 0);

// unsigned int texture;

Camera cam(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cam.look(xpos, ypos);
}

// Resize viewport upon resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Handle keyboard input
void processInput()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    const float speed = deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.move(CAM_FORWARDS, speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.move(CAM_BACKWARDS, speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.move(CAM_LEFT, speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.move(CAM_RIGHT, speed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.move(CAM_UP, speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.move(CAM_DOWN, speed);

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;;
        exit(-1);
    }

    // Set size of viewport to be window size
    glViewport(0, 0, SCREEN_W, SCREEN_H); // x, y, w, h
    glEnable(GL_DEPTH_TEST);
}

// Compile GLSL code
Shader* compileShaders(const std::string &vertexShader, const std::string &fragmentShader)
{
    return new Shader(vertexShader.c_str(), fragmentShader.c_str());
}

// Drawing commands
void draw()
{
    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color with specified color (state-setting)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the background and depth buffer
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shader->use();
    shader->setVec3("objectColor", glm::vec3(0.8f, 0.1f, 0.8f));
    shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    // Transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::lookAt(cam.pos, cam.pos+cam.front, cam.up);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_W/(float)SCREEN_H, 0.1f, 100.0f);

    // Use the shader program and bind vertex array each time we draw
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int projLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    // glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);


    // Draw light source
    lightSourceShader->use();
        // Use the shader program and bind vertex array each time we draw
    modelLoc = glGetUniformLocation(lightSourceShader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    viewLoc = glGetUniformLocation(lightSourceShader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    projLoc = glGetUniformLocation(lightSourceShader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(lightVAO);
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
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
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    // glEnableVertexAttribArray(1);

    // Create and bind
    glGenBuffers(1, &lightVBO);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightEBO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices+36*5, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    // Texture attributes
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    // glEnableVertexAttribArray(1);

    // Textures
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // if (data) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }

    // stbi_image_free(data);

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

    for (int i = 0; i < sizeof(indices)/sizeof(float); i++)
        indices[i] = i;
    for (int i = 0; i < sizeof(lightIndices)/sizeof(float); i++)
        lightIndices[i] = i;

    shader = compileShaders("shaders/vertex_shader.glsl", "shaders/frag_shader.glsl");
    lightSourceShader = compileShaders("shaders/vertex_shader.glsl", "shaders/light_source_frag.glsl");
    render();

    glfwTerminate();
    return 0;
}