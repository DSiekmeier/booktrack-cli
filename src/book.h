#ifndef BOOKTRACK_CLI_BOOK_H
#define BOOKTRACK_CLI_BOOK_H

#include <ctime>
#include <string>
#include <vector>

namespace booktrack_cli {

/**
 * @brief Structure used to store start and end of book reading
 */
struct reading_time {
  time_t date_start;
  time_t date_end;
};

/**
 * @brief Represents a single book in a library
 * @details The Book class contains every information about a single book.
 * Several Book instances built up one Library.
 */
class Book {
 public:
  Book() = default;
  explicit Book(const std::string& main_title,
                const std::string& author = "",
                unsigned int pages = 0,
                const std::string& shelf = "");

  /**
   * @brief Serializes the current book into a JSON string
   */
  std::string ToJsonString() const;

  /**
   * @brief Get the title of the current book
   */
  inline auto GetTitle() const { return title_; };

  /**
   * @brief Get the author of the current book
   */
  inline auto GetAuthor() const { return author_; }

  /**
   * @brief Get the reading time of the current book in days
   */
  inline auto GetReadingTimeDays() const { return reading_time_days_; }

  /**
   * @brief Get the number of pages of the current book
   */
  inline auto GetPages() const { return pages_; }

  /**
   * @brief Get the shelf to which the current book belongs to
   */
  inline auto GetShelf() const { return shelf_; }

  /**
   * @brief Get the library wide unique id of the book
   */
  inline auto GetId() const { return id_; }

  /**
   * @brief Set the start of a reading of a book
   *
   * \return true on success
   */
  bool SetReadingStart(const int day, const int month, const int year);

  /**
   * @brief Set the end of a reading of a book
   *
   * \return true on success
   */
  bool SetReadingEnd(const int day, const int month, const int year);

  /**
   * @brief Sets all information of a Book instance from a JSON object
   */
  void SetDataFromJson(const nlohmann::json& book_json);

  /**
   * @brief Sets the id of the book
   */
  void SetId(const size_t id);

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
  size_t id_{};

  // internal helper methods
  void UpdateReadingTimeDays_();
};

}  // namespace booktrack_cli

#endif
