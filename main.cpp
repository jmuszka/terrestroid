#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

using namespace std;

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

    // Upper triangle
    positions.push_back(-0.25);
    positions.push_back(0);
    positions.push_back(0.25);
    positions.push_back(0);
    positions.push_back(0);
    positions.push_back(0.5);

    // Lower left triangle
    positions.push_back(-0.25);
    positions.push_back(0);
    positions.push_back(-0.5);
    positions.push_back(-0.5);
    positions.push_back(0);
    positions.push_back(-0.5);

    // Lower right triangle
    positions.push_back(0.25);
    positions.push_back(0);
    positions.push_back(0.5);
    positions.push_back(-0.5);
    positions.push_back(0);
    positions.push_back(-0.5);

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
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Loop
    while(!glfwWindowShouldClose(window))
    {
        // Redraw background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw triangles
        glUseProgram(shader_program_object);
        {
            glBindVertexArray(vao);
            {
                glDrawArrays(GL_TRIANGLES, 0, positions.size()/2);
            }
            glBindVertexArray(0);
        }
        glUseProgram(0);

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