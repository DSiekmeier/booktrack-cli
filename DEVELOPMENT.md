# Development

If you have any questions or suggestions regarding this project I am happy to hear from you.

## Commit message conventions

To keep the commit history clean please prefix all commit messages with on of the following prefixes:

1. **feature:** This commit will be a directly visible feature for the user, e.g. a new commandline option.
2. **bugfix:** This commit fixes a bug (obviously).
3. **docs:** This commit changes the documentation only, whether it is for the user or the developer community.
4. **refactor:** A code change that neither fixes a bug nor adds a feature, e.g. renaming variables and so on.
5. **chore:** Changes to the build process, tools or update of third party libraries.

## Compiling from source

Building **booktrack-cli** from source can simply be done by using CMake. Nevertheless there is a single Bash script you can also use:

```bash
# Clone the project
git clone http://github.com/dsiekmeier/booktrack-cli

# Buil application with Release configuration
./tools/run-build.sh

# Build application and run the unit tests
./tools/run-build.sh test

# Build application and run the Clang-Tidy linter
./tools/run-build.sh lint
```

Unit tests for **booktrack-cli** are written using [GoogleTest](https://google.github.io/googletest).

The script does not remove the the build directory, so if you want to have a clean build you might want to do this manually (`rm -rf ./build`).

## Generating API documentation

The source code of **booktrack-cli** is (more or less...) annotated using [Doxygen](https://www.doxygen.nl/index.html) comments. This has to be available on your system. You can generate a HTML based documentation via CMake:

```bash
# Build with CMake
cmake -S. -Bbuild -DWITH_DOCS=ON
cmake --build build
```

The result will than be located at `./build/generated_docs/html/`.

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
gcovr -r .. -e ../external/ -e ../test/ --html-details index_gcovr.html
```

The file `index_gcovr.html` is created inside the build folder and contains the results. For more information about gcovr see the [documentation](https://gcovr.com/en/stable/).
