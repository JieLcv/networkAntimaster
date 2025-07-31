# Install script for directory: /home/jiege/projects/network-antiMaster/server-antiMaster

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/common/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/http/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/reactor/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/tcp/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/thread/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/crypto/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/serialize/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/game/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/database/cmake_install.cmake")
  include("/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/jiege/projects/network-antiMaster/server-antiMaster/cmake-build-remote-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
