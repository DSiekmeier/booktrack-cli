#include <string>
#include <vector>

#include <CLI/CLI11.hpp>
#include <nlohmann/json.hpp>

#include <version.h>
#include "book.h"
#include "cli.h"
#include "library.h"
#include "utilities.h"

using namespace booktrack_cli;

namespace {

void SubcmdList(const CliOptions& options) {
  Library library_from_file(options.library_file_path);
  library_from_file.Dump();
}

void SubcmdAdd(const CliOptions& options) {
  Library library_from_file(options.library_file_path);
  Book new_book(options.add.title, options.add.author, options.add.pages,
                options.add.shelf);
  new_book.SetId(library_from_file.GetMaxUsedId() + 1);

  // add start reading date
  auto start = SplitDateComponents(options.add.reading_start, '.');
  if (start.size() == 3) {
    new_book.SetReadingStart(start[0], start[1], start[2]);
  }

  // add end reading date
  auto end = SplitDateComponents(options.add.reading_end, '.');
  if (end.size() == 3) {
    new_book.SetReadingEnd(end[0], end[1], end[2]);
  }

  library_from_file.AddBook(new_book).StoreToFile();
}

void SubcmdDelete(const CliOptions& options) {
  Library library_from_file(options.library_file_path);
  library_from_file.RemoveBookByTitle(options.del.title).StoreToFile();
}

void AddCliOptions(CLI::App& app, CliOptions& options) {
  // add main options
  app.set_version_flag("--version", []() {
    std::stringstream version_string;
    version_string << BOOKTRACK_CLI_VERSION_MAJOR << "."
                   << BOOKTRACK_CLI_VERSION_MINOR << "."
                   << BOOKTRACK_CLI_VERSION_PATCH;
    return "booktrack-cli v" + version_string.str();
  });

  app.add_option("-l,--library,", options.library_file_path,
                 "Set the path of the library")
      ->mandatory();
  app.require_subcommand();

  // add subcommand "list" with options
  app.add_subcommand("list", "List books in the library")
      ->callback([&options]() { SubcmdList(options); });

  // add subcommand "add" with options
  auto sub_add = app.add_subcommand("add", "Add a book to the library")
                     ->callback([&options]() { SubcmdAdd(options); });
  sub_add->add_option("-t,--title", options.add.title, "")->mandatory();
  sub_add->add_option("-a,--author", options.add.author, "");
  sub_add->add_option("-p,--pages", options.add.pages, "");
  sub_add->add_option("-s,--shelf", options.add.shelf, "");
  sub_add->add_option("--reading-start", options.add.reading_start);
  sub_add->add_option("--reading-end", options.add.reading_end);

  // add subcommand "delete" with options
  auto sub_delete =
      app.add_subcommand("delete", "Delete a book from the library")
          ->callback([&options]() { SubcmdDelete(options); });
  sub_delete->add_option("--by-title", options.del.title, "")->mandatory();
}

}  // namespace

int main(int argc, char* argv[]) {
  CliOptions options{};
  CLI::App app("booktrack_cli");
  AddCliOptions(app, options);
  CLI11_PARSE(app, argc, argv);
}
