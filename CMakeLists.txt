cmake_minimum_required(VERSION 3.30)
project(ChessEngine)

set(PROJECT_NAME "chess_engine")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libs
include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(sfml catch2)

# Link
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.hpp)

list(FILTER SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# Create Library
add_library(ChessEngineLib ${SOURCES})
target_include_directories(ChessEngineLib PUBLIC ${INCLUDE_DIR})
target_link_libraries(ChessEngineLib PUBLIC sfml-graphics sfml-window sfml-system)
target_compile_options(ChessEngineLib PRIVATE
    -Wall
)

# Main executable
add_executable(ChessEngine ${SRC_DIR}/main.cpp) 
target_link_libraries(ChessEngine PRIVATE ChessEngineLib)
target_include_directories(ChessEngine PRIVATE ${INCLUDE_DIR})


# Testing
enable_testing()
include(CTest)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(ChessEngineTests ${TEST_SOURCES})

target_include_directories(ChessEngineTests PRIVATE ${INCLUDE_DIR})
target_link_libraries(ChessEngineTests PRIVATE ChessEngineLib Catch2::Catch2WithMain)

include(${CMAKE_SOURCE_DIR}/build/_deps/catch2-src/extras/Catch.cmake)
catch_discover_tests(ChessEngineTests)



