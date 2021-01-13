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

void displayScene()
{
    glfwSwapBuffers(global->window);
    glViewport(0, 0, global->windowWidth, global->windowHeight);
}