#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
protected:
    string country_code;
    double price;
public:
    Product(string code, double price) : country_code(code), price(price) {}
    virtual ~Product() {}
    string get_country_code() const { return country_code; }
    double get_price() const { return price; }
};

class Toy : public Product {
private:
    string name;
    int min_age;
    int max_age;
public:
    Toy(string code, double price, string name, int min_age, int max_age) :
        Product(code, price), name(name), min_age(min_age), max_age(max_age) {}
    ~Toy() {}
    string get_name() const { return name; }
    int get_min_age() const { return min_age; }
    int get_max_age() const { return max_age; }
};

void print_toy(const Toy& toy) {
    cout << "Name: " << toy.get_name() << endl;
    cout << "Price: " << toy.get_price() << endl;
    cout << "Country code: " << toy.get_country_code() << endl;
    cout << "Minimum age: " << toy.get_min_age() << endl;
    cout << "Maximum age: " << toy.get_max_age() << endl << endl;
}

int main() {
    vector<Toy> toys;
    toys.push_back(Toy("US", 15.99, "Teddy bear", 0, 6));
    toys.push_back(Toy("CN", 10.99, "Lego", 4, 12));
    toys.push_back(Toy("JP", 29.99, "Tamagotchi", 6, 12));
    toys.push_back(Toy("DE", 19.99, "Playmobil", 4, 10));
    toys.push_back(Toy("FR", 8.99, "Yo-yo", 8, 15));

    int min_age, max_age;
    double min_price, max_price;
    cout << "Enter the minimum age: ";
    cin >> min_age;
    cout << "Enter the maximum age: ";
    cin >> max_age;
    cout << "Enter the minimum price: ";
    cin >> min_price;
    cout << "Enter the maximum price: ";
    cin >> max_price;

    cout << endl << "Recommended toys:" << endl;
    for (const auto& toy : toys) {
        if (toy.get_min_age() <= max_age && toy.get_max_age() >= min_age &&
            toy.get_price() >= min_price && toy.get_price() <= max_price) {
            print_toy(toy);
        }
    }

    cout << "Would you like to see the country codes of the recommended toys? (y/n): ";
    char answer;
    cin >> answer;
    if (answer == 'y') {
        cout << endl << "Country codes of the recommended toys:" << endl;
        for (const auto& toy : toys) {
            if (toy.get_min_age() <= max_age && toy.get_max_age() >= min_age &&
                toy.get_price() >= min_price && toy.get_price() <= max_price) {
                cout << toy.get_country_code() << endl;
            }
        }
    }

    return 0;
}
