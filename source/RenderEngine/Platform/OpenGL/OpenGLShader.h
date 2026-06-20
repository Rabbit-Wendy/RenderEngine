#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

namespace RE {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc);  //顶点着色器源代码和片段着色器源代码
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;


        void UpLoadUniformInt(const std::string& name, const int values);

		void UpLoadUniformFloat(const std::string& name, const float values);
		void UpLoadUniformFloat2(const std::string& name, const glm::vec2& values); 
		void UpLoadUniformFloat3(const std::string& name, const glm::vec3& values); 
		void UpLoadUniformFloat4(const std::string& name, const glm::vec4& values); 

        void UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_RendererID;
	};
}