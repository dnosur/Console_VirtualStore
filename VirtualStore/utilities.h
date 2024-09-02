#pragma once
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string>

void clear();
void pause();

void gotoxy(int X, int Y);

COORD getxy();
void getxy(int& x, int& y);

int randomInt(int min, int max);

bool isNumber(const std::string& s);

bool containsDigit(const std::string& str);

std::string getCurrentDateTime();
std::string getCurrentDateTime(time_t now);

time_t GetDate();