cmake_minimum_required(VERSION 3.30)
project(ChessEngine)

set(PROJECT_NAME "chess_engine")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)

FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.hpp)

add_executable(ChessEngine ${SOURCES})

target_include_directories(ChessEngine PRIVATE ${INCLUDE_DIR})

target_link_libraries(ChessEngine PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_options(ChessEngine PRIVATE
    -Wall
)



