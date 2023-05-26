#include <iostream>
#include <vector>
using namespace std;

// ������� ���� ��� ����� ���������� ��� �����
class Product {
protected:
    string countryOfOrigin;
    double price;
public:
    Product(const string& country, double price)
        : countryOfOrigin(country), price(price) {}

    void displayCountry() const {
        cout << "��� �����-���������: " << countryOfOrigin << endl;
    }

    double getPrice() const {
        return price;
    }
};

// ���� "�������", �� ��������� ������� ���� "�����"
class Toy : public Product {
private:
    string name;
    int minAge;
    int maxAge;
public:
    Toy(const string& country, double price, const string& toyName, int min, int max)
        : Product(country, price), name(toyName), minAge(min), maxAge(max) {}

    void displayToyInfo() const {
        cout << "�������: " << name << endl;
        cout << "�������������� ������ �������: " << minAge << " - " << maxAge << " ����" << endl;
        displayCountry();
    }

    bool isInRange(int age) const {
        return (age >= minAge && age <= maxAge);
    }
};

int main() {
    // ��������� ������� �������
    vector<Toy> toys;
    toys.push_back(Toy("UA", 10.99, "�'��", 3, 8));
    toys.push_back(Toy("CN", 25.50, "�����������", 5, 12));
    toys.push_back(Toy("US", 17.75, "������", 4, 10));
    toys.push_back(Toy("PL", 8.99, "������", 2, 6));
    toys.push_back(Toy("UA", 12.99, "�������", 3, 7));

    // ����� ����������� ���� ������� �������� �� ������� ���
    int minAge, maxAge;
    double minPrice, maxPrice;
    cout << "������ ��������� ��: ";
    cin >> minAge;
    cout << "������ ������������ ��: ";
    cin >> maxAge;
    cout << "������ �������� ����: ";
    cin >> minPrice;
    cout << "������ ����������� ����: ";
    cin >> maxPrice;

    // ����� �� ��������� �������, �� ������������� ������ ������� �� ����� ���
    cout << "������������ �������: " << endl;
    for (const Toy& toy : toys) {
        if (toy.isInRange(minAge) && toy.isInRange(maxAge) && toy.getPrice() >= minPrice && toy.getPrice() <= maxPrice) {
            toy.displayToyInfo();
            cout << "---------------" << endl;
        }
    }

    return 0;
}
