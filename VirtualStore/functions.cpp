#include "functions.h"

IUser* CreateUser()
{
    setlocale(LC_ALL, "Russian");
    int userType = 0;

    auto checkStr = [](const std::string& str, const int length) -> bool {
        return containsDigit(str) || str.size() <= 0 || str.size() >= length;
    };

    while (userType < 1 || userType > 2) {
        clear();
        cout << "Укажите тип учётной записи (1 - Клиент, 2 - Рабочий): ";
        cin >> userType;
    }

    string name, surname, username, password;

    do {
        clear();
        cout << "Введите ваше имя: ";
        cin >> name;
    } while (checkStr(name, 15));

    do {
        clear();
        cout << "Введите вашу фамилию: ";
        cin >> surname;
    } while (checkStr(surname, 15));

    do {
        clear();
        cout << "Введите ваше имя пользователя: ";
        cin >> username;
    } while (checkStr(username, 15));

    do {
        clear();
        cout << "Введите пароль: ";
        cin >> password;
    } while (password.size() < 6);

    int userPos = 0;

    if (userType == 1) {
        while (userPos < 1 || userPos > 2) {
            clear();
            cout << "Вы VIP клиент (1 - Да, 2 - Нет)?\n: ";
            cin >> userPos;
        }
    }

    if (userType == 2) {
        while (userPos < 1 || userPos > 3) {
            clear();
            cout << "Укажите вашу должность: " << endl
                 << "1. Обычный сотрудник." << endl
                 << "2. Менеджер." << endl
                 << "3. Директор." << endl
                 << ": ";
            cin >> userPos;
        }
    }

    if (userType == 1) {
        return new Client((char*)name.c_str(), (char*)surname.c_str(), (char*)username.c_str(), (char*)password.c_str(), userType == 1);
    }
    return new Worker((char*)name.c_str(), (char*)surname.c_str(), (char*)username.c_str(), (char*)password.c_str(), userType);
}

void Login(string& username, string& password)
{
    clear();

    cout << "Логин: ";
    cin >> username;

    cout << "Пароль: ";
    cin >> password;
}

void ShowMenu(IUser*& user, int& point)
{
    clear();
    user->SayHi();

    if (!user->IsWorker()) {
        return;
    }

    cout << "1. Вывести всех клиентов." << endl
        << "2. Вывести VIP клиентов." << endl
        << "3. Вывести всех клиентов с покупками." << endl
        << "4. Клиент с самой дорогой покупкой." << endl
        << "5. Добавить товар." << endl
        << "6. Изменить статус товара." << endl
        << "7. Совершить покупку." << endl
        << "8. Выход" << endl
        << ": ";

    cin >> point;
    return clear();
}

void ShowAllClients(UserController& userController)
{
    for (IUser* user : userController.GetUsers()) {
        user->Info();
        cout << endl;
    }
    pause();
}

void ShowAllVipClients(UserController& userController)
{
    for (IUser* user : userController.GetUsers()) {
        if (user->IsWorker()) {
            continue;
        }

        if (!user->GetType()) {
            continue;
        }

        user->Info();
        cout << endl;
    }
    pause();
}

void ShowAllClientsWithPurchases(UserController& userController)
{
    int count = 0;
    for (IUser* user : userController.GetUsers()) {
        if (user->IsWorker() || user->GetPurchasesSum() <= 0) {
            continue;
        }

        count++;
        user->Info();
        cout << endl;
    }

    cout << ((count) ? "" : "Нету пользователей с покупками!\n");
    pause();
}

void ShowClientsWithRichestPurchase(UserController& userController)
{
    IUser* temp = nullptr;
    double minSum = DBL_MAX;

    for (IUser* user : userController.GetUsers()) {
        if (user->IsWorker() || user->GetPurchasesSum() <= 0) {
            continue;
        }

        if (user->GetPurchasesSum() > minSum) {
            continue;
        }

        temp = user;
        minSum = user->GetPurchasesSum();
    }

    if (temp == nullptr) {
        cout << "Ни один полбзователь ещё не совершил покупку!";
        return pause();
    }

    temp->Info();
    pause();
}

void AddProduct(Shop& shop)
{
    char name[15];
    double price;

    cout << "Введите название товара: ";
    cin >> name;

    cout << "Введите цену: ";
    cin >> price;

    shop.PushProduct(Product(name, price));
}

void ChangeProductStatus(Shop& shop)
{
    if (shop.GetProductsCount() <= 0) {
        cout << "Нету товаров на складе!";
        return pause();
    }

    int point = 0;
    while (point < 1 || point > shop.GetProductsCount()) {
        clear();
        for (int i = 0; i < shop.GetProductsCount(); i++) {
            Product product = shop.GetProduct(i);
            cout << i + 1 << ". " << product.name << " " << product.price << " грн\n";
        }
        cout << ": ";
        cin >> point;
    }
    point--;

    int status = 0;
    Product product = shop.GetProduct(point);
    while (status < 1 || status > 2) {
        clear();
        cout << product.name << " " << product.price << " грн\n";
        cout << "Укажите статус продукта (1 - Имеется, 2 - Продан): ";
        cin >> status;
    }

    if (status == 2) {
        shop.RemoveProduct(point);
    }
}

void Purchase(Shop& shop, IUser& user)
{
    if (shop.GetProductsCount() <= 0) {
        cout << "Нету товаров на складе!";
        return pause();
    }

    int point = -1;
    int count = 0;

    while (point != 0 || point > shop.GetProductsCount()) {
        clear();

        cout << "Корзина ";
        if (!user.GetBasket().GetCount()) {
            cout << "пуста!";
        }
        else {
            cout << user.GetBasket().GetSum(user.IsWorker(), user.GetType()) << " грн.";
        }
        cout << endl;

        cout << "\n0. Закончить покупку.\n";
        for (int i = 0; i < shop.GetProductsCount(); i++) {
            cout << i + 1 << ". " << shop.GetProduct(i).name << " " << shop.GetProduct(i).price << "грн\n";
        }
        cout << ": ";
        cin >> point;

        if (!point) {
            break;
        }

        if (point > shop.GetProductsCount()) {
            continue;
        }

        point--;

        while (count < 1) {
            clear();
            cout << shop.GetProduct(point).name << " " << shop.GetProduct(point).price << "грн\n";
            cout << "Колличество товара: ";
            cin >> count;
        }

        for (int i = 0; i < count; i++) {
            user.GetBasket().Push(shop.GetProduct(point));
        }

        clear();
        cout << shop.GetProduct(point).name << " добавлено в колличестве " << count << " шт.";
        pause();
        clear();

        point = -1;
        count = 0;
    }

    clear();
    cout << "Общая сумма: " << user.GetBasket().GetSum(user.IsWorker(), user.GetType()) << ". Спасибо за покупку!";
    user.AddPurchaseAmount(user.GetBasket().GetSum(user.IsWorker(), user.GetType()));
    user.GetBasket().Clear();
    pause();
}
