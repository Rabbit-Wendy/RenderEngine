#include "Log.h"
#include "OpenGLShader.h"
#include <glad.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>


static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	else if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	RE_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}

RE::OpenGLShader::OpenGLShader(const std::string& filePath)
{  
	std::string source = ReadFile(filePath);
    std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
    Compile(shaderSources);
}

RE::OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    Compile(sources);
}

RE::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

std::string RE::OpenGLShader::ReadFile(const std::string& filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		RE_CORE_ERROR("Could not open file '{0}'", filePath);
	}
	return result;
}

std::unordered_map<GLenum, std::string> RE::OpenGLShader::PreProcess(const std::string& source)
{
    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
		RE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
        size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		RE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);
        shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - nextLinePos);
    }
	return shaderSources;
}

void RE::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	GLuint program = glCreateProgram();
	std::vector<GLuint> shaderIDs;
	shaderIDs.reserve(shaderSources.size());
	for (auto& kv : shaderSources)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			RE_LOG_CORE_ERROR("{0}", infoLog.data());
			RE_CORE_ASSERT(false, "shader complication failure!");
			break;
		}
		glAttachShader(program, shader);
		shaderIDs.push_back(shader);
	}

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);
		for (auto id : shaderIDs)
			glDeleteShader(id);

		RE_LOG_CORE_ERROR("{0}", infoLog.data());
		RE_CORE_ASSERT(false, "OpenGLShader Link failure!");
		return;
	}

	m_RendererID = program;

	for (auto id : shaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}

void RE::OpenGLShader::bind() const
{
	glUseProgram(m_RendererID);
}

void RE::OpenGLShader::unbind() const
{
	glUseProgram(0);
}

void RE::OpenGLShader::UpLoadUniformInt(const std::string& name, const int value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}

void RE::OpenGLShader::UpLoadUniformFloat(const std::string& name, const float value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(location, value);
}

void RE::OpenGLShader::UpLoadUniformFloat2(const std::string& name, const glm::vec2& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform2f(location, values.x, values.y);
}

void RE::OpenGLShader::UpLoadUniformFloat3(const std::string& name, const glm::vec3& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, values.x, values.y, values.z);
}

void RE::OpenGLShader::UpLoadUniformFloat4(const std::string& name, const glm::vec4& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, values.x, values.y, values.z, values.w);
}

void RE::OpenGLShader::UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void RE::OpenGLShader::UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
