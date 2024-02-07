#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static bool wireframe = true;
    if(action == GLFW_PRESS) {
        switch(key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_SPACE:
            wireframe ? 
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframe = !wireframe;
            break;
        }
    }
}

static const char* vertex_shader_text = 
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

static const char* fragment_shader_text = 
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

GLfloat vertices[] = {
    // X     Y      Z
    -0.5f, -0.5f,  0.0f,    // lower left
     0.5f, -0.5f,  0.0f,    // lower right
     0.0f,  0.5f,  0.0f     // upper center
};

int main(int argc, char** argv)
{
    cout << "Application started..." << endl;
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Initialize GLFW
    glfwSetErrorCallback(error_callback);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create main window
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    // Initialize OpenGL
    gladLoadGL(glfwGetProcAddress);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Create buffers
    GLuint vao_id, vbo_id;
    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create shader program
    const unsigned int max_log_length = 512;
    GLchar info_log[max_log_length];
    GLint status;

    cout << "Creating vertex shader..." << endl;
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader_id);
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE) {
        glGetShaderInfoLog(vertex_shader_id, max_log_length, NULL, info_log);
        cerr << "Error  : failed to compile vertex shader" << endl;
        cerr << "Status : " << status << endl;
        cerr << "Info   : " << info_log << endl;
        return EXIT_FAILURE;
    }

    cout << "Crating fragment shader..." << endl;
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader_id);
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE) {
        glGetShaderInfoLog(fragment_shader_id, max_log_length, NULL, info_log);
        cerr << "Error  : failed to compile fragment shader" << endl;
        cerr << "Status : " << status << endl;
        cerr << "Info   : " << info_log << endl;
        return EXIT_FAILURE;
    }

    GLuint shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &status);

    if(status != GL_TRUE) {
        glGetProgramInfoLog(shader_program_id, max_log_length, NULL, info_log);
        cerr << "Error  : failed to create shader program" << endl;
        cerr << "Status : " << status << endl;
        cerr << "Info   : " << info_log << endl;
        return EXIT_FAILURE;
    }

    cout << "Shader program created" << endl;

    glUseProgram(shader_program_id);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    // Data array - vertices
    //  ___________________________________
    // |  Vertex 1 |  Vertex 2 |  Vertex 3 |
    // |___________|___________|___________|
    // | X | Y | Z | X | Y | Z | X | Y | Z |
    // |___|___|___|___|___|___|___|___|___|
    // | 0 | 1 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
    //
    //  <---------> <---------> <--------->
    //     step
    glBindVertexArray(vao_id);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                          // Input layout position in vertex shader
        3,                          // Input vector size
        GL_FLOAT,                   // Data type
        GL_FALSE,                   // No need to normalize data
        3 * sizeof(GL_FLOAT),       // Data step
        (GLvoid*)0                  // Start data offset
    );

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    // Shutdown
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
