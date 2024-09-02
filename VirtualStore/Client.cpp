#include "Client.h"

char* Client::GetPassword()
{
	return user.password;
}

int Client::GetType()
{
	return user.type;
}

const int Client::GetLastPurchaseDate()
{
	return user.lastPurchaseDate;
}

Client::Client()
{
}

Client::Client(User user): user(user)
{
}

Client::Client(char name[15], char surname[15], char username[15], char password[8], int type)
{
	user = User(name, surname, username, password, type, false);
}

Client::~Client()
{
}

char* Client::GetName()
{
	return user.name;
}

char* Client::GetSurname()
{
	return user.surname;
}

char* Client::GetUsename()
{
	return user.username;
}

void Client::AddPurchaseAmount(double sum)
{
	user.lastPurchaseDate = GetDate();
	user.purchasesSum += sum;
}

double Client::GetPurchasesSum()
{
	return user.purchasesSum;
}

bool Client::IsWorker()
{
	return false;
}

BasketController& Client::GetBasket()
{
	return basket;
}

void Client::SayHi()
{
	std::cout << "Здравствуйте, " << GetName() << " " << GetSurname() << (GetType() ? " (VIP)!" : "!") << std::endl;
}

void Client::Info()
{
	std::cout << GetName() << " " << GetSurname() << " " << (GetType() ? " (VIP)\n" : "\n")
		<< "Сумма всех покупок: " << GetPurchasesSum() << "грн\n";

	if (user.lastPurchaseDate == -1) {
		return;
	}

	std::cout << "Дата последней покупки: " << getCurrentDateTime(GetLastPurchaseDate()) << std::endl;
}

Client& Client::operator=(const Client& other)
{
	user = other.user;
	return *this;
}

bool operator==(const Client& lhs, const Client& rhs)
{
	return lhs.user == rhs.user;
}

bool operator!=(const Client& lhs, const Client& rhs)
{
	return !(lhs.user == rhs.user);
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
	os << client.user;
	return os;
}

std::istream& operator>>(std::istream& is, Client& client)
{
	is >> client.user;
	return is;
}
