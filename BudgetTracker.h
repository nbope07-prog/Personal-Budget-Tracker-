/*
Name: Naveen
Description: Defines the BudgetTracker class and its functions.
*/
#ifndef BUDGET_TRACKER_H
#define BUDGET_TRACKER_H
#include "TransactionList.h"
#include "Category.h"
#include <string>
class BudgetTracker {
private:
    double balance;
    double totalIncome;
    double totalExpenses;
    TransactionList<Transaction> transactions;
    void updateTotals();
public:
    BudgetTracker();
    void addTransaction(const std::string& desc, double amt, Category cat,
                        const std::string& type, const std::string& date = "");
    void searchByCategory(Category cat) const;
    void sortByAmount();
    void viewBalance() const;
    void viewCategorySpending() const;
    void viewTransactions() const;
    void run();
};
#endif
