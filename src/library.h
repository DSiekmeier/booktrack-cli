#ifndef BOOKTRACK_CLI_LIBRARY_H
#define BOOKTRACK_CLI_LIBRARY_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "book.h"

namespace booktrack_cli {

/**
 * @brief Represents a collection of books
 * @details The Library class is a collection of tracked books. On the file
 * system a single library corresponds to one JSON file.
 *
 */
class Library {
 public:
  Library() = delete;

  /**
   * @brief Construct a new Library object
   */
  explicit Library(const std::string& library_file_path);

  /**
   * @brief Write the library with all containing books to the file system
   */
  void StoreToFile();

  /**
   * @brief Add a new book to the library
   */
  Library& AddBook(Book book);

  /**
   * @brief Remove the book with \p title from the library
   */
  Library& RemoveBookByTitle(std::string title);

  /**
   * @brief Remove the book with \p id from the library
   */
  Library& RemoveBookById(size_t id);

  /**
   * @brief Get the currently maximum used book id
   */
  inline auto GetMaxUsedId() const { return max_used_id_; }

  /**
   * @brief Get the complete library as a vector of Books by filter
   *
   * The filter is currently a simple string which has to match of one the
   * values described at parameter \p filter. The comparison with \p value will
   * is case insensitive.
   *
   * @param[in] filter  One of the values [author|title]
   * @param[in] value   The value to search for
   *
   * @return A vector of Books matching \p filter and \p value
   */
  std::vector<Book> GetBookCollection(const std::string& filter = "",
                                      const std::string& value = "") const;

 private:
  std::vector<Book> library_books_;
  std::string library_file_path_{};
  size_t max_used_id_{0};  // Stores the currently maximumx used book id

  void LoadFromFile_();
  std::string ToJsonString_() const;
};

}  // namespace booktrack_cli

#endif
