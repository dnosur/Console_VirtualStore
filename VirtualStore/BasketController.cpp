#include "BasketController.h"

double BasketController::GetSale(double sum, int post)
{
	double saleProcent = .0f;

	if (post == 1) {
		saleProcent = 10;
	}

	if (post == 2) {
		saleProcent = 20;
	}

	if (post == 3) {
		saleProcent = 30;
	}

	return sum * (saleProcent / 100.0);
}

void BasketController::Push(Product product)
{
	products.push_back(product);
}

void BasketController::Remove(int index)
{
	products.erase(products.begin() + index);
}

double BasketController::GetSum(bool isWorker, int post)
{
	double sum = .0;
	for (Product& product : products) {
		sum += product.price;
	}
	return (!isWorker ? sum : sum - GetSale(sum, post));
}

int BasketController::GetCount()
{
	return products.size();
}

void BasketController::Clear()
{
	products.clear();
}

BasketController& BasketController::operator-=(const Product& product)
{
	auto it = std::find(products.begin(), products.end(), product);
	if (it != products.end()) {
		products.erase(it);
	}
	return *this;
}

Product& BasketController::operator[](const int index)
{
	if (index < 0 || index >= products.size()) {
		throw "Index error!";
	}
	return products[index];
}
