#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <iostream>

#include <GLFW/glfw3.h>

// Functions
void SizeCallback(GLFWwindow* windowm, int w, int h);
void processInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE = "Main";

int main() {
    // Window initialization and set window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Apple systems only 
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Window creating
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    
    // Window creating error handling
    if(window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Selects the created window
    glfwMakeContextCurrent(window);
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, SizeCallback);

    #pragma region Hello Triangle
    // Triangle vertices
    float vertices[] = {
         0.5f,  0.5f, 0.0f, // Top Right
         0.5f, -0.5f, 0.0f // Bottom Right
        -0.5f, -0.5f, 0.0f // Bottom Left
        -0.5f,  0.5f, 0.0f, // Top Left
    };

    #pragma region Vextex Shader
    // Vertex shader code in GLSL
    const char *vertexShaderSource = 
    #include "./shaders/shader.glvs"
    ;
    // Creates vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Binds Shader code to the vertex shader created    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // Compiles shader

    std::cout << "Shader compile error handling" << "\n";
    // Shader compiling error handling
    int sucess;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "Couldn't compile shader" << infolog << std::endl;
        return -1;
    }
    std::cout << "No errors when compiling vertex shaders" << "\n";
    #pragma endregion Vextex Shader
    
    #pragma region Fragment Shader
    // Fragment shader code in GLSL
    const char *fragShaderSource = 
    #include "./shaders/shader.glfs"
    ;
    // Creates vertex shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Binds Shader code to the vertex shader created    
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader); // Compiles shader

    // Shader compiling error handling
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "Couldn't compile shader" << infolog << std::endl;
        return -1;
    }
    std::cout << "No errors when compiling fragment shaders" << "\n";
    #pragma endregion Fragment Shader

    #pragma region Shader Program
    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // Attaches Vertex and Fragment shader to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Error Handling
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "Couldn't link the shader program" << infolog << std::endl;
        return -1;
    }
    std::cout << "No errors when linking program" << "\n";

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    #pragma endregion Shader Program

    // Vertex buffer & Vertex array
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Copy vertices to buffer and configure VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set the Vertex attribute pointers
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    #pragma endregion Hello Triangle

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Clear the screen
        glClearColor(.2,.2,.2,1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Using shader program to render triangle
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // End loop, calling events and swapping buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Ends process
    glfwTerminate();
    return 0;
}

void SizeCallback(GLFWwindow* windowm, int w, int h) 
{
    glViewport(0,0, w, h);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}