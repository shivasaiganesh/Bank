#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password123"

// Base class representing a generic account
class Account {
public:
    int accountNumber;
    string name;
    string aadhar;
    string dob;
    string accountType;
    string address;
    string pan;
    float balance;
    string password;
    string pin;

    Account() : balance(0.0) {}

    // Virtual method for displaying account information 
    virtual void displayAccount() const {
        cout << "Account Number: " << accountNumber << "\n"
             << "Name: " << name << "\n"
             << "Aadhar: " << aadhar << "\n"
             << "DOB: " << dob << "\n"
             << "Account Type: " << accountType << "\n"
             << "Address: " << address << "\n"
             << "PAN: " << pan << "\n"
             << "Balance: " << balance << "\n";
    }

    // Virtual destructor
    virtual ~Account() {}
};

// Derived class for SavingsAccount
class SavingsAccount : public Account {
public:
    SavingsAccount() {
        accountType = "Savings";
    }

    void displayAccount() const override {
        cout << "Savings Account - ";
        Account::displayAccount();  // Call base class method
    }
};

// Derived class for CurrentAccount
class CurrentAccount : public Account {
public:
    CurrentAccount() {
        accountType = "Current";
    }

    void displayAccount() const override {
        cout << "Current Account - ";
        Account::displayAccount();  // Call base class method
    }
};

class BankSystem {
private:
    vector<Account*> accounts;

public:
    BankSystem() {}

    // Admin login function
    bool adminLogin() {
        string username, password;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;

        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
            cout << "Admin logged in successfully!\n";
            return true;
        } else {
            cout << "Invalid credentials. Access denied.\n";
            return false;
        }
    }

    // Create new account
    void createAccount() {
        int choice;
        cout << "Enter account type (1 for Savings, 2 for Current): ";
        cin >> choice;

        Account* newAccount = nullptr;
        if (choice == 1) {
            newAccount = new SavingsAccount();
        } else if (choice == 2) {
            newAccount = new CurrentAccount();
        }

        if (newAccount != nullptr) {
            cout << "Enter account number: ";
            cin >> newAccount->accountNumber;
            cout << "Enter name: ";
            cin.ignore();  // To clear the buffer before using getline
            getline(cin, newAccount->name);
            cout << "Enter Aadhar number (12 digits): ";
            cin >> newAccount->aadhar;
            cout << "Enter Date of Birth (DD/MM/YYYY): ";
            cin >> newAccount->dob;
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, newAccount->address);
            cout << "Enter PAN number (10 characters): ";
            cin >> newAccount->pan;
            cout << "Enter password: ";
            cin >> newAccount->password;
            cout << "Enter PIN (4 digits): ";
            cin >> newAccount->pin;
            cout << "Enter initial balance: ";
            cin >> newAccount->balance;

            accounts.push_back(newAccount);
            cout << "Account created successfully!\n";
        }
    }

    // View all accounts
    void viewAccounts() {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        cout << "List of Accounts:\n";
        for (auto& account : accounts) {
            account->displayAccount();  // Polymorphic call
            cout << "-----------------------------\n";
        }
    }

    // Search for an account by account number using binary search
    void searchAccount() {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        // Sort accounts by account number before binary search
        sort(accounts.begin(), accounts.end(),
            [](Account* a, Account* b) { return a->accountNumber < b->accountNumber; });

        int accountNumber;
        cout << "Enter the account number to search: ";
        cin >> accountNumber;

        auto it = lower_bound(accounts.begin(), accounts.end(), accountNumber,
            [](Account* account, int accountNumber) { return account->accountNumber < accountNumber; });

        if (it != accounts.end() && (*it)->accountNumber == accountNumber) {
            cout << "Account Found:\n";
            (*it)->displayAccount();
        } else {
            cout << "Account not found.\n";
        }
    }

    // Delete an account by account number
    void deleteAccount() {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        int accountNumber;
        cout << "Enter the account number to delete: ";
        cin >> accountNumber;

        auto it = find_if(accounts.begin(), accounts.end(),
                          [accountNumber](Account* account) {
                              return account->accountNumber == accountNumber;
                          });

        if (it != accounts.end()) {
            delete *it;  // Free the allocated memory for the account
            accounts.erase(it);  // Remove the account from the vector
            cout << "Account deleted successfully.\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    // Destructor to free memory
    ~BankSystem() {
        for (auto& account : accounts) {
            delete account;  // Cleanup all dynamically allocated accounts
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    // Perform admin login
    if (!bank.adminLogin()) {
        return 0; // Exit if login failed
    }

    do {
        cout << "\nBank Account Management System\n";
        cout << "1. Create Account\n";
        cout << "2. View All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Delete Account\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.viewAccounts();
                break;
            case 3:
                bank.searchAccount();
                break;
            case 4:
                bank.deleteAccount();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
