#include "utilities.h"

namespace booktrack_cli {

std::vector<int> SplitDateComponents(const std::string& date_string,
                                     const char delimiter) {
  std::vector<int> elements;
  std::stringstream stream(date_string);
  std::string number;
  while (std::getline(stream, number, delimiter)) {
    try {
      auto converted_number = std::stoi(number);
      elements.push_back(converted_number);
    } catch (const std::invalid_argument& ex) {
      return {};
    }
  }
  return elements;
}

void DumpBookCollection(const std::vector<Book> collection) {
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

  for (const auto& book : collection) {
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
  std::cout << "Number of books: " << collection.size() << std::endl
            << std::endl;
}
}  // namespace booktrack_cli
