#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Telefon {
protected:
    string nazva;
    string firma;
    double tsina;
public:
    Telefon(const string& nazva, const string& firma, double tsina) : nazva(nazva), firma(firma), tsina(tsina) {}

    virtual void print() const = 0;

    double getTsina() const {
        return tsina;
    }
};

class MobilnyiTelefon : public Telefon {
private:
    string kolor;
    int obiemPamjati;
public:
    MobilnyiTelefon(const string & nazva, const string & firma, double tsina, const string & kolor, int obiemPamjati)
        : Telefon(nazva, firma, tsina), kolor(kolor), obiemPamjati(obiemPamjati) {}

    void print() const override {
        cout << "�������� �������: " << nazva << ", Գ���: " << firma << ", ֳ��: " << tsina
            << ", ����: " << kolor << ", ��'�� ���'��: " << obiemPamjati << endl;
    }
};

class Radiotelefon : public Telefon {
private:
    double radiusDii;
    bool avtovidpovidach;
public:
    Radiotelefon(const string& nazva, const string& firma, double tsina, double radiusDii, bool avtovidpovidach)
        : Telefon(nazva, firma, tsina), radiusDii(radiusDii), avtovidpovidach(avtovidpovidach) {}

    void print() const override {
        cout << "�����������: " << nazva << ", Գ���: " << firma << ", ֳ��: " << tsina
            << ", ����� 䳿: " << radiusDii << ", �������� �������������: " << (avtovidpovidach ? "���" : "ͳ") << endl;
    }

    bool hasAvtovidpovidach() const {
        return avtovidpovidach;
    }
};

bool sortByTsina(const Telefon* t1, const Telefon* t2) {
    return t1->getTsina() < t2->getTsina();
}

int main() {
    vector<Telefon*> telefoni;

    ifstream file1("file1.txt");
    ifstream file2("file2.txt");

    string nazva, firma, kolor;
    double tsina, radiusDii;
    int obiemPamjati;
        bool avtovidpovidach;

    // ���������� ����� � ������� �����
    while (file1 >> nazva >> firma >> tsina >> kolor >> obiemPamjati) {
        telefoni.push_back(new MobilnyiTelefon(nazva, firma, tsina, kolor, obiemPamjati));
}

// ���������� ����� � ������� �����
while (file2 >> nazva >> firma >> tsina >> radiusDii >> avtovidpovidach) {
    telefoni.push_back(new Radiotelefon(nazva, firma, tsina, radiusDii, avtovidpovidach));
}

file1.close();
file2.close();

// ���������� �������� �� �����
sort(telefoni.begin(), telefoni.end(), sortByTsina);

// ��������� �������� � ����
ofstream output("output.txt");

double totalSum = 0.0;

for (const Telefon* telefon : telefoni) {
    telefon->print();
    totalSum += telefon->getTsina();
}

output << "�������� ����: " << totalSum << endl;
output.close();

// ��������� ������������ � �������������� � ������� ����
ofstream radiotelefonOutput("radiotelefon_output.txt");

for (const Telefon* telefon : telefoni) {
    const Radiotelefon* radiotelefon = dynamic_cast<const Radiotelefon*>(telefon);
    if (radiotelefon && radiotelefon->hasAvtovidpovidach()) {
        radiotelefon->print();
    }
}

radiotelefonOutput.close();

// ������� ���'��
for (Telefon* telefon : telefoni) {
    delete telefon;
}

return 0;
}
