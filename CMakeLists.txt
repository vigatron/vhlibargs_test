cmake_minimum_required(VERSION 3.16)
project(vhlibargs_test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#
add_subdirectory(src/extmods/vhlibplatform)

#
add_subdirectory(src/extmods/vhlibargs)


add_compile_definitions(
    VER_MAJ=${PROJECT_VERSION_MAJOR}
    VER_MIN=${PROJECT_VERSION_MINOR}
    VER_PAT=${PROJECT_VERSION_PATCH}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/main.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    vhlib_platform
    vhlib_args
)
