#ifndef SEEN_WINDOW
#define SEEN_WINDOW

void errorCallback(int error, const char* description);
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void focusCallback(GLFWwindow* window, int focused);
void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseActionCallback(GLFWwindow* window, int button, int action, int mods);

void displayScene();



#endif