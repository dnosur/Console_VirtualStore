#pragma once
#include <istream>

#include "IUser.h"

struct User {
    User() {
        strcpy_s(this->name, "John");
        strcpy_s(this->surname, "Doe");
        strcpy_s(this->username, "DeadMan1488");
        strcpy_s(this->password, "1111");

        isWorker = false;
        type = -1;

        purchasesSum = .0;
        lastPurchaseDate = -1;
    }
    User(IUser*& user) {
        strcpy_s(this->name, user->GetName());
        strcpy_s(this->surname, user->GetSurname());
        strcpy_s(this->password, user->GetPassword());
        strcpy_s(this->username, user->GetUsename());

        this->type = user->GetType();
        this->isWorker = user->IsWorker();

        purchasesSum = user->GetPurchasesSum();
        lastPurchaseDate = user->GetLastPurchaseDate();
    }
    User(char name[15], char surname[15], char username[15], char password[8], int type, bool isWorker) {
        strcpy_s(this->name, name);
        strcpy_s(this->surname, surname);
        strcpy_s(this->password, password);
        strcpy_s(this->username, username);

        this->type = type;
        this->isWorker = isWorker;

        purchasesSum = .0;
        lastPurchaseDate = -1;
    }

    char name[15];
    char surname[15];
    char username[15];
    char password[8];

    bool isWorker;
    int type;

    double purchasesSum;
    int lastPurchaseDate;

    User& operator=(const User& other) {
        if (this != &other) {
            strcpy_s(this->name, other.name);
            strcpy_s(this->surname, other.surname);
            strcpy_s(this->username, other.username);
            strcpy_s(this->password, other.password);

            this->type = other.type;
            this->isWorker = other.isWorker;

            this->purchasesSum = other.purchasesSum;
            this->lastPurchaseDate = other.lastPurchaseDate;
        }
        return *this;
    }

    User& operator=(IUser*& other) {

        strcpy_s(this->name, other->GetName());
        strcpy_s(this->surname, other->GetSurname());
        strcpy_s(this->username, other->GetUsename());
        strcpy_s(this->password, other->GetPassword());

        this->type = other->GetType();
        this->isWorker = other->IsWorker();

        this->purchasesSum = other->GetPurchasesSum();
        this->lastPurchaseDate = other->GetLastPurchaseDate();

        return *this;
    }

    friend bool operator==(const User& lhs, const User& rhs) {
        return strcmp(lhs.name, rhs.name) == 0 
                && strcmp(lhs.surname, rhs.surname) == 0
                && strcmp(lhs.password, rhs.password) == 0
                && strcmp(lhs.username, rhs.username) == 0
                && lhs.lastPurchaseDate == rhs.lastPurchaseDate
                && lhs.type == rhs.type
                && lhs.isWorker == rhs.isWorker
                && lhs.purchasesSum == rhs.purchasesSum;
    }

    friend bool operator==(const User& lhs, IUser*& rhs) {
        return strcmp(lhs.name, rhs->GetName()) == 0
            && strcmp(lhs.surname, rhs->GetSurname()) == 0
            && strcmp(lhs.password, rhs->GetPassword()) == 0
            && strcmp(lhs.username, rhs->GetUsename()) == 0
            && lhs.lastPurchaseDate == rhs->GetLastPurchaseDate()
            && lhs.type == rhs->GetType()
            && lhs.isWorker == rhs->IsWorker()
            && lhs.purchasesSum == rhs->GetPurchasesSum();
    }

    friend bool operator!=(const User& lhs, const User& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator!=(const User& lhs, IUser*& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.name << " " << user.surname << " " << user.username << " " << user.lastPurchaseDate << " " << user.password << " " << user.type << " " << user.isWorker << " " << user.purchasesSum;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, User& user) {
        is >> user.name >> user.surname >> user.username >> user.lastPurchaseDate >> user.password >> user.type >> user.isWorker >> user.purchasesSum;
        return is;
    }
};