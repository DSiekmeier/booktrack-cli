#ifndef BOOKTRACK_CLI_SYSINFOAGGREGATOR_H
#define BOOKTRACK_CLI_SYSINFOAGGREGATOR_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace booktrack_cli {

struct SysInfo {
  std::string os_release_name;
  std::string os_release_version;
};

class SysInfoAggregator {
 public:
  explicit SysInfoAggregator(const fs::path& release_file)
      : release_file_{release_file} {};

  /**
   * @brief Read system info from /etc/os-release
   *
   * @return SysInfo  filled SysInfo struct
   * @throws std::runtime_error
   */
  [[nodiscard]] SysInfo GetSysInfo();

 private:
  std::vector<std::string> split_entries(const std::string& str);

  fs::path release_file_;
};
}  // namespace booktrack_cli

#endif
