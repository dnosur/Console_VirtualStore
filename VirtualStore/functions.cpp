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
        cout << "������� ��� ������� ������ (1 - ������, 2 - �������): ";
        cin >> userType;
    }

    string name, surname, username, password;

    do {
        clear();
        cout << "������� ���� ���: ";
        cin >> name;
    } while (checkStr(name, 15));

    do {
        clear();
        cout << "������� ���� �������: ";
        cin >> surname;
    } while (checkStr(surname, 15));

    do {
        clear();
        cout << "������� ���� ��� ������������: ";
        cin >> username;
    } while (checkStr(username, 15));

    do {
        clear();
        cout << "������� ������: ";
        cin >> password;
    } while (password.size() < 6);

    int userPos = 0;

    if (userType == 1) {
        while (userPos < 1 || userPos > 2) {
            clear();
            cout << "�� VIP ������ (1 - ��, 2 - ���)?\n: ";
            cin >> userPos;
        }
    }

    if (userType == 2) {
        while (userPos < 1 || userPos > 3) {
            clear();
            cout << "������� ���� ���������: " << endl
                 << "1. ������� ���������." << endl
                 << "2. ��������." << endl
                 << "3. ��������." << endl
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

    cout << "�����: ";
    cin >> username;

    cout << "������: ";
    cin >> password;
}

void ShowMenu(IUser*& user, int& point)
{
    clear();
    user->SayHi();

    if (!user->IsWorker()) {
        return;
    }

    cout << "1. ������� ���� ��������." << endl
        << "2. ������� VIP ��������." << endl
        << "3. ������� ���� �������� � ���������." << endl
        << "4. ������ � ����� ������� ��������." << endl
        << "5. �������� �����." << endl
        << "6. �������� ������ ������." << endl
        << "7. ��������� �������." << endl
        << "8. �����" << endl
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

    cout << ((count) ? "" : "���� ������������� � ���������!\n");
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
        cout << "�� ���� ������������ ��� �� �������� �������!";
        return pause();
    }

    temp->Info();
    pause();
}

void AddProduct(Shop& shop)
{
    char name[15];
    double price;

    cout << "������� �������� ������: ";
    cin >> name;

    cout << "������� ����: ";
    cin >> price;

    shop.PushProduct(Product(name, price));
}

void ChangeProductStatus(Shop& shop)
{
    if (shop.GetProductsCount() <= 0) {
        cout << "���� ������� �� ������!";
        return pause();
    }

    int point = 0;
    while (point < 1 || point > shop.GetProductsCount()) {
        clear();
        for (int i = 0; i < shop.GetProductsCount(); i++) {
            Product product = shop.GetProduct(i);
            cout << i + 1 << ". " << product.name << " " << product.price << " ���\n";
        }
        cout << ": ";
        cin >> point;
    }
    point--;

    int status = 0;
    Product product = shop.GetProduct(point);
    while (status < 1 || status > 2) {
        clear();
        cout << product.name << " " << product.price << " ���\n";
        cout << "������� ������ �������� (1 - �������, 2 - ������): ";
        cin >> status;
    }

    if (status == 2) {
        shop.RemoveProduct(point);
    }
}

void Purchase(Shop& shop, IUser& user)
{
    if (shop.GetProductsCount() <= 0) {
        cout << "���� ������� �� ������!";
        return pause();
    }

    int point = -1;
    int count = 0;

    while (point != 0 || point > shop.GetProductsCount()) {
        clear();

        cout << "������� ";
        if (!user.GetBasket().GetCount()) {
            cout << "�����!";
        }
        else {
            cout << user.GetBasket().GetSum(user.IsWorker(), user.GetType()) << " ���.";
        }
        cout << endl;

        cout << "\n0. ��������� �������.\n";
        for (int i = 0; i < shop.GetProductsCount(); i++) {
            cout << i + 1 << ". " << shop.GetProduct(i).name << " " << shop.GetProduct(i).price << "���\n";
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
            cout << shop.GetProduct(point).name << " " << shop.GetProduct(point).price << "���\n";
            cout << "����������� ������: ";
            cin >> count;
        }

        for (int i = 0; i < count; i++) {
            user.GetBasket().Push(shop.GetProduct(point));
        }

        clear();
        cout << shop.GetProduct(point).name << " ��������� � ����������� " << count << " ��.";
        pause();
        clear();

        point = -1;
        count = 0;
    }

    clear();
    cout << "����� �����: " << user.GetBasket().GetSum(user.IsWorker(), user.GetType()) << ". ������� �� �������!";
    user.AddPurchaseAmount(user.GetBasket().GetSum(user.IsWorker(), user.GetType()));
    user.GetBasket().Clear();
    pause();
}
