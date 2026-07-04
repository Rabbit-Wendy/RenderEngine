#pragma once

#include <memory>

#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <sstream>
#include <functional>

#include <stdint.h>
#include <string>



#define BIT(x)  (1 << x)


#ifdef RE_ENABLE_ASSERTS
    #define RE_ASSERT(x, ...) { if(!(x)) { RE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define RE_CORE_ASSERT(x, ...) { if(!(x)) { RE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define RE_ASSERT(x, ...)
    #define RE_CORE_ASSERT(x, ...)
#endif

#define RE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace RE
{ 
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

