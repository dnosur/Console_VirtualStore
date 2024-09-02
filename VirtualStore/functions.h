#pragma once
#include <iostream>

#include "Shop.h"
#include "UserController.h"

#include "utilities.h"

using namespace std;

IUser* CreateUser();
void Login(string& username, string& password);

void ShowMenu(IUser*& user, int& point);

void ShowAllClients(UserController& userController);
void ShowAllVipClients(UserController& userController);
void ShowAllClientsWithPurchases(UserController& userController);

void ShowClientsWithRichestPurchase(UserController& userController);

void AddProduct(Shop& shop);

void ChangeProductStatus(Shop& shop);

void Purchase(Shop& shop, IUser& user);