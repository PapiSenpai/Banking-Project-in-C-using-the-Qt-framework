/* 
Explanation

BankAccount Class: Manages individual accounts with methods for depositing, withdrawing,
and displaying account details.
Bank Class: Manages multiple accounts and includes methods for creating accounts, depositing,
withdrawing, and displaying account details. It also handles file operations to save and load
account data.

This is a basic implementation to get you started. You can expand it by adding more features 
like user authentication, transaction history, and error handling.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class BankAccount {
public:
    int accountNumber;
    std::string accountHolderName;
    double balance;

    BankAccount(int accNum, std::string name, double bal) 
        : accountNumber(accNum), accountHolderName(name), balance(bal) {}

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient balance!" << std::endl;
        }
    }

    void display() {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolderName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
};

class Bank {
private:
    std::vector<BankAccount> accounts;

public:
    void createAccount(int accNum, std::string name, double initialDeposit) {
        BankAccount newAccount(accNum, name, initialDeposit);
        accounts.push_back(newAccount);
    }

    void deposit(int accNum, double amount) {
        for (auto &account : accounts) {
            if (account.accountNumber == accNum) {
                account.deposit(amount);
                return;
            }
        }
        std::cout << "Account not found!" << std::endl;
    }

    void withdraw(int accNum, double amount) {
        for (auto &account : accounts) {
            if (account.accountNumber == accNum) {
                account.withdraw(amount);
                return;
            }
        }
        std::cout << "Account not found!" << std::endl;
    }

    void displayAccount(int accNum) {
        for (auto &account : accounts) {
            if (account.accountNumber == accNum) {
                account.display();
                return;
            }
        }
        std::cout << "Account not found!" << std::endl;
    }

    void saveToFile() {
        std::ofstream outFile("accounts.txt");
        for (auto &account : accounts) {
            outFile << account.accountNumber << " " << account.accountHolderName << " " << account.balance << std::endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        std::ifstream inFile("accounts.txt");
        int accNum;
        std::string name;
        double balance;
        while (inFile >> accNum >> name >> balance) {
            createAccount(accNum, name, balance);
        }
        inFile.close();
    }
};

int main() {
    Bank bank;
    bank.createAccount(1, "Alice", 1000.0);
    bank.createAccount(2, "Bob", 500.0);

    bank.deposit(1, 200.0);
    bank.withdraw(2, 100.0);

    bank.displayAccount(1);
    bank.displayAccount(2);

    bank.saveToFile();
    bank.loadFromFile();

    return 0;
}
