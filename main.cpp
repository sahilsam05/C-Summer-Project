#include "Customer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

class CustomerManager {
private:
    std::vector<Customer> customers;

public:
    void addCustomer() {
        Customer customer;
        std::cin >> customer;
        customers.push_back(customer);
        std::cout << "Customer added successfully!\n";
    }

    void displayAllCustomers() {
        if (customers.empty()) {
            std::cout << "No customers found.\n";
            return;
        }

        std::cout << "\n1. Display in order of customer name\n";
        std::cout << "2. Display by type\n";
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displayByName();
        } else if (choice == 2) {
            displayByType();
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    void displayByName() {
        std::vector<Customer> sortedCustomers = customers;
        std::sort(sortedCustomers.begin(), sortedCustomers.end(),
                  [](const Customer& a, const Customer& b) {
                      return a.getName() < b.getName();
                  });

        std::cout << "\nCustomers sorted by name:\n";
        for (const auto& customer : sortedCustomers) {
            std::cout << customer << std::endl;
        }
    }

    void displayByType() {
        std::cout << "Enter type (New/Regular): ";
        std::string type;
        std::cin >> type;

        std::cout << "\nCustomers of type " << type << ":\n";
        bool found = false;
        for (const auto& customer : customers) {
            if (customer.getType() == type) {
                std::cout << customer << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No customers found with type " << type << std::endl;
        }
    }

    void findCustomer() {
        std::cout << "Enter customer ID: ";
        int id;
        std::cin >> id;

        const Customer* customerPtr = findCustomerById(id);
        if (customerPtr != nullptr) {
            std::cout << "Customer found: " << *customerPtr << std::endl;
        } else {
            std::cout << "Customer " << id << " not found.\n";
        }
    }

    void findByPurchaseNumber() {
        std::cout << "Enter purchase number: ";
        int purchaseNum;
        std::cin >> purchaseNum;

        const Customer* customerPtr = findCustomerByPurchaseNumber(purchaseNum);
        if (customerPtr != nullptr) {
            std::cout << "Customer found: " << *customerPtr << std::endl;
        } else {
            std::cout << "No customer found with purchase number " << purchaseNum << std::endl;
        }
    }

    const Customer* findCustomerById(int id) const {
        for (const auto& customer : customers) {
            if (customer.getId() == id) {
                return &customer;
            }
        }
        return nullptr;
    }

    const Customer* findCustomerByPurchaseNumber(int purchaseNum) const {
        for (const auto& customer : customers) {
            const auto& purchases = customer.getPurchaseNumbers();
            if (std::find(purchases.begin(), purchases.end(), purchaseNum) != purchases.end()) {
                return &customer;
            }
        }
        return nullptr;
    }

    void loadData() {
        std::ifstream file("customers.txt");
        if (!file.is_open()) {
            std::cout << "No existing customer data file found. Starting fresh.\n";
            return;
        }

        customers.clear();
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            // Basic parsing without stringstream or complex getline
            // Assuming format: ID;Title;Name;Type;PurchaseCount;P1;P2;...
            size_t prev_pos = 0;
            size_t current_pos = line.find(";");

            int id = std::stoi(line.substr(prev_pos, current_pos - prev_pos));
            prev_pos = current_pos + 1;
            current_pos = line.find(";", prev_pos);

            std::string title = line.substr(prev_pos, current_pos - prev_pos);
            prev_pos = current_pos + 1;
            current_pos = line.find(";", prev_pos);

            std::string name = line.substr(prev_pos, current_pos - prev_pos);
            prev_pos = current_pos + 1;
            current_pos = line.find(";", prev_pos);

            std::string type = line.substr(prev_pos, current_pos - prev_pos);
            prev_pos = current_pos + 1;
            current_pos = line.find(";", prev_pos);

            int purchaseCount = std::stoi(line.substr(prev_pos, current_pos - prev_pos));
            prev_pos = current_pos + 1;

            std::vector<int> purchaseNumbers;
            for (int i = 0; i < purchaseCount; ++i) {
                current_pos = line.find(";", prev_pos);
                if (current_pos == std::string::npos) { // Last purchase number
                    purchaseNumbers.push_back(std::stoi(line.substr(prev_pos)));
                } else {
                    purchaseNumbers.push_back(std::stoi(line.substr(prev_pos, current_pos - prev_pos)));
                    prev_pos = current_pos + 1;
                }
            }

            Customer customer(id, title, name, type, purchaseNumbers);
            customers.push_back(customer);
        }

        file.close();
        std::cout << "Loaded " << customers.size() << " customers from file.\n";
    }

    void saveData() {
        std::ofstream file("customers.txt");
        if (!file.is_open()) {
            std::cout << "Error: Could not save customer data.\n";
            return;
        }

        for (const auto& customer : customers) {
            file << customer.getId() << ";"
                 << customer.getTitle() << ";"
                 << customer.getName() << ";"
                 << customer.getType() << ";"
                 << customer.getPurchaseNumbers().size();

            for (int purchaseNum : customer.getPurchaseNumbers()) {
                file << ";" << purchaseNum;
            }
            file << "\n"; // Each customer record on a new line
        }

        file.close();
        std::cout << "Customer data saved successfully.\n";
    }

    void showMenu() {
        std::cout << "\n=== Customer Management System ===\n";
        std::cout << "1. Add Customer\n";
        std::cout << "2. Display All Customers\n";
        std::cout << "3. Find Customer by ID\n";
        std::cout << "4. Find Customer by Purchase Number\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose option: ";
    }

    void run() {
        loadData();

        int choice;
        do {
            showMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    addCustomer();
                    break;
                case 2:
                    displayAllCustomers();
                    break;
                case 3:
                    findCustomer();
                    break;
                case 4:
                    findByPurchaseNumber();
                    break;
                case 5:
                    saveData();
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    CustomerManager manager;
    manager.run();
    return 0;
}
