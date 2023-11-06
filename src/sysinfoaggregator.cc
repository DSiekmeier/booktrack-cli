#include <exception>
#include <fstream>

#include "sysinfoaggregator.h"
using namespace booktrack_cli;

SysInfo SysInfoAggregator::GetSysInfo() {
  SysInfo value;
  std::ifstream input_file{release_file_};

  if (input_file.good()) {
    std::string line;
    while (getline(input_file, line)) {
      const auto splitted = split_entries(line);
      if (splitted[0] == "NAME") {
        value.os_release_name = splitted[1];
      }
      if (splitted[0] == "VERSION") {
        value.os_release_version = splitted[1];
      }
    }
    input_file.close();
  } else {
    throw std::runtime_error("Could not open file.");
  }

  return value;
}

std::vector<std::string> SysInfoAggregator::split_entries(
    const std::string& str) {
  std::vector<std::string> result;
  std::string::size_type start{0};
  std::string::size_type position;
  do {
    position = str.find_first_of("=", start);
    result.push_back(str.substr(start, position - start));
    start = position + 1;
  } while (position != std::string::npos);

  return result;
}
