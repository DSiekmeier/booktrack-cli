#include <exception>
#include <string>
#include <vector>

#include <CLI/CLI11.hpp>
#include <nlohmann/json.hpp>

#include "book.h"
#include "cli.h"
#include "details.h"
#include "library.h"
#include "statistics.h"
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
    auto filtered_lib =
        lib.GetBookCollection(FilterClass::kAuthor, options.filter_author);
    DumpBookCollection(filtered_lib);
  }

  // filter by title
  if (!options.filter_title.empty()) {
    auto filtered_lib =
        lib.GetBookCollection(FilterClass::kTitle, options.filter_title);
    DumpBookCollection(filtered_lib);
  }

  // filter by shelf
  if (!options.filter_shelf.empty()) {
    auto filtered_lib =
        lib.GetBookCollection(FilterClass::kShelf, options.filter_shelf);
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

void SubcmdStatistics(Library& lib,
                      [[maybe_unused]] const CliOptionsStatistics& options) {
  Statistics stats(lib);
  stats.DumpStatistics();
}

void SubcmdDetails(Library& lib, const CliOptionsDetails& options) {
  // DumpBookDetails(options.id);
  auto check_exist = lib.GetBookById(options.id);
  if (check_exist.has_value()) {
    auto book = check_exist.value();
    DumpBookDetails(book);
  } else {
    std::cout << "Could not find a book with id: " << options.id << ".\n";
  }
}

void SubcmdEdit(Library& lib, [[maybe_unused]] const CliOptionsEdit& options) {
  auto check_exist = lib.GetBookById(options.id);

  if (check_exist.has_value()) {
    auto book = check_exist.value();
    auto changes = options.changeset;

    // update book
    if (!changes.title.empty()) {
      book.SetTitle(changes.title);
    }

    if (!changes.author.empty()) {
      book.SetAuthor(changes.author);
    }

    book.SetPages(changes.pages);

    // Update library
    lib.RemoveBookById(book.GetId());
    lib.AddBook(book).StoreToFile();
  } else {
    std::cout << "Could not find a book with id: " << options.id << ".\n";
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  CliOptions options{};
  CLI::App app("booktrack_cli");
  AddCliOptions(app, options);
  CLI11_PARSE(app, argc, argv);

  try {
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
      case PrimaryCommand::kStatistics:
        SubcmdStatistics(library_from_file, options.statistics);
        break;
      case PrimaryCommand::kDetails:
        SubcmdDetails(library_from_file, options.details);
        break;
      case PrimaryCommand::kEdit:
        SubcmdEdit(library_from_file, options.edit);
        break;
      default:
        break;
    }
  } catch (const nlohmann::json::exception& ex) {
    std::cout << "Failed to load the library. :-(" << '\n';
    std::cout << "details:" << '\n';
    std::cout << "   " << ex.what() << '\n';
  } catch (const std::exception& ex) {
    std::cout << "Some unknown error occurred. :-(\n";
    std::cout << "details:" << '\n';
    std::cout << "   " << ex.what() << '\n';
  }
}
