/*
Name: Naveen
Description: It converts category numbers and names.
*/
#include "Category.h"
std::string categoryToString(Category category) {
    switch (category) {
        case Category::Food: return "Food";
        case Category::Transportation: return "Transportation";
        case Category::Housing: return "Housing";
        case Category::Utilities: return "Utilities";
        case Category::Entertainment: return "Entertainment";
        case Category::Health: return "Health";
        default: return "Other";
    }
}
Category categoryFromNumber(int number) {
    if (number >= 1 && number <= 7) return static_cast<Category>(number - 1);
    return Category::Other;
}
