#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <sstream>
#include <functional>



#ifdef RE_BUILD_DLL
    #define RE_API __declspec(dllexport)
#else
    #define RE_API __declspec(dllimport)
#endif

#define BIT(x)  (1 << x)
