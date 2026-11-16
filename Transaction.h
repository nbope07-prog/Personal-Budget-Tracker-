/*
Name: Naveen
Description: Defines the Transaction class and its functions and represents one income or expense.
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include "Category.h"
class Transaction {
private:
    std::string description;
    double amount;
    Category category;
    std::string type;
    std::string date;
public:
    Transaction();
    Transaction(const std::string& desc, double amt, Category cat,
                const std::string& transactionType, const std::string& transactionDate = "");
    std::string getDescription() const;
    double getAmount() const;
    Category getCategory() const;
    std::string getType() const;
    std::string getDate() const;
    void setDescription(const std::string& desc);
    void setAmount(double amt);
    void setCategory(Category cat);
    void setType(const std::string& transactionType);
    void setDate(const std::string& transactionDate);
    // REQUIRED CONCEPT: three overloaded operators.
    bool operator==(const Transaction& other) const;
    bool operator<(const Transaction& other) const;
    bool operator>(const Transaction& other) const;
};
#endif
