#pragma once
#include "BasketController.h"

__interface IUser {
	char* GetName();
	char* GetSurname();
	char* GetUsename();
	char* GetPassword();

	void AddPurchaseAmount(double sum);

	double GetPurchasesSum();
	const int GetLastPurchaseDate();

	int GetType();
	bool IsWorker();

	BasketController& GetBasket();

	void SayHi();
	void Info();
};