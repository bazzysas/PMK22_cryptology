#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>

void print_log_table() {
    std::cout << std::setw(10) << "Number" << std::setw(10) << "Logarithm" << std::endl;
    std::cout << std::setw(23) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

    for (int i = 2; i <= 100; ++i) {
        double naturalLog = std::log(i);
        double decimalLog = std::log10(i);
        std::cout << std::setw(10) << i << std::setw(10) << std::fixed << std::setprecision(5)
            << decimalLog << std::endl;
    }
}

void printCentered(const std::string& text) {
    int screenWidth = 80;
    int textWidth = text.length();
    int padding = (screenWidth - textWidth) / 2;

    std::cout << std::setw(padding + textWidth) << text << std::endl;
}

std::ostream& systemTime(std::ostream& os) {
    std::time_t currentTime;
    std::time(&currentTime);
    char dateTimeString[26];
    ctime_s(dateTimeString, sizeof(dateTimeString), &currentTime);
    dateTimeString[strlen(dateTimeString) - 1] = '\0';
    os << dateTimeString;
    return os;
}

std::istream& skipCharacters(std::istream& is) {
    char dummy[11];
    is.read(dummy, 10);

    return is;
}

int main() {
    // �������� 1: ���� ������� ������������ �� ����������� ��������� �����
    std::cout << "������� ������������ �� ����������� ��������� ����� �� 2 �� 100:\n";
    print_log_table();
    std::cout << std::endl;

    // �������� 2: ��������� ����� � ����� ������
    std::cout << "������ �����: ";
    std::string userInput;
    std::getline(std::cin, userInput);
    std::cout << "����� � ����� ������:\n";
    printCentered(userInput);
    std::cout << std::endl;

    // �������� 3: ��������� ���������� ���� �� ����
    std::cout << "������� ���� �� ���: ";
    std::cout << systemTime << std::endl;
    std::cout << std::endl;

    // �������� 4: ���������� �� ������� 10 �������
    std::cout << "������ �����: ";
    std::cin >> skipCharacters;
    std::cout << "��������� 10 �������." << std::endl;

    return 0;
}
