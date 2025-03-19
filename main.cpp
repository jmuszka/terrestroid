#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

// Add a vertex to the vertex list
void addVertex(vector<GLfloat> *p, GLfloat x, GLfloat y)
{
    // Push two floats, x and y position, to the vector
    p->push_back(x);
    p->push_back(y);
}

// Add a triangle to the vertex list
void addTriangle(vector<GLfloat> *p,
                    GLfloat x1, GLfloat y1,
                    GLfloat x2, GLfloat y2,
                    GLfloat x3, GLfloat y3
) {

    // Simply add 3 vertices to the vertex vector
    addVertex(p, x1, y1);
    addVertex(p, x2, y2);
    addVertex(p, x3, y3);

}

// Display all triangles on the screen
void drawTriangles(vector<GLfloat> *p, unsigned int vao, GLuint shader_program_object)
{
    glUseProgram(shader_program_object);
    {
        glBindVertexArray(vao);
        {
            glDrawArrays(GL_TRIANGLES, 0, p->size()/2);
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

// Convert a hexadecimal character to a decimal integer
int getDecVal(char digit)
{
    switch(digit)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            // If invalid hexadeimal digit
            return -1;
    }
}

// Change the color of the background through a color hex string
void setBackgroundColor(string colorHex)
{
    // If invalid color hex, set background to black
    if (colorHex.size() != 7) 
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        return;
    }

    // Parse from string to 3-tuple int
    int red = 16*getDecVal(colorHex[1]) + getDecVal(colorHex[2]);
    int green = 16*getDecVal(colorHex[3]) + getDecVal(colorHex[4]);
    int blue = 16*getDecVal(colorHex[5]) + getDecVal(colorHex[6]);

    // Set background color
    glClearColor(red/255.0f, green/255.0f, blue/255.0f, 1.0f);
}

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
    vector<GLfloat> positions;
    addTriangle(&positions, -0.25, 0, 0.25, 0, 0, 0.5); // upper triangle
    addTriangle(&positions, -0.25, 0, -0.5, -0.5, 0, -0.5); // lower left triangle
    addTriangle(&positions, 0.25, 0, 0.5, -0.5, 0, -0.5); // lower right triangle

    // Create vertex buffer
    unsigned int vbo = 0;
    glGenBuffers(1, &vbo);
    {
        // Bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Add vertices to buffer
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
        // Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Create vertex array
    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    {
        // Bind vertex Array
        glBindVertexArray(vao);
        // Enable the first input variable (vertex position)
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Configure vertex geometry
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // Configure shader
    GLuint shader_program_object = 0;
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

    // Set background color
    setBackgroundColor("#494949");

    // Draw loop
    while(!glfwWindowShouldClose(window))
    {
        clear(); // redraw background
        drawTriangles(&positions, vao, shader_program_object);

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