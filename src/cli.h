#ifndef BOOKTRACK_CLI_CLI_H
#define BOOKTRACK_CLI_CLI_H

#include <string>

namespace booktrack_cli {

/**
 * @brief Contains available options for the "add" subcommand
 */
struct CliOptionsAdd {
  std::string author;
  std::string title;
  unsigned int pages;
  std::string shelf;
  std::string reading_start;
  std::string reading_end;
};

/**
 * @brief Contains available options for the "delete" subcommand
 */
struct CliOptionsDel {
  std::string title;
};

/**
 * @brief Structure containing all options for the command line interface
 */
struct CliOptions {
  std::string library_file_path;
  CliOptionsAdd add;
  CliOptionsDel del;
};

}  // namespace booktrack_cli

#endif
