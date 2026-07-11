#include <string>
#include "Core.h"

#pragma once

namespace RE { 
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}