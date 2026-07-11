#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glad.h>

namespace RE {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

        void UpLoadUniformInt(const std::string& name, const int values);

		void UpLoadUniformFloat(const std::string& name, const float values);
		void UpLoadUniformFloat2(const std::string& name, const glm::vec2& values); 
		void UpLoadUniformFloat3(const std::string& name, const glm::vec3& values); 
		void UpLoadUniformFloat4(const std::string& name, const glm::vec4& values); 

        void UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
        std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		unsigned int m_RendererID;
		std::string m_Name;
	};
}