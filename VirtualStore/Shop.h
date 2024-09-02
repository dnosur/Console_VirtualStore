#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "Product.h"

class Shop
{
	std::vector<Product> products;
	const char* db_name = "products.txt";

	void Save();
	void Load();
public:
	Shop();
	~Shop();

	const Product& GetProduct(const int index);
	int GetProductsCount();

	void PushProduct(Product product);
	void RemoveProduct(int index);
};