#include "Shader.h"
#include "math/Matrix4.h"
#include "math/Vectors.h"

namespace Tactics
{
	Shader::Shader()
	{
		
	}
	Shader::Shader(const std::string filepath)
	{
		parse_shader_code(filepath);
		create_shader();
	}
	/// <summary>
	/// Parses a single shader file. Separation denoted by #shader vertex, #shader fragment
	/// </summary>
	/// <param name="filepath">= Filepath to the shader</param>
	void Shader::parse_shader_code(const std::string filepath)
	{
		std::ifstream stream(filepath);
		if (!stream)
		{
			std::cout << "Cannot open " << filepath << std::endl;
			assert(false);
		}

		enum class ShaderType
		{
			NONE = -1, 	VERTEX = 0, FRAGMENT = 1
		};

		//@Cleanup Might be more efficient way of doing this. I do not actually know what is going on here, copied from tutorial.
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}
		vertexShaderCode = ss[0].str();
		fragmentShaderCode = ss[1].str();
	}

	void Shader::create_shader()
	{
		compile_vertex_shader();
		compile_fragment_shader();
		program = glCreateProgram();
		GLCall(glAttachShader(program, vertexShader));
		GLCall(glAttachShader(program, fragmentShader));
		GLCall(glLinkProgram(program));
	}
	/// <summary>
	/// Finds the location of a uniform from opengl
	/// </summary>
	/// <param name="name"></param>
	/// <returns>int</returns>
	void Shader::compile_fragment_shader()
	{
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragSrc = fragmentShaderCode.c_str();
		GLCall(glShaderSource(fragmentShader, 1, &fragSrc, nullptr));
		GLCall(glCompileShader(fragmentShader));
		int result;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(fragmentShader, length, &length, message);
			log_error(message);
			delete message;
		}
	}
	void Shader::compile_vertex_shader()
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSrc = vertexShaderCode.c_str();
		GLCall(glShaderSource(vertexShader, 1, &vertexSrc, nullptr));
		GLCall(glCompileShader(vertexShader));
		int result;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(vertexShader, length, &length, message);
			log_error(message);
			delete message;
		}
	}
	int Shader::get_uniform_location(const char* name)
	{
		
		GLCall(int location = glGetUniformLocation(program, name));
		// if (location == -1)
		// 	log_error("Warning: uniform %s doesn't exist!", name);
		return location;
	}
	void Shader::set_uniform_1i(const char* name, int value)
	{
		GLCall(glUseProgram(program));
		GLCall(glUniform1i(get_uniform_location(name), value));
	}
	void Shader::set_uniform_1iv(const char* name, int count, int samplers[])
	{
		GLCall(glUseProgram(program));
		glUniform1iv(get_uniform_location(name), count, samplers);
	}
	void Shader::set_uniform_1f(const char* name, float value)
	{
		GLCall(glUseProgram(program));
		GLCall(glUniform1f(get_uniform_location(name), value));
	}
	void Shader::set_uniform_mat4f(const char* name, const Matrix4 &matrix)
	{
		GLCall(glUseProgram(program));
		GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, (float*)&matrix));
	}
	void Shader::set_uniform_vec4f(const char* name, const Vector4 &vector4)
	{
		GLCall(glUseProgram(program));
		GLCall(glUniform4fv(get_uniform_location(name), 1, (float*)&vector4));
	}
}
