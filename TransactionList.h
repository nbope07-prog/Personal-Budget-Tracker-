/*
Name: Naveen
Description:  Defines the linked list and its functions.
*/
#ifndef TRANSACTION_LIST_H
#define TRANSACTION_LIST_H
#include "Transaction.h"
#include <cstddef>
// REQUIRED CONCEPT: class template, instantiated with Transaction in BudgetTracker.
template <typename T>
class TransactionList {
private:
    // REQUIRED CONCEPT: singly linked list implemented from scratch.
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& item) : data(item), next(nullptr) {}
    };
    Node* head;
    int size;
    // REQUIRED CONCEPT: recursive category search with aggregate results.
    struct SearchSummary {
        int count;
        double expenses;
        double income;
    };
    SearchSummary recursiveSearch(Category category, const Node* node) const;
    static Node* split(Node* first);
    static Node* merge(Node* left, Node* right);
    static Node* mergeSort(Node* first);
public:
    TransactionList();
    ~TransactionList();
    TransactionList(const TransactionList&) = delete;
    TransactionList& operator=(const TransactionList&) = delete;
    void addTransaction(const T& transaction);
    bool removeTransaction(const T& transaction);
    void displayTransactions() const;
    void searchByCategory(Category category) const;
    void sortByAmount();
    double calculateTotal() const;
    double calculateIncome() const;
    double calculateExpenses() const;
    double categorySpending(Category category) const;
    int getSize() const;
};
#endif
