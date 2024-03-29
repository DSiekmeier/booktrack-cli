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
  kStatistics,
  kDetails,
  kEdit,
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
 * @brief Contains available options for the "list" subcommand
 */
struct CliOptionsList {
  std::string filter_author{};
  std::string filter_title{};
  std::string filter_shelf{};
};

/**
 * @brief Contains available options for the "statistics" subcommand
 */
struct CliOptionsStatistics {};

/**
 * @brief Contains available options for the "details" subcommand
 */
struct CliOptionsDetails {
  size_t id{0};
};

/**
 * @brief Contains available options for the "edit" subcommand
 */
struct CliOptionsEdit {
  size_t id{0};
  CliOptionsAdd changeset;
};

/**
 * @brief Structure containing all options for the command line interface
 */
struct CliOptions {
  std::string library_file_path;
  PrimaryCommand command;
  CliOptionsAdd add;
  CliOptionsDel del;
  CliOptionsList list;
  CliOptionsStatistics statistics;
  CliOptionsDetails details;
  CliOptionsEdit edit;
};

/**
 * @brief Add all available commandline options to the app
 */
void AddCliOptions(CLI::App& app, CliOptions& opt);

}  // namespace booktrack_cli

#endif
