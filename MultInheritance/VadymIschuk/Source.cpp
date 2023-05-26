#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ����������� ���� Գ����
class Figure {
public:
    virtual double getArea() const = 0;
    virtual void print() const = 0;
};

// ����������� ���� ������ Գ����, �������� �� Գ����
class FlatFigure : public Figure {
public:
    void print() const override {
        cout << "Flat Figure" << endl;
    }
};

// ����������� ���� ��'���� Գ����, �������� �� Գ����
class SolidFigure : public Figure {
public:
    virtual double getHeight() const = 0;
    void print() const override {
        cout << "Solid Figure" << endl;
    }
};

// ���� ������������, �������� �� ������ Գ����
class Polygon : public FlatFigure {
private:
    double area;
public:
    Polygon(double area) : area(area) {}

    double getArea() const override {
        return area;
    }

    void print() const override {
        cout << "Polygon: Area = " << area << endl;
    }
};

// ���� ����, �������� �� ������ Գ����
class Circle : public FlatFigure {
private:
    double area;
public:
    Circle(double area) : area(area) {}

    double getArea() const override {
        return area;
    }

    void print() const override {
        cout << "Circle: Area = " << area << endl;
    }
};

// ���� ������������, �������� �� ��'���� Գ����
class Parallelepiped : public SolidFigure {
private:
    double height;
public:
    Parallelepiped(double height) : height(height) {}

    double getArea() const override {
        return 0.0; // ����� �� ��������������� ��� ���������� ��'����� �����
    }

    double getHeight() const override {
        return height;
    }

    void print() const override {
        cout << "Parallelepiped: Height = " << height << endl;
    }
};

// ���� �����, �������� �� ��'���� Գ����
class Cone : public SolidFigure {
private:
    double height;
public:
    Cone(double height) : height(height) {}

    double getArea() const override {
        return 0.0; // ����� �� ��������������� ��� ���������� ��'����� �����
    }

    double getHeight() const override {
        return height;
    }

    void print() const override {
        cout << "Cone: Height = " << height << endl;
    }
};

int main() {
    vector<Figure*> figures;

    // �������� ����� ��� 10 ������������ �����
    figures.push_back(new Circle(10.0));
    figures.push_back(new Polygon(5.0));
    figures.push_back(new Circle(7.5));
    figures.push_back(new Parallelepiped(3.0));
    figures.push_back(new Cone(6.0));
    figures.push_back(new Parallelepiped(2.5));
    figures.push_back(new Circle(12.0));
    figures.push_back(new Cone(4.5));
    figures.push_back(new Polygon(8.0));
    figures.push_back(new Parallelepiped(1.5));

    // ���������� ������� ����� �� ��������� ����
    sort(figures.begin(), figures.end(), [](Figure* a, Figure* b) {
        return a->getArea() > b->getArea();
        });

    cout << "Flat Figures (sorted by area in descending order):" << endl;
    for (Figure* figure : figures) {
        if (dynamic_cast<FlatFigure*>(figure)) {
            figure->print();
        }
    }

    // ���������� ��'����� ����� �� ���������� ������
    sort(figures.begin(), figures.end(), [](Figure* a, Figure* b) {
        if (dynamic_cast<SolidFigure*>(a) && dynamic_cast<SolidFigure*>(b)) {
            return dynamic_cast<SolidFigure*>(a)->getHeight() < dynamic_cast<SolidFigure*>(b)->getHeight();
        }
        return false;
        });

    cout << "Solid Figures (sorted by height in ascending order):" << endl;
    for (Figure* figure : figures) {
        if (dynamic_cast<SolidFigure*>(figure)) {
            figure->print();
        }
    }

    // ������ ������, ���� � ������������ ������ ��� ������� � �������� ���������
    double searchValue = 12.0;
    for (Figure* figure : figures) {
        if (dynamic_cast<Polygon*>(figure) && dynamic_cast<Polygon*>(figure)->getArea() == searchValue) {
            cout << "Found a polygon with area equal to " << searchValue << endl;
            figure->print();
            break;
        }
        if (dynamic_cast<Circle*>(figure) && dynamic_cast<Circle*>(figure)->getArea() == searchValue) {
            cout << "Found a circle with area equal to " << searchValue << endl;
            figure->print();
            break;
        }
        if (dynamic_cast<Parallelepiped*>(figure) && dynamic_cast<Parallelepiped*>(figure)->getHeight() == searchValue) {
            cout << "Found a parallelepiped with height equal to " << searchValue << endl;
            figure->print();
            break;
        }
        if (dynamic_cast<Cone*>(figure) && dynamic_cast<Cone*>(figure)->getHeight() == searchValue) {
            cout << "Found a cone with height equal to " << searchValue << endl;
            figure->print();
            break;
        }
    }

    // ��������� ������� ���'��
    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}
