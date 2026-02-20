#RE最外层

#指定cmake最低版本
cmake_minimum_required(VERSION 3.15)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)
#要求使用指定的C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#添加 /utf-8 编译选项
add_compile_options(/utf-8)

#指定项目名称
project(RenderEngine)

#设置启动项目
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SandBox)

#设置生成可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
#设置生成动态库路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

#添加子目录
add_subdirectory(RenderEngine)
add_subdirectory(SandBox)
add_subdirectory(GLFW)