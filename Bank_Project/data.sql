CREATE TABLE Accounts (
    accountNumber INT PRIMARY KEY,
    accountHolderName VARCHAR(100),
    balance DOUBLE
);

CREATE TABLE Transactions (
    transactionID INT PRIMARY KEY AUTO_INCREMENT,
    accountNumber INT,
    type VARCHAR(10),
    amount DOUBLE,
    FOREIGN KEY (accountNumber) REFERENCES Accounts(accountNumber)
);
