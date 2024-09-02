#include "Shop.h"

void Shop::Save()
{
    std::ofstream file(db_name);
    if (file.is_open()) {
        for (Product& product : products) {
            file << product << std::endl;
        }
        file.close();
        std::cout << "Список записано у файл " << db_name << std::endl;
    }
    else {
        std::cerr << "Помилка відкриття файлу " << db_name << std::endl;
    }
}

void Shop::Load()
{
    std::ifstream file(db_name);
    if (file.is_open()) {
        Product value;
        while (file >> value) {
            PushProduct(value);
        }
        file.close();
        std::cout << "Список зчитано з файлу " << db_name << std::endl;
    }
    else {
        std::cerr << "Помилка відкриття файлу " << db_name << std::endl;
    }
}

Shop::Shop()
{
    Load();
}

Shop::~Shop()
{
    Save();
}

const Product& Shop::GetProduct(const int index)
{
    if (index < 0 || index >= GetProductsCount()) {
        throw "Index error!";
    }
    return products[index];
}

int Shop::GetProductsCount()
{
    return products.size();
}

void Shop::PushProduct(Product product)
{
    products.push_back(product);
}

void Shop::RemoveProduct(int index)
{
    products.erase(products.begin() + index);
}
