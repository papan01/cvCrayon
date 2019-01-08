#ifndef CVCRAYON_OPGL_VIEWER_H
#define CVCRAYON_OPGL_VIEWER_H

#include <GLFW\glfw3.h>
#include <string>

namespace opgl
{
	class Viewer
	{
	public:
		Viewer() = delete;
		explicit Viewer(const int& width, const int& height, const std::string& title);
		~Viewer();

		void Updata();
		void ClearColor(const float& r, const float& g, const float& b, const float& a);
		bool Viewer::isClosed();
	private:
		GLFWwindow* window;
		bool b_isClosed;	
	};
}

#endif // !CVCRAYON_OPGL_VIEWER_H

