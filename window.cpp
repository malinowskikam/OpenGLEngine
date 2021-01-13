#include "include.hpp"

using namespace std;

extern Global* global;

void errorCallback(int error, const char* description)
{
    cerr << "GLFW Error" << error << ": " << description << endl;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    global->windowWidth = width;
    global->windowHeight = height;
}

void focusCallback(GLFWwindow* window, int focused)
{

}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
    
}

void mouseActionCallback(GLFWwindow* window, int button, int action, int mods)
{
    
}

void displayScene()
{
    glfwSwapBuffers(global->window);
    glViewport(0, 0, global->windowWidth, global->windowHeight);
}