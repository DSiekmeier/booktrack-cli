#ifndef BOOKTRACK_CLI_CLI_H
#define BOOKTRACK_CLI_CLI_H

#include <string>

namespace booktrack_cli {

// options for "add" subcommand
struct CliOptionsAdd {
  std::string author;
  std::string title;
  unsigned int pages;
  std::string shelf;
  std::string reading_start;
  std::string reading_end;
};

// options for "delete" subcommand
struct CliOptionsDel {
  std::string title;
};

struct CliOptions {
  std::string library_file_path;
  CliOptionsAdd add;
  CliOptionsDel del;
};

}  // namespace booktrack_cli

#endif
