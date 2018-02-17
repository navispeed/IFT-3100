cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_STANDARD 11)

set(OF_MAIN_DIR /Users/greg/Downloads/of_v0.9.8_osx_release)
project(ift-3100)

file( GLOB_RECURSE SRC src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp src/**/*.h external/**/src/*)
add_executable(app ${SRC})


include(includelist.cmake)
include(test.cmake)
include_directories(./src)
#include_directories(/usr/include/c++/4.2.1 /Applications/Xcode.app/Contents/Developer/usr )

#find_package(PkgConfig REQUIRED)
#pkg_search_module(CAIRO REQUIRED cairo)
#pkg_search_module(ZLIB REQUIRED zlib)
#pkg_search_module(GLEW REQUIRED glew)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall"
#configure_file(${FMODEX_DIR}/lib/osx/libfmodex.dylib ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#add_custom_target(XCode COMMAND make -C .. -j8)
add_custom_target(XCode COMMAND cd .. && xcodebuild)
add_custom_target(XCodeDebug COMMAND cd .. && xcodebuild -scheme "IFT-3100 Debug")