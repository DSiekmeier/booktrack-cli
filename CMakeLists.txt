cmake_minimum_required(VERSION 3.16)

# PROJECT CONFIGURATION =============================================
project("booktrack-cli"
	VERSION 0.4.1
	DESCRIPTION "A book tracking app for shell enthusiasts."
    HOMEPAGE_URL "https://github.com/DSiekmeier/booktrack-cli"
    LANGUAGES CXX
)

configure_file(
    src/version.h.in
    version.h
)
# ===================================================================

# BUILD CONFIGURATION ===============================================
option(WITH_TESTS "Build tests" OFF)
option(WITH_DOCS "Generate documentation" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
# ===================================================================

# EXTERNAL BUILDS ===================================================
add_subdirectory(external/fmt)
# ===================================================================

# BUILD LIBRARY =====================================================
add_library(${PROJECT_NAME}-lib OBJECT
    src/book.cc
    src/cli.cc
    src/details.cc
    src/library.cc
    src/statistics.cc
    src/utilities.cc
)

target_include_directories(${PROJECT_NAME}-lib
    PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME}-lib
    PRIVATE
        fmt::fmt
)
# ===================================================================

# BUILD APPLICATION =================================================
add_executable(${PROJECT_NAME}
    src/main.cc
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}-lib
        fmt::fmt
)
# ===================================================================

# ADD UNIT TESTS TO BUILD ===========================================
if(WITH_TESTS)
    # set flags for code coverage
    SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage")
    SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

    add_subdirectory(test)
endif()
# ===================================================================

# ADD GENERATION OF DOCUMENTATION ===================================
if(WITH_DOCS)
    add_subdirectory(docs)
endif()
# ===================================================================
