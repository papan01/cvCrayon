#ifndef CVCRAYON_OPGL_SHADER_H
#define CVCRAYON_OPGL_SHADER_H

#include <string>
#include <glm\glm.hpp>
#include <GL\glew.h>

namespace opgl
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		Shader() = delete;
		Shader(const Shader& shader) = delete;
		Shader& operator=(const Shader& shader) = delete;
		~Shader();

		void Bind();
		void setBool(const std::string &name, const bool &value) const;
		void setInt(const std::string &name, const int &value) const;
		void setFloat(const std::string &name, const float &value) const;
		void set4f(const std::string &name, const float &x, const float &y, const float &z, const float &w) const;
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec2(const std::string &name, const float& x, const float& y) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec3(const std::string &name, const float& x, const float& y, const float& z) const;
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setVec4(const std::string &name, const float& x, const float& y, const float& z, const float& w) const;
		void setMatrix2fv(const std::string &name, const int &matrix_count, const GLuint &need_Transpos, const glm::mat2 &trans) const;
		void setMatrix3fv(const std::string &name, const int &matrix_count, const GLuint &need_Transpos, const glm::mat3 &trans) const;
		void setMatrix4fv(const std::string &name, const int &matrix_count, const GLuint &need_Transpos, const glm::mat4 &trans) const;

	private:
		GLuint programID;
		GLuint vertex;
		GLuint fragment;
	private:
		std::string LoadShader(const std::string& filePath);
		GLuint CreateShader(const std::string& shaderCode, const unsigned int& type);
		void CheckShaderError(const GLuint& shader, const GLuint& flag, const bool& isProgram, const std::string& errorMessage);
	};
}



#endif // !CVCRAYON_OPGL_SHADER_H

