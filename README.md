# 🏦 Bank Account Management System (C++)

A simple console-based Bank Account Management System implemented in C++. This program allows an administrator to manage customer accounts including creating, viewing, searching, and deleting savings or current accounts.

## 🚀 Features

- Admin login authentication
- Create new accounts (Savings / Current)
- View all existing accounts
- Search accounts by account number (binary search)
- Delete accounts by account number
- Object-oriented design using inheritance and polymorphism
- Dynamic memory management with proper cleanup

## 🛠️ Technologies Used

- C++ (OOP, STL)
- Console I/O

## 📂 File Structure



## 🔐 Admin Credentials

- **Username**: `admin`  
- **Password**: `password123`

> You can modify these credentials in the `#define` section of the source code.

## 🧑‍💻 How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/bank-management-cpp.git
   cd bank-management-cpp


Design Overview
Account (base class): Holds common attributes and virtual displayAccount() method.

SavingsAccount & CurrentAccount: Inherit from Account and override display behavior.

BankSystem: Manages all account-related operations and handles admin login.


 Important Notes
The account number is used as the unique identifier.

Account data is stored in memory and not persisted after the program exits.

For production-level systems, consider using file/database storage and enhanced security.


Developed by Shiva Sai Ganesh
