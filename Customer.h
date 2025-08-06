#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <iostream>

class Customer
{
public:

    // Default constructor
    Customer();

    // Full constructor
    Customer(int id, const std::string& title, const std::string& name, const std::string& type, const std::vector<int>& purchaseNumbers);

    // Copy constructor
    Customer(const Customer& other);

    // Destructor
    ~Customer();

    // Assignment operator
    Customer& operator=(const Customer& other);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getName() const;
    std::string getType() const;
    std::vector<int> getPurchaseNumbers() const;

    // Setters
    void setId(int id);
    void setTitle(const std::string& title);
    void setName(const std::string& name);
    void setType(const std::string& type);
    void setPurchaseNumbers(const std::vector<int>& purchaseNumbers);

    // Overloaded operators
    bool operator==(const Customer& other) const;
    bool operator!=(const Customer& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Customer& customer);
    friend std::istream& operator>>(std::istream& is, Customer& customer);

private:
    int id;
    std::string title;
    std::string name;
    std::string type;
    std::vector<int> purchaseNumbers;

};


#endif //CUSTOMER_H
