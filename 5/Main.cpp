//Необходимо создать класс — зоомагазин.В классе должны быть следующие поля : животное(напр.волк, пингвин, собака), пол, имя, цена, количество.
//Включить в состав класса необходимый минимум методов, обеспечивающий полноценное функционирование объектов указанного класса :
//
//Конструкторы(по умолчанию, с параметрами, копирования);
//Деструктор;
//Переопределить возможные для класса операции, продумать порядок их выполнения;
//Добавить необходимые методы.
//Предоставить возможность вводить данные с клавиатуры или из файла(с помощью конструктора или операцией »).

#include<iostream>
#include<string>
#include<fstream>

#include"ZooMagazine.h"

enum Actions { EXIT, ADD_ANIMAL, DELETE_ANIMAL, SHOW_MAGAZINE, SAVE, LOAD, ACTIONS_SIZE };

int menu();
Animal enterAnimalInfo();
void saveToFile(std::fstream& file, const std::string& path, const ZooMagazine& zm);
void loadFromFile(std::fstream& file, const std::string& path, ZooMagazine& zm);
void printMagazine(const ZooMagazine& zm);
void deleteAnimal(ZooMagazine& zm);

int main()
{
	std::string path{"file.txt"};
	std::fstream file;
	file.exceptions(std::fstream::failbit | std::fstream::badbit);

	ZooMagazine zm;

	int answer;
	do
	{
		answer = menu();

		switch (answer)
		{
		case Actions::ADD_ANIMAL:
			zm.addAnimal(enterAnimalInfo());
			break;
		case Actions::DELETE_ANIMAL:
			deleteAnimal(zm);
			break;
		case Actions::SHOW_MAGAZINE:
			printMagazine(zm);
			break;
		case Actions::SAVE:
			saveToFile(file, path, zm);
			break;
		case Actions::LOAD:
			loadFromFile(file, path, zm);
			break;
		case Actions::EXIT:
			std::cout << "Good bye!" << std::endl;
			break;
		}
	} while (answer != Actions::EXIT);

	return 0;
}

template<typename T>
T checkInput(const std::string& output)
{
	T input;
	while (true)
	{
		std::cout << output;
		std::cin >> input;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			return input;
	}
}

int menu()
{
	std::string output{"To add new animal - 1,\nto delete element - 2,\nto show magazine - 3,\nto save magazine - 4,\nto load magazine - 5,\nto exit - 0\nEnter: "};
	while (true)
	{
		int answer(checkInput<int>(output));
		if (answer >= Actions::EXIT && answer <= Actions::ACTIONS_SIZE)
			return answer;
		std::cout << "Error, try again!\n";
	}
}

Animal enterAnimalInfo()
{
	std::cout << "Enter kind of animal: ";
	std::string kind, name;
	std::cin >> kind;
	std::cout << "Enter name of animal: ";
	std::cin >> name;

	int age(checkInput<int>("Enter age of animal: "));

	int sex;
	while (true)
	{
		sex = checkInput<int>("Enter sex of animal, male - 1, female - 2: ");
		if (sex == Sex::MALE || sex == Sex::FEMALE)
			break;
		std::cout << "Error, try again!\n";
	}
	
	double price(checkInput<double>("Enter price of animal: "));

	std::cin.clear();
	std::cin.ignore(32767, '\n');

	return Animal(kind, name, age, static_cast<Sex>(sex), price);
}

void saveToFile(std::fstream&file,const std::string& path, const ZooMagazine&zm)
{
	try
	{
		file.open(path, std::fstream::out);

	}
	catch (const std::exception& ex)
	{
		std::cout << "Error in openning file to save, " << ex.what() << std::endl;
		file.open(path, std::fstream::out | std::fstream::app);
	}

	file << zm << '\n';

	try
	{
		if (file.is_open())
			file.close();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error in closing file to save, " << ex.what() << std::endl;
	}
}

void loadFromFile(std::fstream& file, const std::string& path, ZooMagazine& zm)
{
	try
	{
		file.open(path, std::fstream::in);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error of openning file to load, " << ex.what() << std::endl;
	}

	zm.loadFromFile(file);

	try
	{
		if (file.is_open())
			file.close();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error of closing file to load, " << ex.what() << std::endl;
	}
}

void printMagazine(const ZooMagazine& zm)
{
	std::cout << '\n' << zm << std::endl;
}

void deleteAnimal(ZooMagazine& zm)
{
	printMagazine(zm);
	while (true)
	{
		int index(checkInput<int>("Enter index of element need to delete: "));
		if (index >= 0 && index < zm.getSize())
		{
			zm.deleteAnimal(index);
			break;
		}
		else
			std::cout << "Error, try again!\n";
	}
}
