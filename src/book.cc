#include <ctime>
#include <string>

#include <nlohmann/json.hpp>

#include "book.h"
using namespace booktrack_cli;

Book::Book(const std::string& main_title,
           const std::string& author,
           unsigned int pages,
           const std::string& shelf)
    : title_(main_title), author_(author), pages_(pages), shelf_(shelf) {}

std::string Book::ToJsonString() const {
  nlohmann::json book_json;

  // meta information
  book_json["shelf"] = shelf_;
  book_json["id"] = id_;

  // reading information
  auto start_ticks = reading_.date_start;
  book_json["reading"]["start"] = start_ticks;

  auto end_ticks = reading_.date_end;
  book_json["reading"]["end"] = end_ticks;

  // book information
  book_json["bookinfo"]["title"] = title_;
  book_json["bookinfo"]["author"] = author_;
  book_json["bookinfo"]["pages"] = pages_;

  return book_json.dump();
}

void Book::SetDataFromJson(const nlohmann::json& book_json) {
  title_ = book_json["bookinfo"]["title"];
  author_ = book_json["bookinfo"]["author"];
  pages_ = book_json["bookinfo"]["pages"];

  reading_.date_start = book_json["reading"]["start"];
  reading_.date_end = book_json["reading"]["end"];
  UpdateReadingTimeDays_();

  shelf_ = book_json["shelf"];
  id_ = book_json["id"];
}

bool Book::SetReadingStart(const int day, const int month, const int year) {
  struct std::tm start_date {};
  start_date.tm_mday = day;
  start_date.tm_mon = month - 1;
  start_date.tm_year = year - 1900;

  auto start_ticks = std::mktime(&start_date);
  reading_.date_start = start_ticks;
  UpdateReadingTimeDays_();

  return true;
}

bool Book::SetReadingEnd(const int day, const int month, const int year) {
  struct std::tm end_date {};
  end_date.tm_mday = day;
  end_date.tm_mon = month - 1;
  end_date.tm_year = year - 1900;

  auto end_ticks = std::mktime(&end_date);
  reading_.date_end = end_ticks;
  UpdateReadingTimeDays_();

  return true;
}

void Book::UpdateReadingTimeDays_() {
  if (reading_.date_end > 0 && reading_.date_start > 0) {
    auto diff = reading_.date_end - reading_.date_start;
    auto diff_hours = diff / 60 / 60;
    reading_time_days_ = diff_hours / 24 + 1;  // +1 to include end day
  }
}

void Book::SetId(const size_t id) {
  id_ = id;
}
