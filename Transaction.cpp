/*
Name: Naveen
Description: This implements the Transaction class functions.
*/
#include "Transaction.h"
Transaction::Transaction() : amount(0), category(Category::Other), type("Expense") {}
Transaction::Transaction(const std::string& desc, double amt, Category cat,
                         const std::string& transactionType, const std::string& transactionDate)
    : description(desc), amount(amt), category(cat), type(transactionType), date(transactionDate) {}
std::string Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }
Category Transaction::getCategory() const { return category; }
std::string Transaction::getType() const { return type; }
std::string Transaction::getDate() const { return date; }
void Transaction::setDescription(const std::string& desc) { description = desc; }
void Transaction::setAmount(double amt) { amount = amt; }
void Transaction::setCategory(Category cat) { category = cat; }
void Transaction::setType(const std::string& transactionType) { type = transactionType; }
void Transaction::setDate(const std::string& transactionDate) { date = transactionDate; }
bool Transaction::operator==(const Transaction& other) const { return amount == other.amount; }
bool Transaction::operator<(const Transaction& other) const { return amount < other.amount; }
bool Transaction::operator>(const Transaction& other) const { return amount > other.amount; }
