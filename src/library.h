#ifndef BOOKTRACK_CLI_LIBRARY_H
#define BOOKTRACK_CLI_LIBRARY_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "book.h"

namespace booktrack_cli {

class Library {
 public:
  Library() = delete;
  explicit Library(const std::string& library_file_path);

  void StoreToFile();
  void Dump() const;
  Library& AddBook(Book book);
  Library& RemoveBookByTitle(std::string title);

 private:
  std::vector<Book> library_books_;
  std::string library_file_path_{};

  void LoadFromFile_();
  std::string ToJsonString_() const;
};

}  // namespace booktrack_cli

#endif
