# :books: About booktrack-cli

![GitHub release (latest by date)](https://img.shields.io/github/v/release/dsiekmeier/booktrack-cli?style=flat-square) ![GitHub](https://img.shields.io/github/license/dsiekmeier/booktrack-cli?style=flat-square)

**booktrack-cli** is a booktracking application for commandline enthusiasts. One focus of the development is an extensive availability of reading statistics.

## Features

:heavy_check_mark: The complete functionality like adding books, viewing and filtering the library and so on is available on the commandline interface.

:heavy_check_mark: The libraries are stored in an open, human readable format (JSON) without proprietary dependencies.

:heavy_check_mark: Your data belongs to you: no communication with any server is necessary.

## Getting Started

Here is a short introduction how to use **booktrack-cli**.

```bash
# Add a book with title only
./booktrack-cli -l ~/my_lib.json add -t "Clean Code"

# Add some books with title and author
./booktrack-cli -l ~/my_lib.json add -t "Refactoring" -a "Martin Fowler"
./booktrack-cli -l ~/my_lib.json add -t "Clean Code" -a "Robert C. Martin"
./booktrack-cli -l ~/my_lib.json add -t "Effective Modern C++" -a "Scott Meyers"

# List all available books in the given library
./booktrack-cli -l ~/my_lib.json list

# List all books in the given library with a filter (case insensitive)
./booktrack-cli -l ~/my_lib.json list --author "martin fowler"
./booktrack-cli -l ~/my_lib.json list --title "Clean Code"
./booktrack-cli -l ~/my_lib.json list --shelf "programming"

# Delete a book from the given library by title
./booktrack-cli -l ~/my_lib.json delete --by-title "Effective Modern C++"

# Delete a book from the given library by the book id
./booktrack-cli -l ~/my_lib.json delete --by-id 2

# Edit the title of the book from the given library with the book id 4
./booktrack-cli -l ~/my_lib.json edit --by-id 4 --title "Introduction to Algorithms"
```

You can see a full list of commandline options below.

```bash
booktrack_cli
Usage: ./booktrack-cli [OPTIONS] SUBCOMMAND

Options:
  -h,--help                   Print this help message and exit
  --version                   Display program version information and exit
  -l,--library TEXT REQUIRED  Set the path of the library

Subcommands:
  add                         Add a book to the library
  delete                      Delete a book from the library
  list                        List books in the library
  statistics                  Show statistics for loaded library
  details                     Show details for a book
  edit                        Edit a book in the library
```

## Notes

1. **Do not consider the `Book ID` to be immutable:** if one deletes a book entry right in the middle of the library, there will be a gap in the series of book IDs. In future program versions, there will be some "housekeeping" mechanism, which reassigns the book IDs. Invoking the `list` subcommand will never change the book ID and can therefore be used to get the valid state of the book IDs.

2. **Filter options are exclusive:** this means, that currently one can only filter the library with the `list` subcommand by using one of the options at the same time, e.g. `--author` or `--title` but not both. Also note, that the filter is case insensitive but compares the whole given text.

3. **Empty filters are handled as non-existent:** if you add a filter option to the `list` subcommand but leave the value empty, e.g. `list -a ""` then this filter will be ignored. This has the effect, that you cannot filter for books in the library which do not have a `shelf` for example.

# Development

Please refer to [DEVELOPMENT.md](DEVELOPMENT.md) for information about building **booktrack-cli** from source. Any contribution is appreciated.

# Acknowledgements

**booktrack-cli** was written by the help of some awesome open source projects (in alphabetical order):

- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html): for code formatting with the built-in `Chromium` style
- [CLI11](https://cliutils.github.io/CLI11/book/): a modern and feature rich command line parsing library
- [CMake](https://cmake.org/): the tool of choice to build **booktrack-cli**
- [fmt](https://fmt.dev/): A modern formatting library
- [JSON for Modern C++](https://json.nlohmann.me/): making the use of JSON in C++ real fun
