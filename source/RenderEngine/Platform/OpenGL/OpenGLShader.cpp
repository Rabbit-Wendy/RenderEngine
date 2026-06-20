#include "Log.h"
#include "OpenGLShader.h"
#include <glad.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

RE::OpenGLShader::OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		RE_LOG_CORE_ERROR("{0}", infoLog.data());
		RE_CORE_ASSERT(false, "Vertext shader complication failure!");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		RE_LOG_CORE_ERROR("{0}", infoLog.data());
		RE_CORE_ASSERT(false, "Fragment shader complication failure!");
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();
	GLuint program = m_RendererID;

	// Attach our shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		RE_LOG_CORE_ERROR("{0}", infoLog.data());
		RE_CORE_ASSERT(false, "OpenGLShader Link failure!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
}

RE::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
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
