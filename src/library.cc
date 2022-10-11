#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "library.h"
using namespace booktrack_cli;

Library::Library(const std::string& library_file_path)
    : library_file_path_{library_file_path} {
  LoadFromFile_();
}

void Library::LoadFromFile_() {
  std::ifstream ifs{library_file_path_};
  if (!ifs.good()) {
    return;
  }

  std::string content;
  content.assign((std::istreambuf_iterator<char>(ifs)),
                 (std::istreambuf_iterator<char>()));

  auto library_books_json = nlohmann::json::parse(content);

  for (const auto& book : library_books_json) {
    Book new_book;
    new_book.SetDataFromJson(book);
    AddBook(new_book);

    // Update the maximum used book id
    auto current_id = new_book.GetId();
    if (current_id > max_used_id_) {
      max_used_id_ = current_id;
    }
  }
}

void Library::StoreToFile() {
  if (library_file_path_ == "") {
    std::cout << "No library file defined." << std::endl;
    return;
  }

  std::ofstream ofs{library_file_path_};
  if (ofs.good()) {
    auto lib_json_string = ToJsonString_();
    ofs << lib_json_string;
  }
}

Library& Library::AddBook(Book book) {
  library_books_.push_back(book);
  return *this;
}

Library& Library::RemoveBookByTitle(std::string title) {
  auto it_begin = library_books_.begin();
  auto it_end = library_books_.end();

  auto it = std::remove_if(it_begin, it_end, [title](const Book& book) {
    return book.GetTitle() == title;
  });

  library_books_.erase(it, library_books_.end());

  return *this;
}

Library& Library::RemoveBookById(size_t id) {
  auto it_begin = library_books_.begin();
  auto it_end = library_books_.end();

  auto it = std::remove_if(
      it_begin, it_end, [id](const Book& book) { return book.GetId() == id; });

  library_books_.erase(it, library_books_.end());

  return *this;
}

std::string Library::ToJsonString_() const {
  json collection;
  for (const auto& book : library_books_) {
    json book_parsed = json::parse(book.ToJsonString());
    collection.push_back(book_parsed);
  }

  return collection.dump();
}

std::vector<Book> Library::GetBookCollection(const std::string& filter,
                                             const std::string& value) const {
  if (filter.empty()) {
    return library_books_;
  }

  std::string value_lowercase;
  std::transform(value.begin(), value.end(),
                 std::back_inserter(value_lowercase), tolower);

  std::vector<Book> filter_list;
  if (filter == "author") {
    for (const auto& book : library_books_) {
      std::string current_author = book.GetAuthor();
      std::string current_author_lowercase;
      std::transform(current_author.begin(), current_author.end(),
                     std::back_inserter(current_author_lowercase), tolower);
      if (current_author_lowercase == value_lowercase) {
        filter_list.push_back(book);
      }
    }
  } else if (filter == "title") {
    for (const auto& book : library_books_) {
      std::string current_title = book.GetTitle();
      std::string current_title_lowercase;
      std::transform(current_title.begin(), current_title.end(),
                     std::back_inserter(current_title_lowercase), tolower);
      if (current_title_lowercase == value_lowercase) {
        filter_list.push_back(book);
      }
    }
  } else if (filter == "shelf") {
    for (const auto& book : library_books_) {
      std::string current_shelf = book.GetShelf();
      std::string current_shelf_lowercase;
      std::transform(current_shelf.begin(), current_shelf.end(),
                     std::back_inserter(current_shelf_lowercase), tolower);
      if (current_shelf_lowercase == value_lowercase) {
        filter_list.push_back(book);
      }
    }
  }
  return filter_list;
}
