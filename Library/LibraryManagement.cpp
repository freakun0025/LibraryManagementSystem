#include<bits/stdc++.h>
using namespace std;

// Forward declarations
class Book;
class Account;

class User {
protected:
    string userId, name, contact;
public:
    User(string uid, string n, string c) : userId(uid), name(n), contact(c) {}
    void displayDetails() {
        cout << "UserID: " << userId << ", Name: " << name << ", Contact: " << contact << endl;
    }
    void login() { cout << name << " logged in.\n"; }
    void logout() { cout << name << " logged out.\n"; }
};

class Book {
    string bookId, title, author;
    bool isAvailable;
public:
    Book(string id, string t, string a) : bookId(id), title(t), author(a), isAvailable(true) {}
    string getBookId() { return bookId; }
    string getTitle() { return title; }
    bool getIsAvailable() { return isAvailable; }
    void checkStatus() { cout << title << " is " << (isAvailable ? "Available" : "Borrowed") << endl; }
    void updateStatus(string status) { isAvailable = (status == "Available"); }
};

class Account {
    string accountNumber;
    double balance;
public:
    Account(string acc, double bal) : accountNumber(acc), balance(bal) {}
    void payFines(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Paid fine: " << amount << ", Remaining: " << balance << endl;
        } else cout << "Insufficient balance.\n";
    }
    double getBalance() { return balance; }
};

class Member : public User {
    string memberId, membershipExpiryDate;
    Account* account;
    vector<Book*> borrowedBooks;
public:
    Member(string uid, string n, string c, string mid, string exp, Account* acc)
        : User(uid, n, c), memberId(mid), membershipExpiryDate(exp), account(acc) {}
    void borrowBook(Book* book) {
        if (book && book->getIsAvailable()) {
            book->updateStatus("Borrowed");
            borrowedBooks.push_back(book);
            cout << name << " borrowed " << book->getTitle() << endl;
        } else cout << "Cannot borrow " << (book ? book->getTitle() : "Unknown") << endl;
    }
    void returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book) {
                book->updateStatus("Available");
                borrowedBooks.erase(it);
                cout << name << " returned " << book->getTitle() << endl;
                return;
            }
        }
        cout << name << " did not borrow " << (book ? book->getTitle() : "Unknown") << endl;
    }
    void viewBorrowedHistory() {
        cout << name << "'s borrowed books:\n";
        for (auto b : borrowedBooks) cout << "  " << b->getTitle() << endl;
        if (borrowedBooks.empty()) cout << "  None\n";
    }
    Account* getAccount() { return account; }
};

class Librarian : public User {
    string employeeId, shift;
    vector<Member*> managedMembers;
public:
    Librarian(string uid, string n, string c, string eid, string s)
        : User(uid, n, c), employeeId(eid), shift(s) {}
    void addBook(Book* book) { cout << name << " added " << (book ? book->getTitle() : "Unknown") << endl; }
    void removeBook(Book* book) { cout << name << " removed " << (book ? book->getTitle() : "Unknown") << endl; }
    void manageOverdueItems() { cout << name << " is managing overdue items.\n"; }
    void addMemberToManage(Member* m) { managedMembers.push_back(m); }
};

class Shelf {
    string shelfId, category;
    vector<Book*> books;
public:
    Shelf(string id, string cat) : shelfId(id), category(cat) {}
    void organizeBooks() { cout << "Organizing shelf " << shelfId << " (" << category << ")\n"; }
    void addBook(Book* book) { books.push_back(book); }
};

class Library {
    string libraryName, address;
    vector<Book> books;
    vector<Shelf*> shelves;
public:
    Library(string n, string a) : libraryName(n), address(a) {}
    void open() { cout << libraryName << " is open.\n"; }
    void close() { cout << libraryName << " is closed.\n"; }
    void addShelf(Shelf* shelf) { shelves.push_back(shelf); }
    void addBook(const Book& book) { books.push_back(book); }
    Book* findBook(string id) {
        for (auto& b : books) if (b.getBookId() == id) return &b;
        return nullptr;
    }
};

int main() {
    Library lib("City Library", "MG Road");
    lib.open();

    Shelf shelf1("S1", "Fiction"), shelf2("S2", "Fantasy");
    lib.addShelf(&shelf1); lib.addShelf(&shelf2);

    // Add Indian and other books
    Book b1("B1", "Dune", "Frank Herbert");
    Book b2("B2", "Dragon Rider", "Cornelia Funke");
    Book b3("B3", "The Hobbit", "J.R.R. Tolkien");
    Book b4("B4", "Godaan", "Munshi Premchand");
    Book b5("B5", "Malgudi Days", "R.K. Narayan");
    Book b6("B6", "Train to Pakistan", "Khushwant Singh");
    Book b7("B7", "The Guide", "R.K. Narayan");
    Book b8("B8", "The White Tiger", "Aravind Adiga");

    lib.addBook(b1); lib.addBook(b2); lib.addBook(b3);
    lib.addBook(b4); lib.addBook(b5); lib.addBook(b6);
    lib.addBook(b7); lib.addBook(b8);

    shelf1.addBook(lib.findBook("B1"));
    shelf1.addBook(lib.findBook("B4"));
    shelf1.addBook(lib.findBook("B5"));
    shelf2.addBook(lib.findBook("B2"));
    shelf2.addBook(lib.findBook("B3"));
    shelf2.addBook(lib.findBook("B6"));
    shelf2.organizeBooks();

    Librarian libn("L1", "Priya", "priya@lib.com", "E1", "Morning");
    libn.login();

    Account acc1("A1", 100), acc2("A2", 50);
    Member m1("U1", "Kunal", "Kunal@mail.com", "M1", "2025-12-31", &acc1);
    Member m2("U2", "Sneha", "sneha@mail.com", "M2", "2026-01-15", &acc2);

    libn.addMemberToManage(&m1);
    libn.addMemberToManage(&m2);

    m1.borrowBook(lib.findBook("B1"));
    m1.borrowBook(lib.findBook("B4"));
    m2.borrowBook(lib.findBook("B2"));
    m2.borrowBook(lib.findBook("B3"));

    m1.viewBorrowedHistory();
    m2.viewBorrowedHistory();

    m1.getAccount()->payFines(20);
    m2.getAccount()->payFines(60);

    libn.addBook(lib.findBook("B7"));
    libn.removeBook(lib.findBook("B8"));
    libn.manageOverdueItems();

    m1.returnBook(lib.findBook("B1"));
    m1.viewBorrowedHistory();

    libn.logout();
    lib.close();
    return 0;
}

// Kunal Mittal (IMT2023533)