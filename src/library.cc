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

std::string Library::ToJsonString_() const {
  json collection;
  for (const auto& book : library_books_) {
    json book_parsed = json::parse(book.ToJsonString());
    collection.push_back(book_parsed);
  }

  return collection.dump();
}

void Library::Dump() const {
  constexpr size_t kLengthId{4};
  constexpr size_t kLengthAuthor{25};
  constexpr size_t kLengthTitle{40};
  constexpr size_t kLengthPages{7};
  constexpr size_t kLengthShelf{15};
  constexpr size_t kLengthReading{6};

  std::cout << std::endl << std::left;
  std::cout << std::setw(kLengthId) << "ID";
  std::cout << std::setw(kLengthAuthor) << "AUTHOR";
  std::cout << std::setw(kLengthTitle) << "TITLE";
  std::cout << std::setw(kLengthPages) << "PAGES";
  std::cout << std::setw(kLengthShelf) << "SHELF";
  std::cout << std::setw(kLengthReading) << "DAYS";
  std::cout << std::endl;
  for (size_t i = 0; i < (kLengthId + kLengthAuthor + kLengthTitle +
                          kLengthPages + kLengthShelf + kLengthReading);
       ++i) {
    std::cout << "-";
  }
  std::cout << std::endl;

  for (const auto& book : library_books_) {
    std::cout << std::left;
    std::cout << std::setw(kLengthId) << book.GetId();
    std::cout << std::setw(kLengthAuthor) << book.GetAuthor();
    std::cout << std::setw(kLengthTitle) << book.GetTitle();
    std::cout << std::setw(kLengthPages) << book.GetPages();
    std::cout << std::setw(kLengthShelf) << book.GetShelf();
    std::cout << std::setw(kLengthReading) << book.GetReadingTimeDays();
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Number of books: " << library_books_.size() << std::endl
            << std::endl;
}
