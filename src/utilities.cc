#include <fmt/color.h>
#include <fmt/core.h>

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

std::string AbbreviateTextIfNecessary(const std::string& text,
                                      const size_t max_length) {
  const std::string replace_text{"... "};
  if (text.empty())
    return text;

  if (max_length < replace_text.length())
    return "";

  std::string new_string{text};
  if (text.length() >= max_length) {
    new_string.replace(max_length - replace_text.length(), std::string::npos,
                       replace_text);
  }
  return new_string;
}

void DumpBookCollection(const std::vector<Book> collection) {
  constexpr size_t kLengthId{5};
  constexpr size_t kLengthAuthor{25};
  constexpr size_t kLengthTitle{40};
  constexpr size_t kLengthPages{7};
  constexpr size_t kLengthShelf{15};
  constexpr size_t kLengthReading{5};

  // output table header
  fmt::print(fmt::emphasis::bold, "{:<{}}", "ID", kLengthId);
  fmt::print(fmt::emphasis::bold, "{:<{}}", "AUTHOR", kLengthAuthor);
  fmt::print(fmt::emphasis::bold, "{:<{}}", "TITLE", kLengthTitle);
  fmt::print(fmt::emphasis::bold, "{:<{}}", "PAGES", kLengthPages);
  fmt::print(fmt::emphasis::bold, "{:<{}}", "SHELF", kLengthShelf);
  fmt::print(fmt::emphasis::bold, "{:<{}}", "DAYS", kLengthReading);
  std::cout << '\n';

  // output library content
  for (const auto& book : collection) {
    fmt::print("{:<{}}", book.GetId(), kLengthId);

    // shorten author
    auto current_author = book.GetAuthor();
    fmt::print("{:<{}}",
               AbbreviateTextIfNecessary(current_author, kLengthAuthor),
               kLengthAuthor);

    // shorten the title
    auto current_title = book.GetTitle();
    fmt::print("{:<{}}", AbbreviateTextIfNecessary(current_title, kLengthTitle),
               kLengthTitle);

    fmt::print("{:<{}}", book.GetPages(), kLengthPages);

    // shorten the name of the shelf
    auto current_shelf = book.GetShelf();
    fmt::print("{:<{}}", AbbreviateTextIfNecessary(current_shelf, kLengthShelf),
               kLengthShelf);

    fmt::print("{:<{}}", book.GetReadingTimeDays(), kLengthReading);
    std::cout << '\n';
  }

  // output footer
  std::cout << std::endl;
  std::cout << "Number of books: " << collection.size() << std::endl
            << std::endl;
}

std::string ToLowerCase(const std::string& source) {
  std::string result;
  std::transform(source.begin(), source.end(), std::back_inserter(result),
                 tolower);
  return result;
}
}  // namespace booktrack_cli
