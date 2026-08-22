#RenderEngine

#设置源文件路径
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成动态库项目
add_library(RenderEngine STATIC ${HEADER_FILES} ${SOURCE_FILES})

#定义宏
target_compile_definitions(RenderEngine PRIVATE GLFW_INCLUDE_NONE)
target_compile_definitions(RenderEngine PUBLIC "$<$<CONFIG:Debug>:RE_ENABLE_ASSERTS>")

#链接库路径
target_link_directories(RenderEngine PRIVATE ${CMAKE_SOURCE_DIR}/../bin)
target_link_directories(RenderEngine PRIVATE ${CMAKE_SOURCE_DIR}/../3rdparty)

#链接库
target_link_libraries(RenderEngine PRIVATE glfw3)
target_link_libraries(RenderEngine PRIVATE OpenGL32)
target_link_libraries(RenderEngine PRIVATE Glad)
target_link_libraries(RenderEngine PRIVATE ImGui)

#包含头文件路径命令
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/Glad/include/glad)
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/Glad/include/KHR)
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/Glad/include)
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/GLFW/include/GLFW)
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/GLFW/include)
target_include_directories(RenderEngine PUBLIC ${CMAKE_SOURCE_DIR}/../3rdparty/ImGui)

target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Events)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ImGui)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Renderer)

