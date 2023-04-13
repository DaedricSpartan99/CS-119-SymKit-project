cmake_minimum_required(VERSION 3.1)
set(CMAKE_BUILD_TYPE Release)

project(symkit)

include_directories(include)

#add sources
file(GLOB SOURCES "engine/*.cpp" "graph/*.cpp")

add_library(symkit STATIC ${SOURCES})

set_target_properties(symkit PROPERTIES

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) -Wall -Werror")
endif()

if (MSVC)
    set (CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) /W4")
endif()

