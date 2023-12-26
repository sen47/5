#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>

enum Sex { MALE = 1, FEMALE };
enum Param { KIND, NAME, AGE, SEX, PRICE, PARAM_SIZE };

struct Animal
{
	std::string m_kind, m_name;
	int m_age;
	Sex m_sex;
	double m_price;

	Animal(const std::string& kind, const std::string& name, const int age, const Sex sex, const double price)
		:m_kind(kind), m_name(name), m_age(age), m_sex(sex), m_price(price) {}

	bool operator ==(const Animal& other);

	std::string getInfo()const 
	{
		return "Kind: " + m_kind + ", name: " + m_name + ", age: " + std::to_string(m_age)
			+ ", sex: " + (m_sex == Sex::MALE ? "male" : "female") + ", price: " + std::to_string(m_price);
	}
};

class ZooMagazine
{
	friend std::ostream& operator<<(std::ostream& os, const ZooMagazine& zm);
	//friend std::istream& operator>>(std::istream& is, ZooMagazine& zm);

	std::vector<Animal>zooMagazine;

public:
	
	ZooMagazine() {};
	ZooMagazine(const std::string& kind, const std::string& name, const int age, const Sex sex, const double price);

	void addAnimal(const std::string& kind, const std::string& name, const int age, const Sex sex, const double price);
	void addAnimal(const Animal& animal);
	void deleteAnimal(const int index);
	void loadFromFile(std::fstream& file);
	int getSize() { return zooMagazine.size(); }
};