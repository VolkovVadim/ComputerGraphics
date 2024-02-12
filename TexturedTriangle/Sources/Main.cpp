#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
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
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 texCoord;\n"
"out vec3 vertexColor;\n"
"out vec2 textureCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"    textureCoord = texCoord;\n"
"}";

static const char* fragment_shader_text = 
"#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 textureCoord;\n"
"out vec4 color;\n"
"uniform sampler2D image;\n"
"void main()\n"
"{\n"
"    color = texture(image, textureCoord) * vec4(vertexColor, 1.0f);\n"
"}\n";

GLfloat vertices[] = {
    // Positions         // Colors          // Texture coords
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Lower right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Lower left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f  // Top center
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

    // Create texture from image file
    int texture_width = 0, texture_height = 0;
    unsigned char* image = SOIL_load_image("./stones.jpg", &texture_width, &texture_height, 0, SOIL_LOAD_RGB);
    cout << "Texture size : " << texture_width << "x" << texture_height << endl;

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(
        GL_TEXTURE_2D,      // Texture target
        0,                  // Mipmap level
        GL_RGB,             // Texture store format
        texture_width,      // Pixels array size
        texture_height,     //
        0,                  // Old parameters, always must be 0
        GL_RGB,             // Source image pixels array format
        GL_UNSIGNED_BYTE,   //
        image               // Pixels color data array
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image resources
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


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

    cout << "Creating program..." << endl;
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
    //  _______________________________________________________________
    // |            Vertex 1           |            Vertex 2           |
    // |___________|___________|_______|___________|___________|_______|
    // | X | Y | Z | R | G | B | S | T | X | Y | Z | R | G | B | S | T |
    // |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
    // | 0 | 1 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
    //
    //  <-----------------------------> <----------------------------->
    //      step = 8 * sizeof(float)
    glBindVertexArray(vao_id);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                             // Input layout position in vertex shader
        3,                             // Input vector size
        GL_FLOAT,                      // Data type
        GL_FALSE,                      // No need to normalize data
        8 * sizeof(GL_FLOAT),          // Data step
        (GLvoid*)0                     // Start data offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                             // Input layout position in vertex shader
        3,                             // Input vector size
        GL_FLOAT,                      // Data type
        GL_FALSE,                      // No need to normalize data
        8 * sizeof(GL_FLOAT),          // Data step
        (GLvoid*)(3 * sizeof(GLfloat)) // Start data offset
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,                             // Input layout position in vertex shader
        2,                             // Input vector size
        GL_FLOAT,                      // Data type
        GL_FALSE,                      // No need to normalize data
        8 * sizeof(GL_FLOAT),          // Data step
        (GLvoid*)(6 * sizeof(GLfloat)) // Start data offset
    );


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    // Shutdown
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
