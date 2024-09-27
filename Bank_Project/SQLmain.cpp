// Implementation of the Core Functions for the Banking System

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

class Bank {
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    Bank() {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "user", "password");
        con->setSchema("banking_system");
    }

    ~Bank() {
        delete con;
    }

    void createAccount(int accNum, std::string name, double initialDeposit) {
        sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO Accounts(accountNumber, accountHolderName, balance) VALUES (?, ?, ?)");
        pstmt->setInt(1, accNum);
        pstmt->setString(2, name);
        pstmt->setDouble(3, initialDeposit);
        pstmt->execute();
        delete pstmt;
    }

    void deposit(int accNum, double amount) {
        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Accounts SET balance = balance + ? WHERE accountNumber = ?");
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, accNum);
        pstmt->execute();
        delete pstmt;

        pstmt = con->prepareStatement("INSERT INTO Transactions(accountNumber, type, amount) VALUES (?, 'deposit', ?)");
        pstmt->setInt(1, accNum);
        pstmt->setDouble(2, amount);
        pstmt->execute();
        delete pstmt;
    }

    void withdraw(int accNum, double amount) {
        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Accounts SET balance = balance - ? WHERE accountNumber = ?");
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, accNum);
        pstmt->execute();
        delete pstmt;

        pstmt = con->prepareStatement("INSERT INTO Transactions(accountNumber, type, amount) VALUES (?, 'withdraw', ?)");
        pstmt->setInt(1, accNum);
        pstmt->setDouble(2, amount);
        pstmt->execute();
        delete pstmt;
    }

    void displayAccount(int accNum) {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Accounts WHERE accountNumber = ?");
        pstmt->setInt(1, accNum);
        sql::ResultSet *res = pstmt->executeQuery();
        while (res->next()) {
            std::cout << "Account Number: " << res->getInt("accountNumber") << std::endl;
            std::cout << "Account Holder: " << res->getString("accountHolderName") << std::endl;
            std::cout << "Balance: $" << res->getDouble("balance") << std::endl;
        }
        delete res;
        delete pstmt;
    }
};

int main() {
    Bank bank;
    bank.createAccount(1, "Alice", 1000.0);
    bank.deposit(1, 200.0);
    bank.withdraw(1, 100.0);
    bank.displayAccount(1);

    return 0;
}
