#include "utilities.h"

void clear() {
	system("cls");
}

void pause() {
	_getch();
}

void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getxy(int& x, int& y) {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	x = screenBufferInfo.dwCursorPosition.X;
	y = screenBufferInfo.dwCursorPosition.Y;
}

COORD getxy() {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	return screenBufferInfo.dwCursorPosition;
}

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool isNumber(const std::string& s)
{
	try {
		std::stoi(s);
		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

bool containsDigit(const std::string& str)
{
	for (char c : str) {
		if (std::isdigit(c)) {
			return true; 
		}
	}
	return false;
}

std::string getCurrentDateTime() {
	std::time_t now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);

	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%d.%m.%y %H:%M", &timeinfo);
	return std::string(buffer);
}

std::string getCurrentDateTime(time_t now)
{
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);

	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%d.%m.%y %H:%M", &timeinfo);
	return std::string(buffer);
}

time_t GetDate()
{
	return std::time(nullptr);
}
