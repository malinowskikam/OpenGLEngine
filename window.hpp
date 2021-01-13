#ifndef SEEN_WINDOW
#define SEEN_WINDOW

void errorCallback(int error, const char* description);
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void displayScene();

#endif