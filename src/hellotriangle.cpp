#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>

#include <GLFW/glfw3.h>

// -- Hello Triangle --
int main() {
        
    
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

    // -- Vertex shader --
    #pragma region Vextex Shader
    // Vertex shader code in GLSL
    const char *vertexShaderSource = 
    #include "./shaders/shader.vs"
    ;
    
    // Creates vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Binds Shader code to the vertex shader created    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // Compiles shader

    // Shader compiling error handling
    int sucess;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);

    if (sucess) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "Couldn't compile shader" << infolog << std::endl;
    }
    #pragma endregion Vextex Shader


    #pragma region Fragment Shader

    // Fragment shader code in GLSL
    const char *fragShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    #pragma endregion 

    #pragma endregion Hello Triangle
}