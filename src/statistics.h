#ifndef BOOKTRACK_CLI_STATISTICS_H
#define BOOKTRACK_CLI_STATISTICS_H
#include <iostream>

#include <ctime>
#include <string>
#include <unordered_set>

#include <fmt/color.h>
#include <fmt/core.h>

#include "library.h"

namespace booktrack_cli {

struct library_statistics {
  size_t number_of_books;
  float reading_days_per_book;
  size_t authors;
  size_t shelfs;
  std::map<int, size_t> books_per_year{};  // year -> count
};

/**
 * @brief Provides access to statistics about the given library
 */
class Statistics {
 public:
  Statistics() = delete;
  explicit Statistics(const Library& library);

  /**
   * @brief Get the calculated statistics
   */
  inline auto GetStatistics() const { return statistics_; }

  void DumpStatistics();

 private:
  void CalculateReadingDaysPerBook_();
  void CountUniqueAuthors_();
  void CountUniqueShelfs_();
  void CountFinishedBooksPerYear_();

  void DumpGeneralLibraryStatistics_() const;

  std::vector<Book> book_collection_;
  library_statistics statistics_;
};

}  // namespace booktrack_cli

#endif
