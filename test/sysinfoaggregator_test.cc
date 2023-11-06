#include <gtest/gtest.h>
#include <exception>

#include "../src/sysinfoaggregator.h"

using namespace booktrack_cli;

TEST(SysInfoAggregator, ReadFromOsRelease) {
  // arrange
  SysInfoAggregator sysinfo_aggregator("/etc/os-release");

  // act
  const auto sysinfo = sysinfo_aggregator.GetSysInfo();

  // assert
  EXPECT_NE(sysinfo.os_release_name, "");
  EXPECT_NE(sysinfo.os_release_version, "");
}

TEST(SysInfoAggregator, ReadNonExistingFile) {
  // arrange
  SysInfoAggregator sysinfo_aggregator("/not/existing/path");

  // act + assert
  EXPECT_THROW(sysinfo_aggregator.GetSysInfo(), std::runtime_error);
}
