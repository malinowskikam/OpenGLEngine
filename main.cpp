#include "include.hpp"

using namespace std;

Global *global = getGlobal();

void initializeData()
{
	
}

void initializeGL()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glewExperimental = GL_TRUE;
	
	GLenum err = glewInit();
	
	if( GLEW_OK != err )
	{
		cerr << "GLEW Error " << err << endl;
		exit(1);
	}

	// OpenGL
	if( !GLEW_VERSION_3_2 )
	{
		cerr << "No OpenGL 3.2!" << endl;
		exit(1);
	}

	cout << "GLEW initialized" << endl;
}

void initializeWindow()
{
	if (!glfwInit())
	{
		cerr << "GLFW init failed" << endl;
		exit(1);
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	global->window = glfwCreateWindow(global->windowWidth, global->windowHeight, WINDOW_NAME, NULL, NULL);
	if(!global->window)
	{
		cerr << "Window init failed" << endl;
		exit(1);
	}

	glfwMakeContextCurrent(global->window);

	glfwSwapInterval(1);

	glfwSetKeyCallback(global->window, keyboardCallback);
	glfwSetFramebufferSizeCallback(global->window, frameBufferSizeCallback);
	glfwSetWindowFocusCallback(global->window, focusCallback);
	glfwSetCursorPosCallback(global->window, mousePosCallback);
	glfwSetMouseButtonCallback(global->window, mouseActionCallback);

	cout << "GLFW initialized" << endl;
}

int main( int argc, char *argv[] )
{
	srand(time(NULL));
	
	initializeWindow();
	initializeGL();
    initializeData();

	//thread console(consoleMain);

	while (!glfwWindowShouldClose(global->window))
	{
		glfwPollEvents();
	}

	cout << "Closing application..." << endl;

	glfwTerminate();
	return 0;
}