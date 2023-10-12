cmake_minimum_required(VERSION 3.10)

# project name
project(SolarSystem)

# executable
add_executable(${PROJECT_NAME} main.cpp)

# create compile command
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add glad
target_include_directories(${PROJECT_NAME} PRIVATE dep/glad/include/)
target_sources(${PROJECT_NAME} PRIVATE dep/glad/src/gl.c)

# add glfw
add_subdirectory(dep/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# add glm
add_subdirectory(dep/glm)
target_link_libraries(${PROJECT_NAME} glm)