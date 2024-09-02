#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "IUser.h"

#include "Client.h"
#include "Worker.h"

using namespace std;

class UserController
{
	vector<IUser*> users;

	const char* db_name = "users.txt";

	void Load();
	void Save();
public:
	UserController();
	~UserController();

	IUser* Auth(char username[15], char password[8]);
	bool SingUp(IUser& user);

	bool IsExist(char username[15]);

	const vector<IUser*>& GetUsers();
};

