#ifndef BOOKTRACK_CLI_UTILITIES_H
#define BOOKTRACK_CLI_UTILITIES_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "book.h"

namespace booktrack_cli {

/**
 * @brief Splits a given date string into its components
 *
 * @param[in]	date_string	A string of form "dd*mm*yyyy"
 * @param[in]	delimiter 	A delimiter marked with "*" above
 * @return	A vector of size 3 with "day", "month", "year", the result is of
 *		size 0 when there was a parsing error
 */
std::vector<int> SplitDateComponents(const std::string& date_string,
                                     const char delimiter);

/**
 * @brief Dumps a collection of books to std::cout
 *
 * @param[in]   collection      A set of Books
 */
void DumpBookCollection(const std::vector<Book> collection);

/**
 * @brief Returns a lowercase copy of \p source
 *
 * @param[in] source  string to be transformed
 * @return    std::string lower case copy of \p source
 */
std::string ToLowerCase(const std::string& source);

/**
 * @brief Shortens a given text to \p max_length and adds ellipses
 *
 * @param[in] text  string to be shortend
 * @param[in] max_length the length of the return value
 * @return modified text
 */
std::string AbbreviateTextIfNecessary(const std::string& text,
                                      const size_t max_length);
}  // namespace booktrack_cli
#endif
