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
   * @brief Dump the list of books inside the library to std::cout
   */
  void Dump() const;

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

 private:
  std::vector<Book> library_books_;
  std::string library_file_path_{};
  size_t max_used_id_{0};  // Stores the currently maximumx used book id

  void LoadFromFile_();
  std::string ToJsonString_() const;
};

}  // namespace booktrack_cli

#endif
