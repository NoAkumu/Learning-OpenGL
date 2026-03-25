#include <glad/glad.h>
#include <iostream>
#include <Primitives/Triangle.h>

int Triangle::setup() {
    // Triangle vertices
    float vertices[] = {
        0.0f,  0.5f, 0.0f, // Top Center
        0.5f, -0.5f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f, // Bottom Left
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

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Copy vertices to buffer and configure VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set the Vertex attribute pointers
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Using shader program to render both triangles to make a square
    glUseProgram(shaderProgram);

    return 0;
}

void Triangle::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Triangle::Triangle() {
    setup();
}