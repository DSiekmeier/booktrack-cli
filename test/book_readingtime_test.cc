#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "../src/book.h"

using namespace booktrack_cli;
using json = nlohmann::json;

TEST(BookGeneralTest, GetReadingTimeDays) {
  // arrange
  Book book("title");
  book.SetReadingStart(1, 1, 2022);
  book.SetReadingEnd(4, 1, 2022);

  // act
  auto result_days = book.GetReadingTimeDays();

  // assert
  EXPECT_EQ(result_days, 4);
}

TEST(BookGeneralTest, GetReadingTimeDaysDatesNotSet) {
  // arrange
  Book book("title");

  // act
  auto result_days = book.GetReadingTimeDays();

  // assert
  EXPECT_EQ(result_days, 0);
}

TEST(BookGeneralTest, GetReadingTimeDaysStartDateMissing) {
  // arrange
  Book book("title");
  book.SetReadingEnd(4, 1, 2022);

  // act
  auto result_days = book.GetReadingTimeDays();

  // assert
  EXPECT_EQ(result_days, 0);
}

TEST(BookGeneralTest, GetReadingTimeDaysEndDateMissing) {
  // arrange
  Book book("title");
  book.SetReadingStart(4, 1, 2022);

  // act
  auto result_days = book.GetReadingTimeDays();

  // assert
  EXPECT_EQ(result_days, 0);
}

TEST(BookGeneralTest, GetReadingEnd) {
  // arrange
  Book book("title");
  book.SetReadingEnd(31, 12, 2022);

  // act
  auto reading_end = book.GetReadingEnd();
  struct tm buf;
  localtime_r(&reading_end, &buf);
  auto result = buf.tm_year + 1900;

  // assert
  EXPECT_EQ(result, 2022);
}
