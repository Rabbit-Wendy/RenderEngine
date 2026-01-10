#pragma once

#ifdef RE_BULD_DLL
    #define RE_API __declspec(dllexport)
#else
    #define RE_API __declspec(dllimport)
#endif
