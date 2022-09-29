find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}-test
    # Tests for the "Book" class
    book_constructor_test.cc
    book_readingtime_test.cc
    book_tojsonstring_test.cc
    book_setdatafromjson_test.cc

    # Tests for the free functions in utilities
    utilities_test.cc
)

target_include_directories(${PROJECT_NAME}-test
    PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME}-test
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME}-lib
)

add_test(${PROJECT_NAME}-test
    ${PROJECT_NAME}-test
)
