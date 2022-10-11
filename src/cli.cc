#include "cli.h"

using namespace booktrack_cli;

namespace {

void AddMainOptions(CLI::App& app, CliOptions& opt) {
  app.set_version_flag("--version", []() {
    std::stringstream version_string;
    version_string << BOOKTRACK_CLI_VERSION_MAJOR << "."
                   << BOOKTRACK_CLI_VERSION_MINOR << "."
                   << BOOKTRACK_CLI_VERSION_PATCH;
    return "booktrack-cli v" + version_string.str();
  });

  app.add_option("-l,--library,", opt.library_file_path,
                 "Set the path of the library")
      ->mandatory();

  app.require_subcommand();
}

void AddListOptions(CLI::App& app, CliOptions& opt) {
  auto sub_list =
      app.add_subcommand("list", "List books in the library")
          ->callback([&opt]() { opt.command = PrimaryCommand::kList; });

  auto author = sub_list->add_option("-a,--author", opt.list.filter_author, "");
  auto title = sub_list->add_option("-t,--title", opt.list.filter_title, "");

  // constraints
  author->excludes(title);
}

void AddAddOptions(CLI::App& app, CliOptions& opt) {
  auto sub_add =
      app.add_subcommand("add", "Add a book to the library")
          ->callback([&opt]() { opt.command = PrimaryCommand::kAdd; });

  sub_add->add_option("-t,--title", opt.add.title, "")->mandatory();
  sub_add->add_option("-a,--author", opt.add.author, "");
  sub_add->add_option("-p,--pages", opt.add.pages, "");
  sub_add->add_option("-s,--shelf", opt.add.shelf, "");
  sub_add->add_option("--reading-start", opt.add.reading_start);
  sub_add->add_option("--reading-end", opt.add.reading_end);
}

void AddDeleteOptions(CLI::App& app, CliOptions& opt) {
  auto sub_delete =
      app.add_subcommand("delete", "Delete a book from the library")
          ->callback([&opt]() { opt.command = PrimaryCommand::kDelete; });

  auto id = sub_delete->add_option("--by-id", opt.del.id, "");
  auto title = sub_delete->add_option("--by-title", opt.del.title, "");

  // constraints
  id->excludes(title);
}

}  // namespace

void booktrack_cli::AddCliOptions(CLI::App& app, CliOptions& opt) {
  AddMainOptions(app, opt);
  AddAddOptions(app, opt);
  AddDeleteOptions(app, opt);
  AddListOptions(app, opt);
}
