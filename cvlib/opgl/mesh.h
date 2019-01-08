#ifndef CVCRAYON_OPGL_MESH_H
#define CVCRAYON_OPGL_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

namespace opgl
{
	class Mesh
	{
	public:
		struct Vertex_P // Position
		{
			glm::vec3 position;
		};

		struct Vertex_PC // Position Color
		{
			glm::vec3 position;
			glm::vec3 color;
		};

		struct Vertex_PT // Position Texture
		{
			glm::vec3 position;
			glm::vec2 texture;
		};

		struct Vertex_PNC // Position Normal Color
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
		};

		struct Vertex_PNT // Position Normal Texture
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texture;
		};

	public:
		Mesh(const std::vector<Vertex_P>   &vertex, const std::vector<int>& indices, const GLenum &usage);
		Mesh(const std::vector<Vertex_PC>  &vertex, const std::vector<int>& indices, const GLenum &usage);
		Mesh(const std::vector<Vertex_PT>  &vertex, const std::vector<int>& indices, const GLenum &usage);
		Mesh(const std::vector<Vertex_PNC> &vertex, const std::vector<int>& indices, const GLenum &usage);
		Mesh(const std::vector<Vertex_PNT> &vertex, const std::vector<int>& indices, const GLenum &usage);
		~Mesh();

		void Draw(const GLenum &mode);
	private:
		Mesh() = delete;
		Mesh(const Mesh& mesh) = delete;
		Mesh& operator=(const Mesh& mesh) = delete;

		GLuint VBO; //Vertex Buffer Objects
		GLuint VAO; //Vertex Array Objects
		GLuint EBO; //Element Buffer Objects
		int EBOCount;
	};
}

#endif // !CVCRAYON_OPGL_MESH_H

