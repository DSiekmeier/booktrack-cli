#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../src/utilities.h"

using namespace booktrack_cli;

TEST(SplitDateComponents, DelimiterPoint) {
  // arrange
  std::vector<int> expected{1, 1, 2020};

  // act
  auto result = SplitDateComponents("01.01.2020", '.');

  // assert
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result, expected);
}

TEST(SplitDateComponents, DelimiterSlash) {
  // arrange
  std::vector<int> expected{1, 1, 2020};

  // act
  auto result = SplitDateComponents("01/01/2020", '/');

  // assert
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result, expected);
}

TEST(SplitDateComponents, InvalidInputMissingNumbers) {
  // arrange
  // act
  auto result = SplitDateComponents("dd/mm/yyyy", '/');

  // assert
  EXPECT_EQ(result.size(), 0);
}

TEST(SplitDateComponents, InvalidInputWrongNumberCount1) {
  // arrange
  // act
  auto result = SplitDateComponents("12/3/yyyy", '/');

  // assert
  EXPECT_EQ(result.size(), 0);
}

TEST(SplitDateComponents, InvalidInputWrongNumberCount2) {
  // arrange
  // act
  auto result = SplitDateComponents("dd/3/2022", '/');

  // assert
  EXPECT_EQ(result.size(), 0);
}
