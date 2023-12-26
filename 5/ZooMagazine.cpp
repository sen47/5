#include "ZooMagazine.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Private
/////////////////////////////////////////////////////////////////////////////////////// Friend func
std::ostream& operator<<(std::ostream& os, const ZooMagazine& zm)
{
	for (const auto& el : zm.zooMagazine)
		os << el.getInfo() << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, ZooMagazine& zm)
{
	std::string bufer, temp;
	std::vector<std::string>animalInfo;
	
	std::getline(is, bufer);
	
	if (bufer != "\n")
	{
		for (int i = 0; i < bufer.size(); ++i)
		{
			if (bufer[i] == ':')
			{
				while (bufer[++i] != ',')
				{
					temp += bufer[i];
				}
				while (temp[0] == ' ')
					temp.erase(temp.begin());
				while (temp.size() - 1 == ' ')
					temp.erase(temp.end() - 1);
			}

			if (!temp.empty())
			{
				animalInfo.push_back(temp);
				temp.clear();
			}
		}
	}

	return is;
}

/////////////////////////////////////////////////////////////////////////////////////// Operator

bool Animal::operator==(const Animal& other)
{
	return (this->m_kind == other.m_kind) && (this->m_name == other.m_name) && (this->m_age == other.m_age) && (this->m_sex == other.m_sex) && (this->m_price == other.m_price);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Public
//////////////////////////////////////////////////////////////////////////////////////////// Ctor

ZooMagazine::ZooMagazine(const std::string& kind, const std::string& name, const int age, const Sex sex, const double price)
{
	addAnimal(kind, name, age, sex, price);
}

//////////////////////////////////////////////////////////////////////////////////////////// Func

void ZooMagazine::addAnimal(const std::string& kind, const std::string& name, const int age, const Sex sex, const double price)
{
	this->addAnimal(Animal(kind, name, age, sex, price));
}

void ZooMagazine::addAnimal(const Animal& animal)
{
	if (!zooMagazine.size() || std::find(zooMagazine.begin(), zooMagazine.end(), animal) == zooMagazine.end())
		zooMagazine.push_back(animal);
}

void ZooMagazine::deleteAnimal(const int index)
{
	zooMagazine.erase(zooMagazine.begin() + index);
}

void ZooMagazine::loadFromFile(std::fstream& file)
{
	std::string bufer, temp;
	std::vector<std::string>animalInfo;
	
	while (!file.eof())
	{
		try
		{
			std::getline(file, bufer);
		}
		catch(const std::exception&ex)
		{
			//std::cout << "Error of reading from file, " << ex.what() << std::endl;
		}

		if (bufer.size() && bufer != "\n")
		{
			for (int i = 0; i < bufer.size(); ++i)
			{
				if (bufer[i] == ':')
				{
					while (bufer[++i] != ',' && i < bufer.size())
					{
						temp += bufer[i];
					}
					while (temp[0] == ' ')
						temp.erase(temp.begin());
					while (temp.size() - 1 == ' ')
						temp.erase(temp.end() - 1);
				}

				if (!temp.empty())
				{
					animalInfo.push_back(temp);
					temp.clear();
				}
			}
		}
		if (animalInfo.size() == Param::PARAM_SIZE)
		{
			Animal animal(animalInfo[KIND], animalInfo[NAME], std::atoi(animalInfo[AGE].c_str()),
				(animalInfo[SEX] == "male" ? Sex::MALE : Sex::FEMALE), std::stod(animalInfo[PRICE].c_str()));

			addAnimal(animal);
		}

		bufer.clear();
		animalInfo.clear();
	}
}