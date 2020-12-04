#define GLFW_INCLUDE_NONE
#include "glfw3.h"


int main() {

	if (!glfwInit())
	{
		// Initialisation failed.
	}

	glfwTerminate();

}
