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
		std::cout << ">>>>Доступные команды<<<<"_tr << std::endl << std::endl;
		std::cout << "1. вставить строку вперед"_tr << std::endl;
		std::cout << "2. вставить строку вниз"_tr << std::endl;
		std::cout << "3. вставить секцию вперед"_tr << std::endl;
		std::cout << "4. вставить секцию вниз"_tr << std::endl;
		std::cout << "5. удалить строку спереди"_tr << std::endl;
		std::cout << "6. удалить строку снизу"_tr << std::endl;
		std::cout << "7. вывести свободные узлы"_tr << std::endl;
		std::cout << "8. выйти из редактирования текста"_tr << std::endl << std::endl;
		std::cout << "\n== Введите команду\n>>> "_tr;
		std::cin >> command;
		std::cout << std::endl;
		if (command < 0 || command > 8)
		{
			std::cout << "== Ошибка: некорректный номер команды"_tr << std::endl;
			continue;
		}
		if (command != 7 && command != 8)
		{
			std::cout << "== Введите номер строки, которую вы хотите редактировать\n>>> "_tr;
			std::cin >> line_num;
			std::cout << std::endl;
			if (line_num >= textlen(text) || line_num < 0)
			{
				std::cout << "== Ошибка: некорректный номер строки"_tr << std::endl << std::endl;
				continue;
			}
		}
		switch (command)
		{
		case 1:
		{
			char str[1000] = { 0 };
			std::cout << "== Введите строку для вставки\n>>> "_tr;
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
			std::cout << "== Введите строку для вставки\n>>> "_tr;
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
			std::cout << "== Введите название секции\n>>> "_tr;
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
			std::cout << "== Введите название секции\n>>> "_tr;
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
		std::cout << ">>>>Доступные команды<<<<"_tr << std::endl << std::endl;;
		std::cout << "1. загрузить текст из файла"_tr << std::endl;
		std::cout << "2. сохранить текст в файл"_tr << std::endl;
		std::cout << "3. вывести текст"_tr << std::endl;
		std::cout << "4. начать редактирование в консоли"_tr << std::endl;
		std::cout << "5. выйти"_tr << std::endl;
		std::cout << "\n== Введите команду\n>>> "_tr;
		std::cin >> command;
		std::cout << std::endl;
		switch (command)
		{
		case 1:
		{
			std::cout << "== Введите имя файла\n>>> "_tr;
			std::cin >> filename;
			std::cout << std::endl;
			text.ReadFromFile(filename);
			break;
		}
		case 2:
		{
			std::cout << "== Введите имя файла\n>>> "_tr;
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
			std::cout << "== Ошибка: некорректный номер команды"_tr << std::endl << std::endl;
			break;
		}
		}
	}
}

int main()
{
	menu();
}
