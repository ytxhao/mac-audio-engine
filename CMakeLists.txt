cmake_minimum_required(VERSION 3.19)
project(mac_audio_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation")
add_compile_options(-x objective-c++)
set(SRC
        main.cpp
        )
add_executable(mac_audio_engine ${SRC})