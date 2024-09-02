#pragma once
#include <istream>

struct Product {
    Product() {
        strcpy_s(this->name, "Empty");
        price = .0;
    }
    Product(char name[15], double price) {
        strcpy_s(this->name, name);
        this->price = price;
    }

    char name[15];
    double price;

    Product& operator=(const Product& other) {
        if (this != &other) {
            strcpy_s(this->name, other.name);
            this->price = other.price;
        }
        return *this;
    }

    friend bool operator==(const Product& lhs, const Product& rhs) {
        return strcmp(lhs.name, rhs.name) == 0
            && lhs.price == rhs.price;
    }

    friend bool operator!=(const Product& lhs, const Product& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << product.name << " " << product.price;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Product& product) {
        is >> product.name >> product.price;
        return is;
    }
};