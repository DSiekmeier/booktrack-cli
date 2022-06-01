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
}  // namespace booktrack_cli
