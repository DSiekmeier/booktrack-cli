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
