#include <gtest/gtest.h>

#include "../src/library.h"
#include "../src/statistics.h"

using namespace booktrack_cli;

TEST(StatisticsTest, EmptyLibrary) {
  // arrange
  Library library("");
  Statistics stats(library);

  // act
  const auto result = stats.GetStatistics();

  // assert
  EXPECT_EQ(result.number_of_books, 0);
  EXPECT_EQ(result.reading_days_per_book, 0);
  EXPECT_EQ(result.authors, 0);
  EXPECT_EQ(result.shelfs, 0);
}

TEST(StatisticsTest, LibraryWithEmptyBooks) {
  // arrange
  Library library("");
  Book book_1;
  library.AddBook(book_1);
  Book book_2;
  library.AddBook(book_2);
  Statistics stats(library);

  // act
  const auto result = stats.GetStatistics();

  // assert
  EXPECT_EQ(result.number_of_books, 2);
  EXPECT_EQ(result.reading_days_per_book, 0);
  EXPECT_EQ(result.authors, 0);
  EXPECT_EQ(result.shelfs, 0);
}

TEST(StatisticsTest, LibraryWithSamples) {
  // arrange
  Library library("");
  Book book_1("title", "author", 0, "duplicate");
  book_1.SetReadingStart(1, 1, 2023);
  book_1.SetReadingEnd(12, 1, 2023);
  library.AddBook(book_1);

  Book book_2("title", "author", 0, "duplicate");
  library.AddBook(book_2);

  Book book_3("title", "author", 0, "unique");
  library.AddBook(book_3);

  Statistics stats(library);

  // act
  const auto result = stats.GetStatistics();

  // assert
  EXPECT_EQ(result.number_of_books, 3);
  EXPECT_EQ(result.reading_days_per_book, 4);
  EXPECT_EQ(result.authors, 1);
  EXPECT_EQ(result.shelfs, 2);
}
