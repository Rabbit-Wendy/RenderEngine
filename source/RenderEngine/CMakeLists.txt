#RenderEngine

#设置源文件路径
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成动态库项目
add_library(RenderEngine SHARED ${HEADER_FILES} ${SOURCE_FILES})

#定义宏
target_compile_definitions(RenderEngine PRIVATE RE_BUILD_DLL)
target_compile_definitions(RenderEngine PRIVATE GLFW_INCLUDE_NONE)

#链接库路径
target_link_directories(RenderEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

#链接库
target_link_libraries(RenderEngine PRIVATE glfw)
target_link_libraries(RenderEngine PRIVATE OpenGL32)
target_link_libraries(RenderEngine PRIVATE Glad)
target_link_libraries(RenderEngine PRIVATE ImGui)

#包含头文件路径命令
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core/public)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Events/public)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/include/GLFW)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ImGui)

