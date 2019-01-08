#include "viewer.h"
#include "../utils/debugutils.h"

namespace
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}


namespace opgl
{
	Viewer::Viewer(const int& width, const int& height, const std::string& title) : b_isClosed(false) {
		// Initialise GLFW
		if (!glfwInit())
			error_exit("Failed to initialize GLFW");

		//openGL version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef  __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif //__APPLE__

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window == NULL) {
			glfwTerminate();
			error_exit("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	}

	Viewer::~Viewer() {
		glfwTerminate();
	}

	void Viewer::Updata()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Viewer::ClearColor(const float & r, const float & g, const float & b, const float & a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool Viewer::isClosed()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);		
		b_isClosed = glfwWindowShouldClose(window) == 0 ? false : true;
		return b_isClosed;
	}

}

