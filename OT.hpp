#include<windows.h>
#include<iostream>
#include<string>
#include<conio.h>
#include <thread>
#include <chrono>

using std::string;
using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

bool check = true;
bool cho = true;

HANDLE Font = GetStdHandle(STD_OUTPUT_HANDLE);

void slow_print(const string&, unsigned int);

void slow_print(const string&message, unsigned int millis_per_char)
{
	for (const char c : message)
	{
		cout << c << flush;
		sleep_for(milliseconds(millis_per_char));
	}
}

string O123 = "1) Login\n\n2) Exit Program\n\nChoice : ";
string U = "UserName / ID : ";
string P = "PassWord : ";
string E = "\nUncorrect please try angin.\n";

void Starting()
{
	string message = "------------------------------------------------------------------------------\n\n";
	string message1 = "------------------------------------------------------------------------------\n\n";
	string message2 = "------------------------------------------------------------------------------\n\n";
	string message3 = "---------------------------------Login System---------------------------------\n\n";
	string message4 = "------------------------------------------------------------------------------\n\n";
	string message5 = "------------------------------------------------------------------------------\n\n";
	string message6 = "------------------------------------------------------------------------------\n\n";

	SetConsoleTextAttribute(Font, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	slow_print(message + message1 + message2 + message3 + message4 + message5 + message6, 4);
}

void wh()
{
	HWND console = GetConsoleWindow();
	RECT lo;
	GetWindowRect(console, &lo); //stores the console's current dimensions

	MoveWindow(console, lo.left, lo.top, 800, 450, TRUE); // 800 width, 500 height
}

void Login()
{
	system("cls");
	system("color b");
	while (check)
	{
		::Starting();
		slow_print(U, 10);
		string name;
		std::cin >> name;
		std::cout << "\n";
		slow_print(P, 10);
		string pasw;
		std::cin >> pasw;

		if (name == "Amin" && pasw == "OMGTHISHAHA")
		{
			MessageBoxA(0, "Welcome Back ! Admin", "Successful", MB_ICONINFORMATION);
			check = false;
			system("cls");
		}
		else
		{
			SetConsoleTextAttribute(Font, FOREGROUND_RED | FOREGROUND_INTENSITY);
			slow_print(E, 10);
			Sleep(2000);
			system("color b");
			system("cls");
		}
	}
}

void Be()
{
	system("cls");
	system("color b");
	while (cho)
	{
	::Starting();
	slow_print(O123, 10);
	int begin_ch;
	std::cin >> begin_ch;
		if (begin_ch == 1)
		{
			cho = false;
			Login();
		}
		else if (begin_ch == 2)
		{
			cho = false;
			exit(0);
		}
		else
		{
			SetConsoleTextAttribute(Font, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "\nPlease Try Choice 1 or 2 ";
			Sleep(2000);
			system("cls");
			Be();
		}
	}
}