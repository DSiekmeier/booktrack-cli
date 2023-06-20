#ifndef BOOKTRACK_CLI_DETAILS_H
#define BOOKTRACK_CLI_DETAILS_H

#include "book.h"

namespace booktrack_cli {

/**
 * @brief Prints all book information on stdout
 * 
 * @param[in] book	Book to print information about
 */
void DumpBookDetails(const Book& book);

}

#endif
