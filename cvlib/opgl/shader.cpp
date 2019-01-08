#include "shader.h"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/utils.h"
#include "../utils/debugutils.h"

namespace opgl
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		// Initialize GLEW
		auto res = glewInit();
		if (res != GLEW_OK)
			error_exit("Glew failed to initialize!");
		else
			glewExperimental = true; // Needed for core profile

		vertex = CreateShader(LoadShader(vertexPath), GL_VERTEX_SHADER);
		fragment = CreateShader(LoadShader(fragmentPath), GL_FRAGMENT_SHADER);

		// shader Program
		programID = glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);
		CheckShaderError(programID, GL_LINK_STATUS, true, "Error linking shader program");
		glValidateProgram(programID);
		CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Invalid shader program");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		glDeleteProgram(programID);
	}

	void Shader::Bind()
	{
		glUseProgram(programID);
	}

	void Shader::setBool(const std::string &name, const bool &value) const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string &name, const int &value) const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string &name, const float &value) const
	{
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	}

	void Shader::set4f(const std::string &name, const float &x, const float &y, const float &z, const float &w) const
	{
		glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
	}

	void Shader::setVec2(const std::string & name, const glm::vec2 & value) const
	{
		glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec2(const std::string & name, const float& x, const float& y) const
	{
		glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
	}

	void Shader::setVec3(const std::string & name, const glm::vec3 & value) const
	{
		glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec3(const std::string & name, const float& x, const float& y, const float& z) const
	{
		glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
	}

	void Shader::setVec4(const std::string & name, const glm::vec4 & value) const
	{
		glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec4(const std::string & name, const float& x, const float& y, const float& z, const float& w) const
	{
		glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
	}

	void Shader::setMatrix2fv(const std::string & name, const int &matrix_count, const GLuint & need_Transpos, const glm::mat2 & trans) const
	{
		glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), matrix_count, need_Transpos, glm::value_ptr(trans));
	}

	void Shader::setMatrix3fv(const std::string & name, const int &matrix_count, const GLuint & need_Transpos, const glm::mat3 & trans) const
	{
		glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), matrix_count, need_Transpos, glm::value_ptr(trans));
	}

	void Shader::setMatrix4fv(const std::string &name, const int &matrix_count, const GLuint &need_Transpos, const glm::mat4 &trans) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), matrix_count, need_Transpos, glm::value_ptr(trans));
	}

	std::string Shader::LoadShader(const std::string & filePath)
	{
		std::string shaderCode;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(filePath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			error_exit("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}
		return shaderCode;
	}

	GLuint Shader::CreateShader(const std::string & shaderCode, const unsigned int & type)
	{
		auto shader = glCreateShader(type);

		if (shader == 0)
			error_exit("Error compiling shader type");

		const GLchar* p[1];
		p[0] = shaderCode.c_str();
		GLint lengths[1];
		lengths[0] = static_cast<GLint>(shaderCode.length());

		glShaderSource(shader, 1, p, lengths);
		glCompileShader(shader);
		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
		return shader;
	}

	void Shader::CheckShaderError(const GLuint & shader, const GLuint & flag, const bool & isProgram, const std::string & errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			PRINT_DEBUG("%s: '%s'", errorMessage, error);
		}
	}
}


