cmake_minimum_required(VERSION 3.10)

# project name
project(SolarSystem)

# create compile command
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add cpp files
file(GLOB SOURCES "src/*.cpp")

# add headers
include_directories(include)

# executable
add_executable(${PROJECT_NAME} ${SOURCES})

# add glad
target_include_directories(${PROJECT_NAME} PRIVATE dep/glad/include/)
target_sources(${PROJECT_NAME} PRIVATE dep/glad/src/gl.c)

# add glfw
add_subdirectory(dep/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# add glm
add_subdirectory(dep/glm)
target_link_libraries(${PROJECT_NAME} glm)