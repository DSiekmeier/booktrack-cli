#include <string>
#include <vector>

#include <CLI/CLI11.hpp>
#include <nlohmann/json.hpp>

#include "book.h"
#include "cli.h"
#include "library.h"
#include "utilities.h"

using namespace booktrack_cli;

namespace {

void SubcmdList(Library& lib, const CliOptionsList& options) {
  if (options.filter_author.empty() && options.filter_title.empty() &&
      options.filter_shelf.empty()) {
    DumpBookCollection(lib.GetBookCollection());
    return;
  }

  // filter by author
  if (!options.filter_author.empty()) {
    auto filtered_lib = lib.GetBookCollection("author", options.filter_author);
    DumpBookCollection(filtered_lib);
  }

  // filter by title
  if (!options.filter_title.empty()) {
    auto filtered_lib = lib.GetBookCollection("title", options.filter_title);
    DumpBookCollection(filtered_lib);
  }

  // filter by shelf
  if (!options.filter_shelf.empty()) {
    auto filtered_lib = lib.GetBookCollection("shelf", options.filter_shelf);
    DumpBookCollection(filtered_lib);
  }
}

void SubcmdAdd(Library& lib, const CliOptionsAdd& options) {
  Book new_book(options.title, options.author, options.pages, options.shelf);
  new_book.SetId(lib.GetMaxUsedId() + 1);

  // add start reading date
  auto start = SplitDateComponents(options.reading_start, '.');
  if (start.size() == 3) {
    new_book.SetReadingStart(start[0], start[1], start[2]);
  }

  // add end reading date
  auto end = SplitDateComponents(options.reading_end, '.');
  if (end.size() == 3) {
    new_book.SetReadingEnd(end[0], end[1], end[2]);
  }

  lib.AddBook(new_book).StoreToFile();
}

void SubcmdDelete(Library& lib, const CliOptionsDel& options) {
  if (options.id != 0) {
    lib.RemoveBookById(options.id).StoreToFile();
    return;
  }

  if (!options.title.empty()) {
    lib.RemoveBookByTitle(options.title).StoreToFile();
    return;
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  CliOptions options{};
  CLI::App app("booktrack_cli");
  AddCliOptions(app, options);
  CLI11_PARSE(app, argc, argv);

  Library library_from_file(options.library_file_path);

  switch (options.command) {
    case PrimaryCommand::kAdd:
      SubcmdAdd(library_from_file, options.add);
      break;
    case PrimaryCommand::kDelete:
      SubcmdDelete(library_from_file, options.del);
      break;
    case PrimaryCommand::kList:
      SubcmdList(library_from_file, options.list);
      break;
    default:
      break;
  }
}
