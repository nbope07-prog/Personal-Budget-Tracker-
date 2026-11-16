/*
Name: Naveen
Description: Defines the different transaction categories.
*/
#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
enum class Category { Food, Transportation, Housing, Utilities, Entertainment, Health, Other };
std::string categoryToString(Category category);
Category categoryFromNumber(int number);
#endif
