#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// ������� ���� "���������"
class Automobile {
protected:
    double engineVolume; // ��'�� �������
    string name; // �����
    string brand; // �����

public:
    Automobile(double volume, string carName, string carBrand) :
        engineVolume(volume), name(carName), brand(carBrand) {}

    virtual void print(ostream& out) const {
        out << "��������� ����� " << brand << ", ������ " << name << ", ��'�� ������� " << engineVolume << " �" << endl;
    }

    string getBrand() {
        return brand;
    }

    // ��� ���������� �� ��'���� �������
    bool operator<(const Automobile& other) const {
        return engineVolume < other.engineVolume;
    }

    // ��� ���������� �� ������
    bool operator==(const Automobile& other) const {
        return brand == other.brand;
    }
};

// �������� ���� "���������� ���������"
class GasolineAutomobile : virtual public Automobile {
protected:
    double fuelTankVolume; // ��'�� ����

public:
    GasolineAutomobile(double volume, string carName, string carBrand, double tankVolume) :
        Automobile(volume, carName, carBrand), fuelTankVolume(tankVolume) {}

    virtual void print(ostream& out) const {
        out << "���������� ��������� ����� " << brand << ", ������ " << name << ", ��'�� ������� " << engineVolume << " �, ��'�� ���� " << fuelTankVolume << " �" << endl;
    }
};

// �������� ���� "������������"
class ElectricAutomobile : virtual public Automobile {
protected:
    int maxRange; // ������������ ����� �� ������ �����
    int chargingTime; // ��� �������

public:
    ElectricAutomobile(double volume, string carName, string carBrand, int range, int time) :
        Automobile(volume, carName, carBrand), maxRange(range), chargingTime(time) {}

    virtual void print(ostream& out) const {
        out << "������������ ����� " << brand << ", ������ " << name << ", ��'�� ������� " << engineVolume << " �, ������������ ����� �� ������ ����� " << maxRange << " ��, ��� ������� " << chargingTime << " ���" << endl;
    }
};

// ���� "����������� ���������"
class HybridAutomobile : public GasolineAutomobile, public ElectricAutomobile {
public:
    HybridAutomobile(double volume, string carName, string carBrand, double tankVolume, int range, int time) :
        Automobile(volume, carName, carBrand), GasolineAutomobile(volume, carName, carBrand, tankVolume), ElectricAutomobile(volume, carName, carBrand, range, time) {}
    virtual void print(ostream& out) const {
        out << "����������� ��������� ����� " << brand << ", ������ " << name << ", ��'�� ������� " << engineVolume << " �, ��'�� ���� " << fuelTankVolume << " �, ������������ ����� �� ������ ����� " << maxRange << " ��, ��� ������� " << chargingTime << " ���" << endl;
    }
};
int main() {
    // ��������� ��'���� ����� ���� ���������
    Automobile a1(2.0, "Civic", "Honda");
    GasolineAutomobile a2(3.5, "Explorer", "Ford", 70.0);
    ElectricAutomobile a3(1.5, "Model S", "Tesla", 500, 8);
    HybridAutomobile a4(2.5, "Prius", "Toyota", 50.0, 400, 6);

    // ��������� ������ ���������
    const int NUM_AUTOMOBILES = 4;
    Automobile* automobiles[NUM_AUTOMOBILES] = { &a1, &a2, &a3, &a4 };

    // ³������� ����� ��� ��������� �����
    ofstream out("output.txt");

    if (out.is_open()) {
        // ��������� ����� ��� �������� � ����
        for (int i = 0; i < NUM_AUTOMOBILES; i++) {
            automobiles[i]->print(out);
        }

        out << endl;

        // ���������� �� ��'���� ������� �� ��������� ������������ ����� � ����
        sort(automobiles, automobiles + NUM_AUTOMOBILES);
        for (int i = 0; i < NUM_AUTOMOBILES; i++) {
            automobiles[i]->print(out);
        }

        out << endl;

        // ���������� �� ������ �� ��������� ������������ ����� � ����
        sort(automobiles, automobiles + NUM_AUTOMOBILES, [](const Automobile* a, const Automobile* b) {
            return a->getBrand() < b->getBrand();
            });

        for (int i = 0; i < NUM_AUTOMOBILES; i++) {
            automobiles[i]->print(out);
        }

        out << endl;

        // �������� �����
        out.close();
    }
    else {
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return 1;
    }

    return 0;
}
