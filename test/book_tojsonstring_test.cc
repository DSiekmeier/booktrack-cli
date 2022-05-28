#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "../src/book.h"

using namespace booktrack_cli;
using json = nlohmann::json;

TEST(BookToJsonStringTest, GetJsonDefault) {
  // arrange
  const std::string expected{
      "{\"bookinfo\":{\"author\":\"\",\"pages\":0,\"title\":\"title\"},"
      "\"reading\":{\"end\":0,\"start\":0},\"shelf\":\"\"}"};
  Book book("title");

  // act
  auto json_string = book.ToJsonString();

  // assert
  EXPECT_EQ(json_string, expected);
}

TEST(BookToJsonStringTest, GetJsonWithAuthor) {
  // arrange
  const std::string expected{
      "{\"bookinfo\":{\"author\":\"Jon "
      "Doe\",\"pages\":0,\"title\":\"title\"},\"reading\":{\"end\":0,\"start\":"
      "0},\"shelf\":\"\"}"};
  Book book("title", "Jon Doe");

  // act
  auto json_string = book.ToJsonString();

  // assert
  EXPECT_EQ(json_string, expected);
}

TEST(BookToJsonStringTest, JsonContainsAllKeysMeta) {
  // arrange
  Book book("Title");

  // act
  const auto json_string = book.ToJsonString();
  const json parsed_json = json::parse(json_string);

  // assert
  EXPECT_TRUE(parsed_json.contains("shelf"));
}

TEST(BookToJsonStringTest, JsonContainsAllKeysBookinfo) {
  // arrange
  Book book("Title");

  // act
  const auto json_string = book.ToJsonString();
  const json parsed_json = json::parse(json_string);

  // assert
  ASSERT_TRUE(parsed_json.contains("bookinfo"));
  EXPECT_TRUE(parsed_json["bookinfo"].contains("title"));
  EXPECT_TRUE(parsed_json["bookinfo"].contains("author"));
  EXPECT_TRUE(parsed_json["bookinfo"].contains("pages"));
}

TEST(BookToJsonStringTest, JsonContainsAllKeysReading) {
  // arrange
  Book book("Title");

  // act
  const auto json_string = book.ToJsonString();
  const json parsed_json = json::parse(json_string);

  // assert
  ASSERT_TRUE(parsed_json.contains("reading"));
  EXPECT_TRUE(parsed_json["reading"].contains("start"));
  EXPECT_TRUE(parsed_json["reading"].contains("end"));
}
