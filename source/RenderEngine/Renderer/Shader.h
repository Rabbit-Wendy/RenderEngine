#pragma once

#include <string>
#include <glm/glm.hpp>

namespace RE { 
    class Shader {
    public:
        Shader(const std::string vertexSrc, const std::string fragmentSrc);  //顶点着色器源代码和片段着色器源代码
        ~Shader();

        void bind() const;
        void unbind() const;

        void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix); //上传一个uniform矩阵

    private:
        unsigned int m_RendererID;
    };
}