cmake_minimum_required(VERSION 3.5)

project(crypto)

#搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)


#将当前目录下的源文件制作成静态库(只需源文件即可制作成静态库，添加头文件和ui文件是为了显示)
add_library(crypto ${SRC} ${HEADERS})
target_link_libraries(crypto PRIVATE Qt${QT_VERSION_MAJOR}::Core
    "E:/openssl/OpenSSL-Win64/lib/libcrypto.lib")
