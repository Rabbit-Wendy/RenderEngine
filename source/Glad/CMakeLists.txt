#Glad

#设置源文件路径
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

#文件树结构
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#生成静态库项目
add_library(Glad STATIC ${HEADER_FILES} ${SOURCE_FILES})

#包含头文件路径命令
target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/glad)
target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR)
target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)