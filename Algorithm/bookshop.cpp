#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

struct Book {
    string title;
    string author;
    double price;
};

struct Bookstore {
    string name;
    vector<Book> books;
};

// ������� ��� ������ �������� �� ������
Bookstore* findBookstoreByName(const vector<Bookstore>& bookstores, const string& name) {
    for (const auto& bookstore : bookstores) {
        if (bookstore.name == name) {
            return const_cast<Bookstore*>(&bookstore);
        }
    }
    return nullptr;
}



// ������� ��� ���������� �������� ������� ������ ��� ���������� ��������
double calculateTotalPrice(const Bookstore* bookstore) {
    double totalPrice = 0.0;
    for (const auto& book : bookstore->books) {
        totalPrice += book.price;
    }
    return totalPrice;
}

// ������� ��� ����������� ������ �������� ������ �� ������ ���������� � ����
void findBooksByAuthor(const vector<Bookstore>& bookstores, const string& author, const string& outputFile) {
    ofstream file(outputFile, ios::app);
    if (!file.is_open()) {
        cout << "Failed to open the file: " << outputFile << endl;
        return;
    }

    for (const auto& bookstore : bookstores) {
        for (const auto& book : bookstore.books) {
            if (book.author == author) {
                file << "Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }

    file.close();
    cout << "Books by author '" << author << "' have been written to the file: " << outputFile << endl;
}

// ������� ��� ���������� ������� ������ �������� ������, ���� ���� ����������� � �������� �������
int countBooksByAuthorInRange(const vector<Bookstore>& bookstores, const string& author, double minPrice, double maxPrice) {
    int count = 0;
    for (const auto& bookstore : bookstores) {
        for (const auto& book : bookstore.books) {
            if (book.author == author && book.price >= minPrice && book.price <= maxPrice) {
                count++;
            }
        }
    }
    return count;
}

// ������� ��� ����������� ��������, ������� ������ ����� ����� �� ������ �����
vector<Bookstore*> findBookstoresWithMoreBooks(const vector<Bookstore>& bookstores, int bookCount) {
    vector<Bookstore*> result;
    for (const auto& bookstore : bookstores) {
        if (bookstore.books.size() > bookCount) {
            Bookstore* bookstorePtr = new Bookstore(bookstore);  // ��������� ��ﳿ Bookstore
            result.push_back(bookstorePtr);
        }
    }
    return result;
}

// ������� ��� ��������, �� ���� ���� ������ ������ ��� �������� ��������, ����� �� ���� ����� ����� � ���� ����� �� �����
bool hasNeighborBooksDoublePrice(const Bookstore* bookstore) {
    for (size_t i = 0; i < bookstore->books.size() - 1; i++) {
        const Book& currentBook = bookstore->books[i];
        const Book& nextBook = bookstore->books[i + 1];
        if (nextBook.price == 2 * currentBook.price) {
            return true;
        }
    }
    return false;
}

// ��������, �� ���� � ������� ������� ���� ���� ����� �� � ������� ��� � ������ �����
bool hasBooksWithLowerPrice(const Bookstore* firstStore, const Bookstore* secondStore) {
    for (const auto& book1 : firstStore->books) {
        for (const auto& book2 : secondStore->books) {
            if (book1.title == book2.title && book1.author == book2.author && book1.price < book2.price) {
                return true;
            }
        }
    }
    return false;
}


// ������� ��� ����������� ����� ���� ������ ��� ���� ������� ��������, ����� �� ���� ����� � ���� ����� �� �����
pair<Book, Book> findFirstBookPairWithDoublePrice(const Bookstore* firstStore, const Bookstore* secondStore) {
    for (const auto& book1 : firstStore->books) {
        for (const auto& book2 : secondStore->books) {
            if (book2.price == 2 * book1.price) {
                return make_pair(book1, book2);
            }
        }
    }
    return make_pair(Book{}, Book{});  // ��������� ������ ������, ���� ���� �� ��������
}

// ������� ��� ��������, �� ����� ��� ����� � ������ ������ �������� �������� ��������� ������������� � ������ ������ ������� ��������
bool isFirstThreeBooksSubsequence(const Bookstore* firstStore, const Bookstore* secondStore) {
    vector<Book> firstThreeBooks(firstStore->books.begin(), firstStore->books.begin() + 3);
    vector<Book> allBooks = secondStore->books;

    vector<Book>::iterator it = search(allBooks.begin(), allBooks.end(), firstThreeBooks.begin(), firstThreeBooks.end(),
        [](const Book& book1, const Book& book2) {
            return book1.title == book2.title && book1.author == book2.author && book1.price == book2.price;
        });

    return it != allBooks.end();
}

int main() {
    vector<Bookstore> bookstores;

    // ������������ ����� � ���������� �����
    ifstream inputFile("bookstores.txt");

    if (!inputFile.is_open()) {
        cout << "Failed to open the file: bookstores.txt" << endl;
        return 0;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Bookstore bookstore;
        getline(iss, bookstore.name, ';');

        string bookInfo;
        while (getline(iss, bookInfo, ',')) {
            istringstream bookIss(bookInfo);
            Book book;
            getline(bookIss, book.title, ':');
            getline(bookIss, book.author, ':');
            bookIss >> book.price;
            bookstore.books.push_back(book);
        }

        bookstores.push_back(bookstore);
    }

    inputFile.close();

    // ����� �������� �� ������
    string bookstoreName = "Bookstore A";
    Bookstore* foundBookstore = findBookstoreByName(bookstores, bookstoreName);
    if (foundBookstore != nullptr) {
        cout << "Bookstore found: " << foundBookstore->name << endl;

        // ���������� �������� ������� ������ ��� ���������� ��������
        double totalPrice = calculateTotalPrice(foundBookstore);
        cout << "Total price of books in " << foundBookstore->name << ": " << totalPrice << endl;

        // ������ ������ �������� ������ �� �������� ��������� � ����
        string authorName = "John Doe";
        string outputFile = "bookstores.txt";
        findBooksByAuthor(bookstores, authorName, outputFile);

        // ���������� ������� ������ �������� ������, ���� ���� ����������� � �������� �������
        double minPrice = 10.0;
        double maxPrice = 50.0;
        int bookCount = countBooksByAuthorInRange(bookstores, authorName, minPrice, maxPrice);
        cout << "Number of books by author '" << authorName << "' in the price range $" << minPrice << " - $" << maxPrice << ": " << bookCount << endl;

        // ����������� ��������, ������� ������ ����� ����� �� ������ �����
        int requiredBookCount = 5;
        vector<Bookstore*> bookstoresWithMoreBooks = findBookstoresWithMoreBooks(bookstores, requiredBookCount);
        cout << "Bookstores with more than " << requiredBookCount << " books:" << endl;
        for (const auto& bookstore : bookstoresWithMoreBooks) {
            cout << "- " << bookstore->name << endl;
        }

        // ��������, �� ���� ���� ������ ������ ��� �������� ��������, ����� �� ���� ����� ����� � ���� ����� �� �����
        bool hasNeighborBooksDoublePriceExist = hasNeighborBooksDoublePrice(foundBookstore);
        cout << "Neighbor books with double price exist in " << foundBookstore->name << ": " << (hasNeighborBooksDoublePriceExist ? "Yes" : "No") << endl;

        // ��������, �� ���� � ������� ������� ���� ���� ����� �� � ������� ��� � ������ �����
        Bookstore* firstStore = &bookstores[0];
        Bookstore* secondStore = &bookstores[1];
        bool hasBooksWithLowerPriceExist = hasBooksWithLowerPrice(firstStore, secondStore);
        cout << "Book with lower price exists in the first store compared to the second store: " << (hasBooksWithLowerPriceExist ? "Yes" : "No") << endl;

        // ����������� ����� ���� ������ ��� ���� ������� ��������, ����� �� ���� ����� � ���� ����� �� �����
        pair<Book, Book> bookPair = findFirstBookPairWithDoublePrice(firstStore, secondStore);
        if (bookPair.first.title != "" && bookPair.second.title != "") {
            cout << "First book pair with double price: " << endl;
            cout << "- Book 1: " << bookPair.first.title << ", Author: " << bookPair.first.author << ", Price: " << bookPair.first.price << endl;
            cout << "- Book 2: " << bookPair.second.title << ", Author: " << bookPair.second.author << ", Price: " << bookPair.second.price << endl;
        } else {
            cout << "No book pair with double price found." << endl;
        }

        // ��������, �� ����� ��� ����� � ������ ������ �������� �������� ��������� ������������� � ������ ������ ������� ��������
        bool isSubsequence = isFirstThreeBooksSubsequence(firstStore, secondStore);
        cout << "First three books from the first store form a subsequence in the second store: " << (isSubsequence ? "Yes" : "No") << endl;
    } else {
        cout << "Bookstore not found: " << bookstoreName << endl;
    }

    return 0;
}
