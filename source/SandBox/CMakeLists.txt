#SandBox

#设置源文件路径
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成可执行项目
add_executable(SandBox ${HEADER_FILES} ${SOURCE_FILES})

#包含头文件路径命令
#target_include_directories(SandBox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../RenderEngine/public)

#链接库路径
target_link_directories(SandBox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

#链接库
target_link_libraries(SandBox PRIVATE RenderEngine)