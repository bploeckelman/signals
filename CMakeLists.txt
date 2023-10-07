cmake_minimum_required(VERSION 3.26)
project(signals C)

set(CMAKE_C_STANDARD 99)

set(OPENAL_INCLUDE_DIR "C:/Tools/OpenAL-1.1/include")
set(OPENAL_LIBRARY "C:/Tools/OpenAL-1.1/libs/Win64/OpenAL32.lib")
find_package(OpenAL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
        main.c
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenAL::OpenAL
)
