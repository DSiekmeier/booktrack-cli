# Development

## Compiling from source

If you want to compile **booktrack-cli** from source follow the below steps:

```bash
# Clone the project
git clone http://github.com/dsiekmeier/booktrack-cli

# Build with CMake
cmake -S. -Bbuild
cmake --build build

# Run the compiled executable
./build/booktrack-cli --help
```

Unit tests for **booktrack-cli** are written using [GoogleTest](https://google.github.io/googletest).

```bash
# Build with CMake
cmake -S. -Bbuild -DWITH_TESTS=ON
cmake --build build

# Run all tests
./build/test/booktrack-cli-test
```

## Generating API documentation

The source code of **booktrack-cli** is (more or less...) annotated using [Doxygen](https://www.doxygen.nl/index.html) comments. This has to be available on your system. You can generate a HTML based documentation via CMake:

```bash
# Build with CMake
cmake -S. -Bbuild -DWITH_DOCS=ON
cmake --build build
```

The result will than be located at `./build/generated_docs/html/`.

## Static code analyzer

Currently while building the souce code `clang-tidy` is invoked with a small set of rules. The number of rules might grow in future, especially regarding the [C++ Core Guidelines ](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html) and the ["modernize-*"](https://clang.llvm.org/extra/clang-tidy/checks/list.html) rules of clang-tidy. Please be aware that the build might take a little bit longer because of the analyzes.

## Code coverage using gcovr

Measuring code coverage is in an experimental stage currently and activated with the `WITH_TESTS` option which also enables building the unit tests. After the build has been finished execute the follwing commands:

```bash
# Build with CMake
cmake -S. -Bbuild -DWITH_TESTS=ON
cmake --build build

# Run the test suite
cd build
./test/booktrack-cli-test

# Generate html report of code coverage
gcovr -v -r .. -e ../external/ -e ../test/ --html-details index_gcovr.html
```

The file `index_gcovr.html` is created inside the build folder and contains the results. For more information about gcovr see the [documentation](https://gcovr.com/en/stable/).
