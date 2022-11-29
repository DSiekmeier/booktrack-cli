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

TEST(ToLowerCaseTest, InputEmpty) {
  // arrange
  std::string test_string{""};

  // act
  auto result = ToLowerCase(test_string);

  // assert
  EXPECT_EQ(result, "");
}

TEST(ToLowerCaseTest, InputAlreadyLowercase) {
  // arrange
  std::string test_string{"this is a lowercase string"};

  // act
  auto result = ToLowerCase(test_string);

  // assert
  EXPECT_EQ(result, "this is a lowercase string");
}

TEST(ToLowerCaseTest, InputAllUppercase) {
  // arrange
  std::string test_string{"THIS IS AN UPPERCASE STRING"};

  // act
  auto result = ToLowerCase(test_string);

  // assert
  EXPECT_EQ(result, "this is an uppercase string");
}

TEST(ToLowerCaseTest, InputNumericalString) {
  // arrange
  std::string test_string{"1234"};

  // act
  auto result = ToLowerCase(test_string);

  // assert
  EXPECT_EQ(result, "1234");
}

TEST(ToLowerCaseTest, InputMixed) {
  // arrange
  std::string test_string{"ThisIsA_1234_Mixed_string."};

  // act
  auto result = ToLowerCase(test_string);

  // assert
  EXPECT_EQ(result, "thisisa_1234_mixed_string.");
}

TEST(AbbreviateTextIfNecessaryTest, TextShortEnough) {
  // arrange
  std::string input{"This is a short text"};
  const size_t kMaxLength{30};

  // act
  const auto result = AbbreviateTextIfNecessary(input, kMaxLength);

  // assert
  EXPECT_EQ(result, input);
  EXPECT_EQ(result.length(), input.length());
}

TEST(AbbreviateTextIfNecessaryTest, TextTooLong) {
  // arrange
  std::string input{"This text is longer than the one in the test above!"};
  const size_t kMaxLength{30};

  // act
  const auto result = AbbreviateTextIfNecessary(input, kMaxLength);

  // assert
  EXPECT_EQ(result.length(), kMaxLength);
  EXPECT_EQ(result, "This text is longer than t... ");
}

TEST(AbbreviateTextIfNecessaryTest, TextIsEmpty) {
  // arrange
  std::string input{""};

  // act
  const auto result = AbbreviateTextIfNecessary(input, 10);

  // assert
  EXPECT_EQ(result.length(), 0);
}

TEST(AbbreviateTextIfNecessaryTest, MaxLengthIsZero) {
  // arrange
  std::string input{"foobarbaz"};

  // act
  const auto result = AbbreviateTextIfNecessary(input, 0);

  // assert
  EXPECT_EQ(result.length(), 0);
}
