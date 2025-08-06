#include "Customer.h"
#include <string>
#include <vector>
#include <iostream>

// Default constructor
Customer::Customer() : id(0), title(""), name(""), type("") {
}

// Full constructor
Customer::Customer(int id, const std::string& title, const std::string& name, const std::string& type, const std::vector<int>& purchaseNumbers)
    : id(id), title(title), name(name), type(type), purchaseNumbers(purchaseNumbers) {
}

// Copy constructor
Customer::Customer(const Customer& other)
    : id(other.id), title(other.title), name(other.name), type(other.type), purchaseNumbers(other.purchaseNumbers) {
}

// Destructor
Customer::~Customer() {
    // No dynamic memory to clean up for this simple class
}

// Assignment operator
Customer& Customer::operator=(const Customer& other) {
    if (this != &other) { // Protect against self-assignment
        id = other.id;
        title = other.title;
        name = other.name;
        type = other.type;
        purchaseNumbers = other.purchaseNumbers;
    }
    return *this;
}

// Getters
int Customer::getId() const {
    return id;
}

std::string Customer::getTitle() const {
    return title;
}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getType() const {
    return type;
}

std::vector<int> Customer::getPurchaseNumbers() const {
    return purchaseNumbers;
}

// Setters
void Customer::setId(int id) {
    this->id = id;
}

void Customer::setTitle(const std::string& title) {
    this->title = title;
}

void Customer::setName(const std::string& name) {
    this->name = name;
}

void Customer::setType(const std::string& type) {
    // Validation for type: only "New" or "Regular" are allowed
    if (type == "New" || type == "Regular") {
        this->type = type;
    }
}

void Customer::setPurchaseNumbers(const std::vector<int>& purchaseNumbers) {
    this->purchaseNumbers = purchaseNumbers;
}

// Overloaded operators
bool Customer::operator==(const Customer& other) const {
    return id == other.id; // Compare based on ID
}

bool Customer::operator!=(const Customer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Customer& customer) {
    os << "ID: " << customer.id << ", Title: " << customer.title
       << ", Name: " << customer.name << ", Type: " << customer.type
       << ", Purchase Numbers: ";

    for (size_t i = 0; i < customer.purchaseNumbers.size(); ++i) {
        os << customer.purchaseNumbers[i];
        if (i < customer.purchaseNumbers.size() - 1) {
            os << ", ";
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Customer& customer) {
    std::string temp_input;

    std::cout << "Enter customer ID: ";
    is >> customer.id;
    std::getline(is, temp_input); // Consume the rest of the line after reading int

    std::cout << "Enter customer title: ";
    std::getline(is, customer.title);

    std::cout << "Enter customer name: ";
    std::getline(is, customer.name);

    std::cout << "Enter customer type (New/Regular): ";
    std::getline(is, customer.type);

    std::cout << "Enter number of purchases: ";
    int numPurchases;
    is >> numPurchases;
    std::getline(is, temp_input); // Consume the rest of the line after reading int

    customer.purchaseNumbers.clear();
    for (int i = 0; i < numPurchases; ++i) {
        std::cout << "Enter purchase number " << (i + 1) << ": ";
        int purchaseNum;
        is >> purchaseNum;
        std::getline(is, temp_input); // Consume the rest of the line after reading int
        customer.purchaseNumbers.push_back(purchaseNum);
    }
    
    return is;
}
