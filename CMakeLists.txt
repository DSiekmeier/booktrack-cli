cmake_minimum_required(VERSION 3.16)

project("booktrack-cli"
	VERSION 0.1.0
	DESCRIPTION "A book tracking app for shell enthusiasts."
    LANGUAGES CXX
)

configure_file(
    src/version.h.in
    version.h
)

include(FetchContent)
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG        v2.2.0
)
FetchContent_MakeAvailable(cli11)

find_package(nlohmann_json 3.7.0 REQUIRED)

option(WITH_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME}-lib
    src/book.cc
    src/library.cc
    src/utilities.cc
)

add_executable(${PROJECT_NAME}
    src/main.cc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        nlohmann_json::nlohmann_json
        CLI11::CLI11
        ${PROJECT_NAME}-lib
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}
)

if(WITH_TESTS)
    add_subdirectory(test)
endif()
