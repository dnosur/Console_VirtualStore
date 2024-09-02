#pragma once
#include <iostream>

#include "User.h"
#include "IUser.h"

#include "utilities.h"

class Client : public IUser
{
	User user;
	BasketController basket;

	char* GetPassword();
	int GetType();
	const int GetLastPurchaseDate();
public:

	Client();
	Client(User user);
	Client(char name[15], char surname[15], char username[15], char password[8], int type);
	~Client();

	char* GetName();
	char* GetSurname();
	char* GetUsename();

	void AddPurchaseAmount(double sum);

	double GetPurchasesSum();
	bool IsWorker();

	BasketController& GetBasket();

	void SayHi();
	void Info();

    Client& operator=(const Client& other);

    friend bool operator==(const Client& lhs, const Client& rhs);
	friend bool operator!=(const Client& lhs, const Client& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Client& client);
	friend std::istream& operator>>(std::istream& is, Client& client);
};