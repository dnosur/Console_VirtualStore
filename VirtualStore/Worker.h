#pragma once
#include <iostream>

#include "User.h"
#include "IUser.h"

#include "utilities.h"

class Worker : public IUser
{
	User user;
	BasketController basket;

	char* GetPassword();
	int GetType();

	const char* GetPositionName();
	const int GetLastPurchaseDate();
public:

	Worker();
	Worker(User user);
	Worker(char name[15], char surname[15], char username[15], char password[8], int type);
	~Worker();

	char* GetName();
	char* GetSurname();
	char* GetUsename();

	void AddPurchaseAmount(double sum);
	double GetPurchasesSum();

	bool IsWorker();

	BasketController& GetBasket();

	void SayHi();
	void Info();

	Worker& operator=(const Worker& other);

	friend bool operator==(const Worker& lhs, const Worker& rhs);
	friend bool operator!=(const Worker& lhs, const Worker& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Worker& worker);
	friend std::istream& operator>>(std::istream& is, Worker& worker);
};