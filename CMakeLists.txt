cmake_minimum_required(VERSION 3.23)
project(CGPrakt2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CGPrakt2
        src/CGUtilities.cpp
        src/CGUtilities.h
        src/color.cpp
        src/color.h
        src/main.cpp
        src/rgbimage.cpp
        src/rgbimage.h
        src/SimpleRayTracer.cpp
        src/SimpleRayTracer.h
        src/vector.cpp
        src/vector.h)
