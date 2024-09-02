#pragma once
#include <vector>

#include "Product.h"

class BasketController
{
	std::vector<Product> products;

	double GetSale(double sum, int post);
public:
	void Push(Product product);
	void Remove(int index);

	double GetSum(bool isWorker = false, int post = 0);
	int GetCount();

	void Clear();

	BasketController& operator -=(const Product& product);
	Product& operator [](const int index);
};