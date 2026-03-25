
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <EGL/egl.h>

#include <Primitives/Triangle.h>
#include <Primitives/Rect.h>

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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, SizeCallback);

    Triangle trig;
    Rect rt;

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Clear the screen
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        trig.draw();
        //rt.draw();

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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}