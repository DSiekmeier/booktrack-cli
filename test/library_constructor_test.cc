#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "../src/library.h"

using namespace booktrack_cli;
using json = nlohmann::json;

TEST(BookConstructorTest, CreateLibraryUnexistingFile) {
  // arrange
  Library library("");

  // act

  // assert
  EXPECT_TRUE(false);
}
