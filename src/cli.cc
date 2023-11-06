#include "cli.h"
#include "sysinfoaggregator.h"

using namespace booktrack_cli;

namespace {

void AddMainOptions(CLI::App& app, CliOptions& opt) {
  // modify version flag and output system information if available
  app.set_version_flag("--version", []() {
    SysInfo system_information{"<invalid value>", "<invalid value>"};
    try {
      SysInfoAggregator sysinfo("/etc/os-release");
      system_information = sysinfo.GetSysInfo();
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what() << '\n';
    }

    std::stringstream version_string;
    version_string << BOOKTRACK_CLI_VERSION_MAJOR << "."
                   << BOOKTRACK_CLI_VERSION_MINOR << "."
                   << BOOKTRACK_CLI_VERSION_PATCH;

    const auto booktrack_version =
        "booktrack-cli v" + version_string.str() + '\n';
    const auto os_release_name =
        "OS name   : " + system_information.os_release_name + '\n';
    const auto os_release_version =
        "OS version: " + system_information.os_release_version + '\n';

    return booktrack_version + '\n' + os_release_name + os_release_version;
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
  auto shelf = sub_list->add_option("-s,--shelf", opt.list.filter_shelf, "");

  // constraints
  author->excludes(title)->excludes(shelf);
  title->excludes(author)->excludes(shelf);
  shelf->excludes(author)->excludes(title);
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

void AddStatisticsOptions(CLI::App& app, CliOptions& opt) {
  app.add_subcommand("statistics", "Show statistics for loaded library")
      ->callback([&opt]() { opt.command = PrimaryCommand::kStatistics; });
}

void AddDetailsOptions(CLI::App& app, CliOptions& opt) {
  auto sub_details =
      app.add_subcommand("details", "Show details for a book")
          ->callback([&opt]() { opt.command = PrimaryCommand::kDetails; });

  sub_details->add_option("--by-id", opt.details.id, "")->mandatory();
}

}  // namespace

void booktrack_cli::AddCliOptions(CLI::App& app, CliOptions& opt) {
  AddMainOptions(app, opt);
  AddAddOptions(app, opt);
  AddDeleteOptions(app, opt);
  AddListOptions(app, opt);
  AddStatisticsOptions(app, opt);
  AddDetailsOptions(app, opt);
}
