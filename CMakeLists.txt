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
option(WITH_DOCS "Generate documantation" OFF)

# Configure C++ standard and compiler verbosity
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
# -----------------------------------------------

# Configure static code analyzer
set(CLANG_TIDY_NAME "clang-tidy")
find_program(CLANG_TIDY_FOUND ${CLANG_TIDY_NAME})
if(CLANG_TIDY_FOUND)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_NAME})
else()
    message("warning: clang-tidy executable not found!")
endif()
# -----------------------------------------------

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

# Add unit tests to build
if(WITH_TESTS)
    add_subdirectory(test)
endif()
# -----------------------------------------------

# Add generation of documentation
if(WITH_DOCS)
    add_subdirectory(docs)
endif()
# -----------------------------------------------
