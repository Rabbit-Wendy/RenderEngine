#pragma once

#include <string>

namespace RE { 
    class Shader {
    public:
        Shader(const std::string vertexSrc, const std::string fragmentSrc);  //顶点着色器源代码和片段着色器源代码
        ~Shader();

        void bind() const;
        void unbind() const;

    private:
        unsigned int m_RendererID;
    };
}