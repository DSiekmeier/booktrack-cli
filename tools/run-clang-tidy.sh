#!/bin/sh

BUILD_DIR=./build
SOURCE_DIR=./src

cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build $BUILD_DIR -- -j

FILE_LIST=$(find $SOURCE_DIR -iname *.h -o -iname *.cc)

clang-tidy -p $BUILD_DIR $FILE_LIST
