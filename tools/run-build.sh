#!/usr/bin/env bash

# Configuration
BUILD_DIR=./build
SOURCE_DIR=.

print_usage() {
    echo "Unknown argument."
    echo "Usage:"
    echo "  run-build [lint | test]"
}

# build booktrack-cli in release configuration
build_release() {
    cmake -S${SOURCE_DIR} -B${BUILD_DIR} -DCMAKE_BUILD_TYPE=Release
    cmake --build ${BUILD_DIR} -- -j
}

# build and run unit tests
build_and_run_tests() {
    cmake -S${SOURCE_DIR} -B${BUILD_DIR} -DWITH_TESTS=ON
    cmake --build ${BUILD_DIR} -- -j
    ./build/test/booktrack-cli-test
}

# run clang-tidy checks
build_and_run_lint() {
    CLANG_TIDY_BASE=./src

    cmake -S$SOURCE_DIR -B$BUILD_DIR -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cmake --build $BUILD_DIR -- -j

    FILE_LIST=$(find $CLANG_TIDY_BASE -iname *.h -o -iname *.cc)

    clang-tidy -p $BUILD_DIR $FILE_LIST
}

# commandline parsing
COMMAND=$1
if [ -z ${COMMAND} ]; then
    build_release
elif [ ${COMMAND} = "lint" ]; then
    build_and_run_lint
elif [ ${COMMAND} = "test" ]; then
    build_and_run_tests
else
    print_usage
fi
