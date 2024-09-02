// VirtualStore.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "UserController.h"
#include "functions.h"
#include "utilities.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char date[15];
    strcpy_s(date, (char*)getCurrentDateTime().c_str());

    UserController userController;

    Client client((char*)"Vasya", (char*)"Ezhov", (char*)"ez_vasya", (char*)"vs1488", 1);
    userController.SingUp(client);

    Worker worker((char*)"Oleg", (char*)"Vorobyov", (char*)"vorob", (char*)"vor228", 2);
    userController.SingUp(worker);

    int point;
    IUser* user = nullptr;

    while (user == nullptr) {
        clear();
        cout << "1. Создать новую учётную запись" << endl
            << "2. Войти в существующую учётную запись" << endl
            << "3. Выход" << endl
            << ": ";
        cin >> point;

        if (point == 1) {
            userController.SingUp(*CreateUser());
            continue;
        }

        if (point == 2) {
            string username, password;
            Login(username, password);
            user = userController.Auth((char*)username.c_str(), (char*)password.c_str());

            if (user != nullptr) {
                break;
            }

            cout << "Неверный логин или пароль!";
            pause();
        }
    }

    Shop shop;

    while (true) {
        ShowMenu(user, point);

        if (!user->IsWorker()) {
            Purchase(shop, *user);
            return 0;
        }

        if (point == 1) {
            ShowAllClients(userController);
        }

        if (point == 2) {
            ShowAllVipClients(userController);
        }

        if (point == 3) {
            ShowAllClientsWithPurchases(userController);
        }

        if (point == 4) {
            ShowClientsWithRichestPurchase(userController);
        }

        if (point == 5) {
            AddProduct(shop);
        }

        if (point == 6) {
            ChangeProductStatus(shop);
        }

        if (point == 7) {
            Purchase(shop, *user);
        }

        if (point == 8) {
            return 0;
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
