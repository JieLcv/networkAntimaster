cmake_minimum_required(VERSION 3.10.2)
project(server_antiMaster)

set(CMAKE_CXX_STANDARD 17)

link_directories(/usr/local/ssl/lib64)
link_directories(/usr/lib/x86_64-linux-gnu/)
link_directories(/usr/local/ssl/lib64)
link_directories(/usr/local/lib)
#添加头文件目录，这样就可以直接包含其他目录中的头文件了
include_directories(
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/http
        ${PROJECT_SOURCE_DIR}/reactor
        ${PROJECT_SOURCE_DIR}/tcp
        ${PROJECT_SOURCE_DIR}/thread
        ${PROJECT_SOURCE_DIR}/serialize
        ${PROJECT_SOURCE_DIR}/crypto
        ${PROJECT_SOURCE_DIR}/game
        ${PROJECT_SOURCE_DIR}/database
        /usr/local/ssl/include/
        /usr/include/mysql
        /usr/local/include/
)
#测试用例
include_directories(${PROJECT_SOURCE_DIR}/test)
#添加子目录
add_subdirectory(common)
add_subdirectory(http)
add_subdirectory(reactor)
add_subdirectory(tcp)
add_subdirectory(thread)
add_subdirectory(crypto)
add_subdirectory(serialize)
add_subdirectory(game)
add_subdirectory(database)
#测试用目录
add_subdirectory(test)

#链接子目录中的静态库文件 前面的可以链接后面的
link_libraries(tcp http reactor thread common test01 mycrypto serialize game database)

#指定可执行文件生成到对应的目录中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(server_antiMaster main.cpp
)
