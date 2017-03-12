#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <iostream>
#include <string>
#include "sqlite3.h"

std::string getCategories();
std::string getItemsOfCategory(int sno);

#endif
