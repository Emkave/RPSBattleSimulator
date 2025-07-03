cmake_minimum_required(VERSION 3.31)
project(RPSBattleSimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(RPSBattleSimulator main.cpp
        Object.h
        logic.h
        settings.h)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/glad)
include_directories(${CMAKE_SOURCE_DIR}/include/KHR)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(D:/SFML-3.0.0/include/SFML)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/SFML-3.0.0/lib/cmake/SFML)
set(Ogg_DIR D:/SFML-3.0.0/lib/cmake/Ogg)
find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio Network)

set(VLD_DIR "D:/Visual Leak Detector")
include_directories(${VLD_DIR}/include)
link_directories(${VLD_DIR}/lib/Win64)
add_definitions(-DVLDBUILD)

target_link_libraries(RPSBattleSimulator PRIVATE glfw3 opengl32 SFML::System SFML::Window SFML::Graphics SFML::Audio vld)
target_include_directories(RPSBattleSimulator PRIVATE ${CMAKE_SOURCE_DIR}/glad ${CMAKE_SOURCE_DIR}/include ${GLFW_LIB_DIR})

