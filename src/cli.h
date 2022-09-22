#ifndef BOOKTRACK_CLI_CLI_H
#define BOOKTRACK_CLI_CLI_H

#include <version.h>
#include <CLI/CLI11.hpp>
#include <string>

namespace booktrack_cli {

/**
 * @brief Identifies the primary command on calling the app
 */
enum class PrimaryCommand {
  kAdd,
  kList,
  kDelete,
};

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
  size_t id{0};
  std::string title{};
};

/**
 * @brief Structure containing all options for the command line interface
 */
struct CliOptions {
  std::string library_file_path;
  PrimaryCommand command;
  CliOptionsAdd add;
  CliOptionsDel del;
};

/**
 * @brief Add all available commandline options to the app
 */
void AddCliOptions(CLI::App& app, CliOptions& opt);

}  // namespace booktrack_cli

#endif
