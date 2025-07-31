cmake_minimum_required(VERSION 3.5)
project(windows)

#搜索当前目录下的所有源文件
aux_source_directory(./ SRC)


#搜索头文件和UI文件
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

#PROJECT_SOURCE_DIR指的是当前PROJECT即windows所处的路径, CMAKE_CURRENT_SOURCE_DIR指的是cmakelist所处的路径
# message("dir1 = "${HEADERS})
# message("dir1 = "${UIS})

#将当前目录下的源文件制作成静态库(只需源文件即可制作成静态库，添加头文件和ui文件是为了显示)
add_library(windows ${SRC} ${HEADERS} ${UIS})
target_link_libraries(windows PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)
