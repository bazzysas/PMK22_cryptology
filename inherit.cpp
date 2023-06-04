#include <iostream>
#include <Windows.h>
using namespace std; 

class Goods
{
protected: 
	string producerName;
	unsigned int countryCode;
	unsigned int price;
public:
	Goods() : producerName(" "), countryCode(482), price(0) {}
	Goods(string prodN, unsigned int cCode, unsigned int p) : producerName(prodN), countryCode(cCode), price(p) {}

	friend istream& operator >> (istream& is, Goods& s)
	{
		is >> s.producerName;
		is >> s.countryCode;
		is >> s.price;
		return is;
	}
	friend ostream& operator << (ostream& out, Goods& s)
	{
		out << s.producerName;
		out << s.countryCode;
		out << s.price;
		return out;
	}
	unsigned int getCountryCode()
	{
		return this->countryCode; 
	}
};
class Toy: public Goods
{
private:
	unsigned int ageLimit; 
	string toyName; 
public: 
	Toy() : ageLimit(0), toyName("def") {}
	Toy(unsigned int ageL,string toyN) : ageLimit(ageL), toyName(toyN){}
	friend ostream& operator << (ostream& out, Toy& s)
	{
		out << s.toyName;
		out << s.ageLimit;
		return out;
	}
	friend istream& operator >> (istream& in, Toy& s)
	{
		cout << "������ ���������� ��� ���������:";
		in >> s.producerName;
		cout << "������ ���������� ��� ����:";
		in >> s.price;
		cout << "������ ��� ����� ��� ��������:";
		in >> s.countryCode; 
		cout << "������ ����� �������:";
		in >> s.toyName;
		cout << "������ ����� ��������� ��� �������:";
		in >> s.ageLimit; 
		return in;
	}
	unsigned int getAgeLimit()
	{
		return this->ageLimit;
	}
	string getToyName()
	{
		return this->toyName; 
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
     int size = 0;
	cout << "������ ������� �������:";
	cin >> size;
	Toy* array = new Toy[size];
	cout << "������ ���������� ���������� ��� �������" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> array[i];
		system("cls");
	}
		unsigned int age = 0;
		cout << "������ ��� ��:";
		cin >> age;
		cout << "���������� ��� ����� = 0" << endl; 
		cout << "���������� ������ ������� ��� ������ ��� = 1" << endl; 
		int choice = 0; 
		cin >> choice;
		
		if (choice == 0)
		{
			int index;
			cout << "������ ����� ������� :";
			cin >> index;
			cout << "��� ����� ��� ������� ";
		    cout << array[index].getToyName();
		    cout << " :"; 
		    cout << array[index].getCountryCode();
		}
		else if (choice == 1)
		{
			cout << "��� ���� ������ �������������� ������� ��� ���:" << endl;
			for (int i = 0; i < size; i++)
			{
				if (array[i].getAgeLimit() < age)
				{
					cout << array[i];
				}
				else
				{
					continue;
				}
			}
		}

	return 0;
}
		