#RenderEngine

#设置源文件路径
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成动态库项目
add_library(RenderEngine SHARED ${HEADER_FILES} ${SOURCE_FILES})

#定义宏
target_compile_definitions(RenderEngine PRIVATE RE_BULD_DLL)

#包含头文件路径命令
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
