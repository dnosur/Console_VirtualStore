#include "UserController.h"

void UserController::Load()
{
    std::ifstream file(db_name);
    if (file.is_open()) {
        User user;
        while (file >> user) {
            if (user.isWorker) {
                users.push_back(new Worker(user));
            }
            else users.push_back(new Client(user));
        }
        file.close();
        std::cout << "������ ������� � ����� " << db_name << std::endl;
    }
    else {
        std::cerr << "������� �������� ����� " << db_name << std::endl;
    }
}

void UserController::Save()
{
    std::ofstream file(db_name);
    if (file.is_open()) {
        for (IUser*& user : users) {
             file << (User)user << std::endl;
        }
        file.close();
        std::cout << "������ �������� � ���� " << db_name << std::endl;
    }
    else {
        std::cerr << "������� �������� ����� " << db_name << std::endl;
    }
}

UserController::UserController()
{
    Load();
}

UserController::~UserController()
{
    Save();
}

IUser* UserController::Auth(char username[15], char password[8])
{
    for (IUser*& user : users) {
        if (strcmp(user->GetUsename(), username) == 0
            && strcmp(user->GetPassword(), password) == 0) {
            return user;
        }
    }
    return nullptr;
}

bool UserController::SingUp(IUser& user)
{
    if (IsExist(user.GetUsename())) {
        return false;
    }

    users.push_back(&user);
    Save();
}

bool UserController::IsExist(char username[15])
{
    for (IUser*& user : users) {
        if (strcmp(user->GetUsename(), username) == 0) {
            return true;
        }
    }
    return false;
}

const vector<IUser*>& UserController::GetUsers()
{
    return users;
}
