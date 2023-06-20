#include <fmt/color.h>
#include <fmt/core.h>

#include "details.h"

namespace booktrack_cli {

void DumpBookDetails(const Book& book) {
  constexpr size_t kLengthPretext{20};

  fmt::print("\"{}\"", fmt::styled(book.GetTitle(), fmt::emphasis::bold));
  fmt::print(" written by ");
  fmt::print("\"{}\"\n", fmt::styled(book.GetAuthor(), fmt::emphasis::bold));
  fmt::print("\n");

  fmt::print("{:{}}: ", "Internal Book ID", kLengthPretext);
  fmt::print("{}\n", fmt::styled(book.GetId(), fmt::emphasis::bold));

  fmt::print("{:{}}: ", "Number of Pages", kLengthPretext);
  fmt::print("{}\n", fmt::styled(book.GetPages(), fmt::emphasis::bold));

  fmt::print("{:{}}: ", "Reading time", kLengthPretext);
  fmt::print("{} days\n",
             fmt::styled(book.GetReadingTimeDays(), fmt::emphasis::bold));

  fmt::print("{:{}}: ", "Shelf", kLengthPretext);
  fmt::print("{}\n", fmt::styled(book.GetShelf(), fmt::emphasis::bold));

  fmt::print("\n");
}

}  // namespace booktrack_cli
