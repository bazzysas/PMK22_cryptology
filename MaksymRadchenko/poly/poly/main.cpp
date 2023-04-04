#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Phone {
protected:
    string name;
    string brand;
    double price;
public:
    Phone(string n, string b, double p) : name(n), brand(b), price(p) {}
    virtual void print() = 0;
    double getPrice() const { return price; }
};

class MobilePhone : public Phone {
private:
    string color;
    int memory;
public:
    MobilePhone(string n, string b, double p, string c, int m) : Phone(n, b, p), color(c), memory(m) {}
    void print() override {
        cout << name << " (" << brand << ", " << color << ", " << memory << "GB, " << price << ")" << endl;
    }
};

class RadioPhone : public Phone {
private:
    int range;
    bool hasAnsweringMachine;
public:
    RadioPhone(string n, string b, double p, int r, bool a) : Phone(n, b, p), range(r), hasAnsweringMachine(a) {}
    void print() override {
        cout << name << " (" << brand << ", " << range << "km, " << (hasAnsweringMachine ? "yes" : "no") << ", " << price << ")" << endl;
    }
    bool hasAM() const { return hasAnsweringMachine; }
};

int main() {
    vector<Phone*> phones;

    ifstream file1("phones1.txt");
    string name, brand, color;
    int memory, range;
    double price;
    while (file1 >> name >> brand >> price >> color >> memory) {
        phones.push_back(new MobilePhone(name, brand, price, color, memory));
    }
    file1.close();

    ifstream file2("phones2.txt");
    bool hasAM;
    while (file2 >> name >> brand >> price >> range >> hasAM) {
        phones.push_back(new RadioPhone(name, brand, price, range, hasAM));
    }
    file2.close();

    sort(phones.begin(), phones.end(), [](const Phone* a, const Phone* b) { return a->getPrice() < b->getPrice(); });
    double totalPrice = 0;
    ofstream out1("phones_sort.txt");
    for (Phone* p : phones) {
        p->print();
        totalPrice += p->getPrice();
        out1 << p->getPrice() << endl;
    }
    out1 << "Total: " << totalPrice << endl;
    out1.close();

    ofstream out2("phones2.txt");
    for (Phone* p : phones) {
        RadioPhone* r = dynamic_cast<RadioPhone*>(p);
        if (r && r->hasAM()) {
            r->print();
            out2 << r->getPrice() << endl;
        }
    }
    out2.close();

    for (Phone* p : phones) {
        delete p;
    }
    return 0;
}
