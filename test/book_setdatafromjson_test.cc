#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "../src/book.h"

using namespace booktrack_cli;
using json = nlohmann::json;

TEST(BookSetDataFromJsonTest, SetAllData) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"author\":\"Max "
      "Mustermann\",\"pages\":123,\"title\":\"title\"},\"id\":"
      "0,\"reading\":{\"end\":0,\"start\":0},\"shelf\":\"bookshelf\"}"_json;

  // act
  new_book.SetDataFromJson(data);

  // assert
  EXPECT_EQ(new_book.GetAuthor(), "Max Mustermann");
  EXPECT_EQ(new_book.GetTitle(), "title");
  EXPECT_EQ(new_book.GetPages(), 123);
  EXPECT_EQ(new_book.GetShelf(), "bookshelf");
}

TEST(BookSetDataFromJsonTest, MissingAuthor) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"pages\":123,\"title\":\"title\"},\"id\":"
      "0,\"reading\":{\"end\":0,\"start\":0},\"shelf\":\"bookshelf\"}"_json;

  // act + assert
  EXPECT_THROW(new_book.SetDataFromJson(data), nlohmann::json::out_of_range);
}

TEST(BookSetDataFromJsonTest, MissingTitle) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"author\":\"Max Mustermann\",\"pages\":123},\"id\":"
      "0,\"reading\":{\"end\":0,\"start\":0},\"shelf\":\"bookshelf\"}"_json;

  // act + assert
  EXPECT_THROW(new_book.SetDataFromJson(data), nlohmann::json::out_of_range);
}

TEST(BookSetDataFromJsonTest, MissingPages) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"author\":\"Max "
      "Mustermann\",\"title\":\"title\"},\"id\":"
      "0,\"reading\":{\"end\":0,\"start\":0},\"shelf\":\"bookshelf\"}"_json;

  // act + assert
  EXPECT_THROW(new_book.SetDataFromJson(data), nlohmann::json::out_of_range);
}

TEST(BookSetDataFromJsonTest, MissingReading) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"author\":\"Max "
      "Mustermann\",\"pages\":123,\"title\":\"title\"},\"id\":"
      "0,\"shelf\":\"bookshelf\"}"_json;

  // act + assert
  EXPECT_THROW(new_book.SetDataFromJson(data), nlohmann::json::out_of_range);
}

TEST(BookSetDataFromJsonTest, MissingShelf) {
  // arrange
  Book new_book;
  json data =
      "{\"bookinfo\":{\"author\":\"Max "
      "Mustermann\",\"pages\":123,\"title\":\"title\"},\"id\":"
      "0,\"reading\":{\"end\":0,\"start\":0}}"_json;

  // act + assert
  EXPECT_THROW(new_book.SetDataFromJson(data), nlohmann::json::out_of_range);
}
