#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "../src/book.h"

using namespace booktrack_cli;
using json = nlohmann::json;

TEST(BookConstructorTest, CreateBook) {
  // arrange
  Book book;

  // act
  // assert
  EXPECT_EQ(book.GetAuthor(), "");
  EXPECT_EQ(book.GetTitle(), "");
  EXPECT_EQ(book.GetPages(), 0);
  EXPECT_EQ(book.GetReadingTimeDays(), 0);
  EXPECT_EQ(book.GetShelf(), "");
}

TEST(BookConstructorTest, CreateBookWithTitle) {
  // arrange
  const auto book_title{"title"};
  Book book(book_title);

  // act
  auto result_title = book.GetTitle();

  // assert
  EXPECT_EQ(result_title, book_title);
}

TEST(BookConstructorTest, CreateBookWithTitleAndAuthor) {
  // arrange
  const auto book_title{"title"};
  const auto book_author{"author"};
  Book book(book_title, book_author);

  // act
  auto result_title = book.GetTitle();
  auto result_author = book.GetAuthor();

  // assert
  EXPECT_EQ(result_title, book_title);
  EXPECT_EQ(result_author, book_author);
}

TEST(BookConstructorTest, CreateBookWithTitleAndAuthorAndPages) {
  // arrange
  const auto book_title{"title"};
  const auto book_author{"author"};
  const auto book_pages{256};
  Book book(book_title, book_author, book_pages);

  // act
  auto result_title = book.GetTitle();
  auto result_author = book.GetAuthor();
  auto result_pages = book.GetPages();

  // assert
  EXPECT_EQ(result_title, book_title);
  EXPECT_EQ(result_author, book_author);
  EXPECT_EQ(result_pages, book_pages);
}

TEST(BookConstructorTest, CreateBookWithTitleAndAuthorAndPagesAndShelf) {
  // arrange
  const auto book_title{"title"};
  const auto book_author{"author"};
  const auto book_pages{256};
  const auto book_shelf{"shelf"};
  Book book(book_title, book_author, book_pages, book_shelf);

  // act
  auto result_title = book.GetTitle();
  auto result_author = book.GetAuthor();
  auto result_pages = book.GetPages();
  auto result_shelf = book.GetShelf();

  // assert
  EXPECT_EQ(result_title, book_title);
  EXPECT_EQ(result_author, book_author);
  EXPECT_EQ(result_pages, book_pages);
  EXPECT_EQ(result_shelf, book_shelf);
}
