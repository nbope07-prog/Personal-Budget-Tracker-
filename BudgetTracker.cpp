/*
Name: Naveen
Description: For User menu, input, and budget operations.
*/

#include "BudgetTracker.h"
#include <iostream>
#include <iomanip>
#include <limits>
BudgetTracker::BudgetTracker() : balance(0), totalIncome(0), totalExpenses(0) {}
void BudgetTracker::updateTotals() {
    totalIncome = transactions.calculateIncome();
    totalExpenses = transactions.calculateExpenses();
    balance = transactions.calculateTotal();
}
void BudgetTracker::addTransaction(const std::string& desc, double amt, Category cat,
                                   const std::string& type, const std::string& date) {
    if (amt < 0 || (type != "Income" && type != "Expense")) {
        std::cout << "Invalid transaction.\n";
        return;
    }
    transactions.addTransaction(Transaction(desc, amt, cat, type, date));
    updateTotals();
}
void BudgetTracker::searchByCategory(Category cat) const { transactions.searchByCategory(cat); }
void BudgetTracker::sortByAmount() { transactions.sortByAmount(); }
void BudgetTracker::viewBalance() const {
    std::cout << std::fixed << std::setprecision(2)
              << "Total income: $" << totalIncome << "\nTotal expenses: $"
              << totalExpenses << "\nBalance: $" << balance << '\n';
}
void BudgetTracker::viewCategorySpending() const {
    for (int i = 1; i <= 7; ++i) {
        Category category = categoryFromNumber(i);
        std::cout << categoryToString(category) << ": $"
                  << std::fixed << std::setprecision(2)
                  << transactions.categorySpending(category) << '\n';
    }
}
void BudgetTracker::viewTransactions() const { transactions.displayTransactions(); }
void BudgetTracker::run() {
    int choice = 0;
    while (choice != 6) {
        std::cout << "\nPersonal Budget Tracker\n"
                  << "1. Add transaction\n2. View transactions\n"
                  << "3. Search by category\n4. Sort by amount\n"
                  << "5. View balance\n6. Exit\nChoose: ";
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) return;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number.\n";
            continue;
        }
        if (choice == 1) {
            std::string desc, type, date;
            double amount = 0;
            int catNumber = 7, typeNumber = 2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Description: ";
            std::getline(std::cin, desc);
            std::cout << "Amount: ";
            if (!(std::cin >> amount)) {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid amount.\n";
                continue;
            }
            std::cout << "Category (1 Food, 2 Transportation, 3 Housing, 4 Utilities, "
                         "5 Entertainment, 6 Health, 7 Other): ";
            if (!(std::cin >> catNumber)) {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid category.\n";
                continue;
            }
            std::cout << "Type (1 Income, 2 Expense): ";
            if (!(std::cin >> typeNumber)) {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid type.\n";
                continue;
            }
            if (catNumber < 1 || catNumber > 7 || (typeNumber != 1 && typeNumber != 2)) {
                std::cout << "Invalid category or type.\n";
                continue;
            }
            type = typeNumber == 1 ? "Income" : "Expense";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Date (optional): ";
            std::getline(std::cin, date);
            addTransaction(desc, amount, categoryFromNumber(catNumber), type, date);
        } else if (choice == 2) {
            viewTransactions();
        } else if (choice == 3) {
            int catNumber = 7;
            std::cout << "Category number (1-7): ";
            if (!(std::cin >> catNumber)) {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid category.\n";
                continue;
            }
            if (catNumber >= 1 && catNumber <= 7) searchByCategory(categoryFromNumber(catNumber));
            else std::cout << "Invalid category.\n";
        } else if (choice == 4) {
            sortByAmount();
            std::cout << "Sorted by amount:\n";
            viewTransactions();
        } else if (choice == 5) {
            viewBalance();
            std::cout << "Spending by category:\n";
            viewCategorySpending();
        } else if (choice != 6) {
            std::cout << "Invalid menu choice.\n";
        }
    }
    std::cout << "Goodbye!\n";
}
