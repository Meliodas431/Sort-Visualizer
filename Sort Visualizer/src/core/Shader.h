#pragma once
#include "Headers.h"
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	uint32_t m_RendererID;
	std::string_view m_FilePath;
	std::unordered_map<std::string_view, int> m_UniformLocationCache;
public:
	Shader();
	~Shader();

	void Create(std::string_view filePath);
	void Bind() const;
	void Unbind() const;

	void SetUniform1i(std::string_view name, int value);
	void SetUniform1ui(std::string_view name, uint32_t value);
	void SetUniform1iv(std::string_view name, int size, const int* value);
	void SetUniform1f(std::string_view name, float value);
	void SetUniform1fv(std::string_view name, int size, const float* value);
	void SetUniform3f(std::string_view name, float v0, float v1, float v2);
	void SetUniform4f(std::string_view name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(std::string_view name, const glm::mat4& matrix);

private:
	int GetUniformLocation(std::string_view name);
	ShaderProgramSource ParseShader(std::string_view filePath);
	uint32_t CreateShader(std::string_view vertexShader, std::string_view fragmentShader);
	uint32_t CompileShader(uint32_t type, std::string_view source);
};