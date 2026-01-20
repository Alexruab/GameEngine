# general info
cmake_minimum_required(VERSION 3.30)

# cpp options
set(CMAKE_CXX_STANDARD 20)

# common options
set(PROJECT_NAME GameEngines)
project(${PROJECT_NAME} VERSION 1.0.0)
add_executable(${PROJECT_NAME} Source/main.cpp)

set(ENGINE_SOURCES
    Source/Core/Engine.cpp
    Source/Core/Engine.h
    .clang-format
)

add_library(${PROJECT_NAME}Lib ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

# folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER Engine)

# include helpers
include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
