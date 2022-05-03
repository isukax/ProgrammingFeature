# TODO Test Framework

cmake_minimum_required(VERSION 3.21)

set(project_name "ProgrammingFeatures")
project(${project_name})

# Library
file(GLOB_RECURSE src src/TemplateLib/*.cpp src/TemplateLib/*.h)
add_library(TemplateLib SHARED ${src})

# Executable
file(GLOB_RECURSE src src/JIT/*.cpp src/JIT/*.h)
add_executable(JIT ${src})

file(GLOB_RECURSE src src/Template/*.cpp src/Template/*.h)
add_executable(Template ${src})

# Linker
# link_directories("build/src/TemplateLib/Debug")
target_include_directories(Template PRIVATE "src/TemplateLib")
target_link_libraries(Template TemplateLib)