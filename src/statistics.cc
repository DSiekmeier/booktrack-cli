#include <algorithm>

#include "statistics.h"

using namespace booktrack_cli;

Statistics::Statistics(const Library& library)
    : book_collection_{library.GetBookCollection()} {
  statistics_.number_of_books = book_collection_.size();
  CalculateReadingDaysPerBook_();
  CountUniqueAuthors_();
  CountUniqueShelfs_();
  CountFinishedBooksPerYear_();
}

void Statistics::DumpStatistics() {
  DumpGeneralLibraryStatistics_();
}

void Statistics::CountUniqueShelfs_() {
  std::unordered_set<std::string> shelfs;
  for (const auto& book : book_collection_) {
    auto current_shelf = book.GetShelf();
    if (!current_shelf.empty())
      shelfs.insert(current_shelf);
  }
  statistics_.shelfs = shelfs.size();
}

void Statistics::CountUniqueAuthors_() {
  std::unordered_set<std::string> authors;
  for (const auto& book : book_collection_) {
    auto current_author = book.GetAuthor();
    if (!current_author.empty())
      authors.insert(current_author);
  }
  statistics_.authors = authors.size();
}

void Statistics::CalculateReadingDaysPerBook_() {
  auto reading_days =
      std::accumulate(book_collection_.begin(), book_collection_.end(), 0,
                      [](int accumulator, const Book& book) {
                        return accumulator + book.GetReadingTimeDays();
                      });

  statistics_.reading_days_per_book =
      (reading_days == 0) ? 0
                          : reading_days / (statistics_.number_of_books * 1.0);
}

void Statistics::CountFinishedBooksPerYear_() {
  for (const auto& book : book_collection_) {
    auto reading_end = book.GetReadingEnd();
    struct tm buf;
    localtime_r(&reading_end, &buf);
    auto current_year = buf.tm_year + 1900;
    statistics_.books_per_year[current_year] += 1;
  }
}

void Statistics::DumpGeneralLibraryStatistics_() const {
  constexpr size_t kLengthPretext{35};

  // section
  fmt::print(fmt::emphasis::underline, "Library Statistics Summary\n");
  fmt::print("\n");

  fmt::print("{:{}}", "Number of books in the library", kLengthPretext);
  fmt::print(": {}\n",
             fmt::styled(statistics_.number_of_books, fmt::emphasis::bold));

  fmt::print("{:{}}", "Average reading time per book", kLengthPretext);
  fmt::print(": {0:.2f} days\n", fmt::styled(statistics_.reading_days_per_book,
                                             fmt::emphasis::bold));

  fmt::print("{:{}}", "Number of authors in the library", kLengthPretext);
  fmt::print(": {}\n", fmt::styled(statistics_.authors, fmt::emphasis::bold));

  fmt::print("{:{}}", "Number of shelfs in the library", kLengthPretext);
  fmt::print(": {}\n", fmt::styled(statistics_.shelfs, fmt::emphasis::bold));

  fmt::print("\n");

  // section
  fmt::print(fmt::emphasis::underline, "Books finished by year\n");
  fmt::print("\n");

  for (const auto& year : statistics_.books_per_year) {
    fmt::print("{}: {} books\n", year.first,
               fmt::styled(year.second, fmt::emphasis::bold));
  }

  fmt::print("\n");
}