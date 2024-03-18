#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace Tactics
{
	struct Matrix4;
	union Vector4;
	struct Shader
	{
		unsigned int program;
		unsigned int vertexShader;
		unsigned int fragmentShader;
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		Shader();
		Shader::Shader(const std::string filepath);
		void parse_shader_code(const std::string filepath);
		void compile_fragment_shader();
		void compile_vertex_shader();
		void create_shader();
		int get_uniform_location(const char* name);
		void set_uniform_1i(const char* name, int value);
		void set_uniform_1iv(const char* name, int count, int samplers[]);
		void set_uniform_1f(const char* name, float value);
		void set_uniform_mat4f(const char* name, const Matrix4 &matrix);
		void set_uniform_vec4f(const char* name, const Vector4 &vector4);
	};
}
#endif