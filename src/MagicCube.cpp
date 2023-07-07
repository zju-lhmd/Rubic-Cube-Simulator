#include "stdafx.h"
#include "MagicCube.h"

Cube cube;

void graphicMode(int argc, char *argv[])
{
	//Initialize the library
	if (!glfwInit())
		throw "glfwInit";

	//MSAA
	glfwWindowHint(GLFW_SAMPLES, 9);

	//Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(WIDTH, HEIGHT, "Magic Cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "glfwCreateWindow";
	}

	//Make the window's context current
	glfwMakeContextCurrent(window);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	
	initCommandHandlers();
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCharCallback(window, characterCallback);
		
	initGL();

	glfwSwapInterval(1);

	//Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		nextFrame();

		render();

		//Swap front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();

		keyboardScan();
		mouseMove();
		updateFPS();
	}

	glfwTerminate();
}

int main(int argc, char *argv[])
{
	srand(clock());
	graphicMode(argc, argv);

	return 0;
}

