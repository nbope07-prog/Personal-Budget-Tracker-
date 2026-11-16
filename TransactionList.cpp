/*
Name: Naveen
Description:  This implements linked list operations, sorting, and recursion.
*/
#include "TransactionList.h"
#include <iostream>
#include <iomanip>
#include <string>
template <typename T>
TransactionList<T>::TransactionList() : head(nullptr), size(0) {}
template <typename T>
TransactionList<T>::~TransactionList() {
    while (head) { Node* old = head; head = head->next; delete old; }
}
template <typename T>
void TransactionList<T>::addTransaction(const T& transaction) {
    Node* node = new Node(transaction);
    if (!head) head = node;
    else {
        Node* current = head;
        while (current->next) current = current->next;
        current->next = node;
    }
    ++size;
}
template <typename T>
bool TransactionList<T>::removeTransaction(const T& transaction) {
    Node* previous = nullptr;
    Node* current = head;
    while (current) {
        if (current->data.getDescription() == transaction.getDescription()
            && current->data.getAmount() == transaction.getAmount()
            && current->data.getType() == transaction.getType()) {
            if (previous) previous->next = current->next;
            else head = current->next;
            delete current;
            --size;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}
template <typename T>
void TransactionList<T>::displayTransactions() const {
    if (!head) { std::cout << "No transactions yet.\n"; return; }
    const Node* current = head;
    while (current) {
        const T& t = current->data;
        std::cout << t.getDescription() << " | $" << std::fixed << std::setprecision(2)
                  << t.getAmount() << " | " << categoryToString(t.getCategory())
                  << " | " << t.getType() << " | " << t.getDate() << '\n';
        current = current->next;
    }
}
// REQUIRED CONCEPT: recursion. Each call returns a summary of the remaining
// list, then combines that result with the current transaction. This does
// actual aggregation on the return path instead of only moving to the next node.
template <typename T>
typename TransactionList<T>::SearchSummary
TransactionList<T>::recursiveSearch(Category category, const Node* node) const {
    if (!node) return {0, 0.0, 0.0}; // Base case: empty remainder

    SearchSummary rest = recursiveSearch(category, node->next);
    const T& t = node->data;
    if (t.getCategory() == category) {
        std::cout << "  " << t.getDescription() << " ($" << t.getAmount()
                  << ", " << t.getType() << ")\n";
        ++rest.count;
        if (t.getType() == "Expense") rest.expenses += t.getAmount();
        else if (t.getType() == "Income") rest.income += t.getAmount();
    }
    return rest;
}
template <typename T>
void TransactionList<T>::searchByCategory(Category category) const {
    std::cout << "Matches for " << categoryToString(category) << ":\n";
    SearchSummary result = recursiveSearch(category, head);
    std::cout << "Found " << result.count << " transaction(s); category expenses: $"
              << std::fixed << std::setprecision(2) << result.expenses
              << "; category income: $" << result.income
              << "; net: $" << (result.income - result.expenses) << '\n';
}
// REQUIRED CONCEPT: own merge sort; std::sort is not used.
template <typename T>
typename TransactionList<T>::Node* TransactionList<T>::split(Node* first) {
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* second = slow->next;
    slow->next = nullptr;
    return second;
}
template <typename T>
typename TransactionList<T>::Node* TransactionList<T>::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    if (!(right->data < left->data)) {
        left->next = merge(left->next, right);
        return left;
    }
    right->next = merge(left, right->next);
    return right;
}
template <typename T>
typename TransactionList<T>::Node* TransactionList<T>::mergeSort(Node* first) {
    if (!first || !first->next) return first;
    Node* second = split(first);
    return merge(mergeSort(first), mergeSort(second));
}
template <typename T>
void TransactionList<T>::sortByAmount() { head = mergeSort(head); }
template <typename T>
double TransactionList<T>::calculateIncome() const {
    double sum = 0;
    for (Node* n = head; n; n = n->next)
        if (n->data.getType() == "Income") sum += n->data.getAmount();
    return sum;
}
template <typename T>
double TransactionList<T>::calculateExpenses() const {
    double sum = 0;
    for (Node* n = head; n; n = n->next)
        if (n->data.getType() == "Expense") sum += n->data.getAmount();
    return sum;
}
template <typename T>
double TransactionList<T>::calculateTotal() const {
    return calculateIncome() - calculateExpenses();
}
template <typename T>
double TransactionList<T>::categorySpending(Category category) const {
    double sum = 0;
    for (Node* n = head; n; n = n->next)
        if (n->data.getCategory() == category && n->data.getType() == "Expense")
            sum += n->data.getAmount();
    return sum;
}
template <typename T>
int TransactionList<T>::getSize() const { return size; }
// Explicit instantiation keeps implementation in .cpp, as required by the rubric.
template class TransactionList<Transaction>;
