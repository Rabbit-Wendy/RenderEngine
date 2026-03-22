#ImGui

#设置源文件路径
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成静态库项目
add_library(ImGui STATIC ${HEADER_FILES} ${SOURCE_FILES})

#包含头文件路径命令
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backends)