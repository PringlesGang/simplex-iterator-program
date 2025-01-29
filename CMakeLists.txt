cmake_minimum_required(VERSION 3.16)

project("simplex-iterator")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(Src
        src/simplex.cpp
        src/simplexTable.cpp
        src/fraction.cpp
)

set(Header
        src/simplexTable.h
        src/fraction.h
)

add_executable("simplex-iterator" ${Src} ${Header})

if (MSVC)
    set(InstallDest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
else ()
    set(InstallDest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()
