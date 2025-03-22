#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <math.h>

#include "window.h"
#include "color.h"

// Number of dimensions
#define N 3
#define PI 3.14159265
// Game name
#define NAME "Terrestroid"
// Game major version
#define MAJOR_VERSION 0
#define MINOR_VERSION 0
#define PATCH_VERSION 0

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define REFRESH_RATE 60.01

using namespace std;

// Globals: to be moved to classes
vector<GLfloat> vertices;
GLuint shader_program_object = 0;
unsigned int vao = 0;
unsigned int vbo = 0;

// Add a vertex to the vertex list
void addVertex(GLfloat x, GLfloat y)
{
    // Push two floats, x and y position, to the vector
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0);
}

// Add a triangle to the vertex list
void _addTriangle(
                    GLfloat x1, GLfloat y1,
                    GLfloat x2, GLfloat y2,
                    GLfloat x3, GLfloat y3
) {

    // Simply add 3 vertices to the vertex vector
    addVertex(x1, y1);
    addVertex(x2, y2);
    addVertex(x3, y3);

}

// Using conventional coordinates
void addTriangle(
    GLfloat x1, GLfloat y1,
    GLfloat x2, GLfloat y2,
    GLfloat x3, GLfloat y3)
{
    _addTriangle(
        (x1-WIN_WIDTH/2)/(WIN_WIDTH/2), -(y1-WIN_HEIGHT/2)/(WIN_HEIGHT/2),
        (x2-WIN_WIDTH/2)/(WIN_WIDTH/2), -(y2-WIN_HEIGHT/2)/(WIN_HEIGHT/2),
        (x3-WIN_WIDTH/2)/(WIN_WIDTH/2), -(y3-WIN_HEIGHT/2)/(WIN_HEIGHT/2)
    );
}

// Display all triangles on the screen
void drawTriangles()
{
    glUseProgram(shader_program_object);
    {
        glBindVertexArray(vao);
        {
            glDrawArrays(GL_TRIANGLES, 0, vertices.size()/N);
        }
        glBindVertexArray(0);
    }
    glUseProgram(0);
}

// Redraw the background
void clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Change the color of the background through a color hex string
void setBackgroundColor(Color color)
{
    glClearColor(color.getRed()/255.0f, 
                 color.getGreen()/255.0f, 
                 color.getBlue()/255.0f, 
                 color.getAlpha()/255.0f);
}

void glPipelineConfig()
{
    // Create vertex buffer
    glGenBuffers(1, &vbo);
    {
        // Bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Add vertices to buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
        // Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Create vertex array
    glGenVertexArrays(1, &vao);
    {
        // Bind vertex Array
        glBindVertexArray(vao);
        // Enable the first input variable (vertex position)
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Configure vertex geometry
        glVertexAttribPointer(0, N, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // Configure shader
    { // SHADERS

        const char* vertex_shader_str =
            "#version 410\n"
            "in vec3 a_position;\n"
            "void main() {\n"
            "gl_Position = vec4(a_position, 1.0);\n"
            "}";

        const char* fragment_shader_str =
            "#version 410\n"
            "out vec4 o_frag_colour;\n"
            "void main() {\n"
            "o_frag_colour = vec4(1.0, 1.0, 0.0, 1.0);\n"
            "}\n";

        GLuint vertex_shader_object = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader_object, 1, &vertex_shader_str, NULL);
        glCompileShader(vertex_shader_object);

        GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_object, 1, &fragment_shader_str, NULL);
        glCompileShader(fragment_shader_object);

        shader_program_object = glCreateProgram();
        glBindAttribLocation(shader_program_object, 0, "a_position");

        glAttachShader(shader_program_object, vertex_shader_object);
        glAttachShader(shader_program_object, fragment_shader_object);
        glLinkProgram(shader_program_object);
    }
}

int main()
{

    Window win(WIN_WIDTH, WIN_HEIGHT);

    // Initialize OpenGL context
    glfwInit();
    
    // Window configurations
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Disable window resizing
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // Maximum refresh rate
    glfwWindowHint(GLFW_SAMPLES, 4); // Set anti-aliasing
    glEnable(GL_MULTISAMPLE); // Enable anti-aliasing

    // Create window
    string name = NAME; string space = " "; string delimit = ".";
    string major = to_string(MAJOR_VERSION);
    string minor = to_string(MINOR_VERSION);
    string patch = to_string(PATCH_VERSION);
    GLFWwindow* window = glfwCreateWindow(win.getWidth(), win.getHeight(), 
        (name+space+major+delimit+minor+delimit+patch).c_str(), 
        nullptr, nullptr); // Windowed
    glfwSetWindowPos(window, 0, 0); // Window position

    // Assign window to OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize OpenGL wrapper
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Error loading GLEW" << endl;
        return 1;
    }

    // Store triangle vertices
    GLfloat length = WIN_WIDTH/8;
    int X = 200; int Y = 200;

    addTriangle(X, Y, 
                X+length*sin(PI/6), Y+length*cos(PI/6), 
                X-length*sin(PI/6), Y+length*cos(PI/6));

    addTriangle(X-length*sin(PI/6), Y+length*cos(PI/6),
                X-length*sin(PI/6)-length*sin(PI/6), Y+length*cos(PI/6)+length*cos(PI/6),
                X, Y+length*cos(PI/6)+length*cos(PI/6));

    addTriangle(X+length*sin(PI/6), Y+length*cos(PI/6),
                X+length*sin(PI/6)+length*sin(PI/6), Y+length*cos(PI/6)+length*cos(PI/6),
                X, Y+length*cos(PI/6)+length*cos(PI/6));

    glPipelineConfig();

    // Set background color
    setBackgroundColor(Color("#4949aa"));

    // Draw loop
    while(!glfwWindowShouldClose(window))
    {
        clear(); // redraw background
        drawTriangles();

        // Check for input events
        glfwPollEvents();
        glfwSwapBuffers(window);

        // Exit program when pressing Escape key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Clean up OpenGL context
    glfwTerminate();
    return 0;
}