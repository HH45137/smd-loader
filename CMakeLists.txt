cmake_minimum_required(VERSION 3.29)
project(smd_loader)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)

add_executable(smd_loader main.cpp
        smd_loader.h)

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
