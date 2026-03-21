#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>

#include <GLFW/glfw3.h>

int ShaderCompileErrorHandle(int shader);

// -- Hello Triangle --
void RenderTriangle() {
    // Triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // Vertex buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

    ShaderCompileErrorHandle(vertexShader);
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

    ShaderCompileErrorHandle(fragmentShader);
    #pragma endregion Fragment Shader

    // Create shader program
    unsigned int shaderProgram;
    
}

int ShaderCompileErrorHandle(int shader){
        // Shader compiling error handling
    int sucess;
    char infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        std::cout << "Couldn't compile shader" << infolog << std::endl;
        return -1;
    }
    return 0;
}