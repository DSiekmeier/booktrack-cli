# :books: About booktrack-cli

 **booktrack-cli** is a booktracking application for commandline enthusiasts. One focus of the development is an extensive availability of reading statistics.

:construction: This is a relatively new project and there are still some important features missing. Feel free to give your feedback!

# Features

- Complete functionality is available on the commandline interface
- Libraries are stored in an open, human readable format (JSON)

# Getting Started

Here is a short introduction how to use **booktrack-cli**.

```bash
# Add a book with title only
./booktrack-cli -l ~/my_lib.json add -t "Clean Code"

# Add a book with title and author
./booktrack-cli -l ~/my_lib.json add -t "Refactoring" -a "Martin Fowler"
./booktrack-cli -l ~/my_lib.json add -t "Clean Code" -a "Robert C. Martin"
./booktrack-cli -l ~/my_lib.json add -t "Effective Modern" -a "Scott Meyers"

# List all available books in the given library
./booktrack-cli -l ~/my_lib.json list

# Delete a book from the given library by title
./booktrack-cli -l ~/my_lib.json delete --title "Effective Modern"
```

You can see a full list of commandline options below.

```bash
booktrack_cli
Usage: ./build/booktrack-cli [OPTIONS] SUBCOMMAND

Options:
  -h,--help                   Print this help message and exit
  --version                   Display program version information and exit
  -l,--library TEXT REQUIRED  Set the path of the library

Subcommands:
  list                        List books in the given library
  add                         Add a book to the given library
```

# Development

## Compiling from source

If you want to compile **booktrack-cli** from source follow the below steps:

```bash
# Clone the project
git clone http://github.com/dsiekmeier/booktrack-cli

# Build with CMake
cmake -S. Bbuild
cmake --build build

# Run the compiled executable
./build/booktrack-cli --help
```

Unit tests for **booktrack-cli** are written using [GoogleTest](https://google.github.io/googletest).

```bash
# Build with CMake
cmake -S. Bbuild -DWITH_TESTS=ON
cmake --build build

# Run all tests
./build/test/BooktrackCLI-test
```

## Code complexity

From time to time the code complexity is measured using the [Lizard code complexity analyzer
](http://www.lizard.ws/) to check if there is need for refactoring some parts of the code.

```bash
# install the lizard
pip install lizard

# perform measurement of source folder
python3 -m lizard -s cyclomatic_complexity ./src
```

# Acknowledgements

**booktrack-cli** was written by the help of some awesome open source projects (in alphabetical order):

- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html): for code formatting with the built-in `Chromium` style
- [CLI11](https://cliutils.github.io/CLI11/book/): a modern and feature rich command line parsing library
- [CMake](https://cmake.org/): the tool of choice to build **booktrack-cli**
- [JSON for Modern C++](https://json.nlohmann.me/): making the use of JSON in C++ real fun
- [Lizard](https://pythonlang.dev/repo/terryyin-lizard/): Cyclomatic Complexity Analyzer written in Python
