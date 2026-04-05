cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "mmolch_qtutil_translation_loader")
set(PROJECT_VERSION "1.0.0")

project(${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS
    Core
)

qt_standard_project_setup()


add_library(${PROJECT_NAME} STATIC
    include/mmolch/qtutil_translation_loader.h
    src/qtutil_translation_loader.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

if(CMAKE_CURRENT_LIST_DIR STREQUAL ${CMAKE_SOURCE_DIR})
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )
    endif ()

    add_subdirectory(example)
endif()
