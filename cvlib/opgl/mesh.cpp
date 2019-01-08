#include "mesh.h"

namespace opgl
{

	Mesh::Mesh(const std::vector<Vertex_P>& vertex, const std::vector<int>& indices, const GLenum & usage) : 
		EBOCount(static_cast<int>(indices.size()))
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOCount * sizeof(int), &indices[0], usage);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(vertex.size()) * sizeof(Vertex_P), &vertex[0], usage);
		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_P), (void*)0);
		glBindVertexArray(0);
	}

	Mesh::Mesh(const std::vector<Vertex_PC>& vertex, const std::vector<int>& indices, const GLenum & usage) :
		EBOCount(static_cast<int>(indices.size()))
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(vertex.size()) * sizeof(Vertex_PC), &vertex[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOCount * sizeof(int), &indices[0], usage);

		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PC), (void*)0);
		// color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PC), (void*)offsetof(Vertex_PC, color));
		glBindVertexArray(0);
	}

	Mesh::Mesh(const std::vector<Vertex_PT>& vertex, const std::vector<int>& indices, const GLenum & usage) :
		EBOCount(static_cast<int>(indices.size()))
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(vertex.size()) * sizeof(Vertex_PT), &vertex[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOCount * sizeof(int), &indices[0], usage);
		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PT), (void*)0);
		// texture
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_PT), (void*)offsetof(Vertex_PT, texture));
		glBindVertexArray(0);
	}

	Mesh::Mesh(const std::vector<Vertex_PNC>& vertex, const std::vector<int>& indices, const GLenum & usage) :
		EBOCount(static_cast<int>(indices.size()))
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(vertex.size()) * sizeof(Vertex_PNC), &vertex[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOCount * sizeof(int), &indices[0], usage);
		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNC), (void*)0);
		// normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNC), (void*)offsetof(Vertex_PNC, normal));
		// color
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNC), (void*)offsetof(Vertex_PNC, color));
		glBindVertexArray(0);
	}

	Mesh::Mesh(const std::vector<Vertex_PNT>& vertex, const std::vector<int>& indices, const GLenum & usage) :
		 EBOCount(static_cast<int>(indices.size()))
	{
		
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(vertex.size()) * sizeof(Vertex_PNT), &vertex[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOCount * sizeof(int), &indices[0], usage);
		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNT), (void*)0);
		// normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNT), (void*)offsetof(Vertex_PNT, normal));
		// texture
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_PNT), (void*)offsetof(Vertex_PNT, texture));
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Mesh::Draw(const GLenum & mode)
	{
		glBindVertexArray(VAO);
		glDrawElements(mode, EBOCount, GL_UNSIGNED_INT, 0);
		//glDrawArrays(mode, 0, EBOCount);
		//glBindVertexArray(0); // no need to unbind it every time 
	}
}



