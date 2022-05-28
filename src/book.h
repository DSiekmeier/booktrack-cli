#ifndef BOOKTRACK_CLI_BOOK_H
#define BOOKTRACK_CLI_BOOK_H

#include <ctime>
#include <string>
#include <vector>

namespace booktrack_cli {

// represents the start and end of reading a book
struct reading_time {
  time_t date_start;
  time_t date_end;
};

class Book {
 public:
  Book() = default;
  explicit Book(const std::string& main_title,
                const std::string& author = "",
                unsigned int pages = 0,
                const std::string& shelf = "");

  std::string ToJsonString() const;

  // Getters
  inline auto GetTitle() const { return title_; };
  inline auto GetAuthor() const { return author_; }
  inline auto GetReadingTimeDays() const { return reading_time_days_; }
  inline auto GetPages() const { return pages_; }
  inline auto GetShelf() const { return shelf_; }

  // Setters
  bool SetReadingStart(const int day, const int month, const int year);
  bool SetReadingEnd(const int day, const int month, const int year);
  void SetDataFromJson(const nlohmann::json& book_json);

 private:
  // book info
  std::string author_{};
  std::string title_{};
  unsigned int pages_{};

  // reading information
  reading_time reading_{};
  size_t reading_time_days_{};

  // meta information
  std::string shelf_{};

  // internal helper methods
  void UpdateReadingTimeDays_();
};

}  // namespace booktrack_cli

#endif
