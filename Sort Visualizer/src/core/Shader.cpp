#include "Shader.h"
#include "ErrorCheck.h"

Shader::Shader()
    : m_RendererID(0) {}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Create(std::string_view filePath) {
    ShaderProgramSource source = ParseShader(filePath.data());
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(std::string_view name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1ui(std::string_view name, uint32_t value) {
    GLCall(glUniform1ui(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(std::string_view name, int size, const int* value) {
	GLCall(glUniform1iv(GetUniformLocation(name), size, value));
}

void Shader::SetUniform1f(std::string_view name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1fv(std::string_view name, int size, const float* value) {
	GLCall(glUniform1fv(GetUniformLocation(name), size, value));
}

void Shader::SetUniform3f(std::string_view name, float v0, float v1, float v2) {
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(std::string_view name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(std::string_view name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(std::string_view name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int loccation = glGetUniformLocation(m_RendererID, name.data()));
	if (loccation == -1)
		std::cout << "Warning: Uniform " << name << " doesn't exist." << std::endl;

	m_UniformLocationCache[name] = loccation;
	return loccation;
}

ShaderProgramSource Shader::ParseShader(std::string_view filePath) {
	std::ifstream open(filePath.data());

    enum class ShadetType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShadetType type = ShadetType::NONE;

    std::string line;
    std::stringstream ss[2];
    while (getline(open, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos) {
                type = ShadetType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShadetType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(std::string_view vertexShader, std::string_view fragmentShader) {
    uint32_t program = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

uint32_t Shader::CompileShader(uint32_t type, std::string_view source) {
    uint32_t id = glCreateShader(type);
    const char* shader = source.data();
    GLCall(glShaderSource(id, 1, &shader, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Fail to compile shader! " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
	return id;
}