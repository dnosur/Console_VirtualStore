#include "Worker.h"

char* Worker::GetPassword()
{
    return user.password;
}

int Worker::GetType()
{
    return user.type;
}

const char* Worker::GetPositionName()
{
    const int type = GetType();

    if (type == 1) {
        return "���������";
    }

    if (type == 2) {
        return "��������";
    }

    return (type == 3 ? "��������" : "");
}

Worker::Worker()
{
}

Worker::Worker(User user) : user(user)
{
}

Worker::Worker(char name[15], char surname[15], char username[15], char password[8], int type)
{
    user = User(name, surname, username, password, type, true);
}

Worker::~Worker()
{
}

char* Worker::GetName()
{
    return user.name;
}

char* Worker::GetSurname()
{
    return user.surname;
}

char* Worker::GetUsename()
{
    return user.username;
}

void Worker::AddPurchaseAmount(double sum)
{
    user.lastPurchaseDate = GetDate();
    user.purchasesSum += sum;
}

double Worker::GetPurchasesSum()
{
    return user.purchasesSum;
}

const int Worker::GetLastPurchaseDate()
{
    return user.lastPurchaseDate;
}

bool Worker::IsWorker()
{
    return true;
}

BasketController& Worker::GetBasket()
{
    return basket;
}

void Worker::SayHi()
{
    std::cout << "������������, " << GetName() << " " << GetSurname() << " (" << GetPositionName() << ")!\n";
}

void Worker::Info()
{
    std::cout << GetName() << " " << GetSurname() << ", ���������: " << GetPositionName() << std::endl
        << "����� ���� �������: " << GetPurchasesSum() << "���\n";

    if (user.lastPurchaseDate == -1) {
        return;
    }

    std::cout << "���� ��������� �������: " << getCurrentDateTime(GetLastPurchaseDate()) << std::endl;
}

Worker& Worker::operator=(const Worker& other)
{
    user = other.user;
    return *this;
}

bool operator==(const Worker& lhs, const Worker& rhs)
{
    return lhs.user == rhs.user;
}

bool operator!=(const Worker& lhs, const Worker& rhs)
{
    return !(lhs.user == rhs.user);
}

std::ostream& operator<<(std::ostream& os, const Worker& worker)
{
    os << worker.user;
    return os;
}

std::istream& operator>>(std::istream& is, Worker& worker)
{
    is >> worker.user;
    return is;
}
