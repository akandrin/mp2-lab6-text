#include <iostream>
#include <cassert>
#include <fstream>
#include <clocale>
#include "TText.h"

class MyString
{
	std::string data;
public:
	MyString(const char* str) : data(str) {}
	friend std::ostream& operator<<(std::ostream& out, const MyString& str);
};

std::ostream& operator<<(std::ostream& out, const MyString& str)
{
	const char* currentLocale = setlocale(LC_ALL, "");

	out << str.data;

	setlocale(LC_ALL, currentLocale); // restore local
	return out;
}

MyString operator "" _tr(const char* str, size_t size)
{
	return MyString(str);
}


int textlen(const TText& text)
{
	int size = 0;
	for (text.Reset(); !text.IsEnd(); text.GoNext(), size++);
	return size;
}

void editMenu(TText& text)
{
	int command = 0;
	int line_num = -1;
	while (command != 8)
	{
		std::cout << std::endl << text << std::endl << std::endl;
		std::cout << ">>>>��������� �������<<<<"_tr << std::endl << std::endl;
		std::cout << "1. �������� ������ ������"_tr << std::endl;
		std::cout << "2. �������� ������ ����"_tr << std::endl;
		std::cout << "3. �������� ������ ������"_tr << std::endl;
		std::cout << "4. �������� ������ ����"_tr << std::endl;
		std::cout << "5. ������� ������ �������"_tr << std::endl;
		std::cout << "6. ������� ������ �����"_tr << std::endl;
		std::cout << "7. ������� ��������� ����"_tr << std::endl;
		std::cout << "8. ����� �� �������������� ������"_tr << std::endl << std::endl;
		std::cout << "\n== ������� �������\n>>> "_tr;
		std::cin >> command;
		std::cout << std::endl;
		if (command < 0 || command > 8)
		{
			std::cout << "== ������: ������������ ����� �������"_tr << std::endl;
			continue;
		}
		if (command != 7 && command != 8)
		{
			std::cout << "== ������� ����� ������, ������� �� ������ �������������\n>>> "_tr;
			std::cin >> line_num;
			std::cout << std::endl;
			if (line_num >= textlen(text) || line_num < 0)
			{
				std::cout << "== ������: ������������ ����� ������"_tr << std::endl << std::endl;
				continue;
			}
		}
		switch (command)
		{
		case 1:
		{
			char str[1000] = { 0 };
			std::cout << "== ������� ������ ��� �������\n>>> "_tr;
			std::cin >> str;
			std::cout << std::endl;
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.InsNextLine(str);
			break;
		}
		case 2:
		{
			char str[1000] = { 0 };
			std::cout << "== ������� ������ ��� �������\n>>> "_tr;
			std::cin >> str;
			std::cout << std::endl;
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.InsDownLine(str);
			break;
		}
		case 3:
		{
			char str[1000] = { 0 };
			std::cout << "== ������� �������� ������\n>>> "_tr;
			std::cin >> str;
			std::cout << std::endl;
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.InsNextSection(str);
			break;
		}
		case 4:
		{
			char str[1000] = { 0 };
			std::cout << "== ������� �������� ������\n>>> "_tr;
			std::cin >> str;
			std::cout << std::endl;
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.InsDownSection(str);
			break;
		}
		case 5:
		{
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.DelNextLine();
			break;
		}
		case 6:
		{
			text.Reset();
			for (int i = 0; i < line_num && !text.IsEnd(); i++, text.GoNext());
			text.DelDownLine();
			break;
		}
		case 7:
			TNode::PrintFree();
			break;
		case 8:
			TNode::CleanMem(text);
			return;
		}
	}
}

void menu()
{
	int command = 0;
	TText text;
	char* filename = new char[100];
	while (command != 5)
	{
		std::cout << ">>>>��������� �������<<<<"_tr << std::endl << std::endl;;
		std::cout << "1. ��������� ����� �� �����"_tr << std::endl;
		std::cout << "2. ��������� ����� � ����"_tr << std::endl;
		std::cout << "3. ������� �����"_tr << std::endl;
		std::cout << "4. ������ �������������� � �������"_tr << std::endl;
		std::cout << "5. �����"_tr << std::endl;
		std::cout << "\n== ������� �������\n>>> "_tr;
		std::cin >> command;
		std::cout << std::endl;
		switch (command)
		{
		case 1:
		{
			std::cout << "== ������� ��� �����\n>>> "_tr;
			std::cin >> filename;
			std::cout << std::endl;
			text.ReadFromFile(filename);
			break;
		}
		case 2:
		{
			std::cout << "== ������� ��� �����\n>>> "_tr;
			std::cin >> filename;
			std::cout << std::endl;
			text.PrintToFile(filename);
			break;
		}
		case 3:
		{
			std::cout << std::endl << text << std::endl << std::endl;
			break;
		}
		case 4:
		{
			system("cls");
			editMenu(text);
			system("cls");
			break;
		}
		case 5:
			return;
		default:
		{
			std::cout << "== ������: ������������ ����� �������"_tr << std::endl << std::endl;
			break;
		}
		}
	}
}

int main()
{
	menu();
}
