/*
    CodeAlpha Internship - Task 4: Banking System
    ------------------------------------------------
    What this program does:
    - Uses 3 classes, as required: Customer, Transaction, and Account.
    - Lets you create accounts, deposit, withdraw, transfer money between
      accounts, and view account info + transaction history.
    - Everything runs through a simple menu in the console.

    Note: This stores data only while the program is running (in memory),
    same as your earlier group project. If you want it to save to a file
    between runs, that's an easy upgrade later - ask me and I'll show you.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ---------------------------------------------------------
// CLASS 1: Transaction
// Represents ONE action on an account (a deposit, withdrawal, etc.)
// ---------------------------------------------------------
class Transaction {
public:
    string type;          // "Deposit", "Withdraw", "Transfer In", "Transfer Out"
    double amount;
    double balanceAfter;  // what the balance was right after this transaction

    // Constructor: runs automatically when we create a Transaction object
    Transaction(string t, double amt, double balAfter) {
        type = t;
        amount = amt;
        balanceAfter = balAfter;
    }
};

// ---------------------------------------------------------
// CLASS 2: Customer
// Represents the PERSON who owns the account (their personal info)
// ---------------------------------------------------------
class Customer {
public:
    int customerId;
    string name;

    Customer(int id = 0, string n = "") {
        customerId = id;
        name = n;
    }
};

// ---------------------------------------------------------
// CLASS 3: Account
// Represents the BANK ACCOUNT itself - holds the customer, balance,
// and the full list of transactions made on this account.
// ---------------------------------------------------------
class Account {
public:
    int accountNumber;
    Customer owner;
    double balance;
    vector<Transaction> history; // every transaction ever made on this account

    Account(int accNum, Customer cust, double startingBalance) {
        accountNumber = accNum;
        owner = cust;
        balance = startingBalance;
    }

    // Add money to the account
    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount, balance));
        cout << "Deposited $" << amount << ". New balance: $" << balance << "\n";
    }

    // Remove money from the account, if there's enough balance
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Withdrawal failed: insufficient balance.\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount, balance));
        cout << "Withdrew $" << amount << ". New balance: $" << balance << "\n";
        return true;
    }

    // Print account details
    void showDetails() {
        cout << "\n--- Account Details ---\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Owner: " << owner.name << " (Customer ID: " << owner.customerId << ")\n";
        cout << "Balance: $" << balance << "\n";
    }

    // Print every past transaction on this account
    void showHistory() {
        cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (int i = 0; i < (int)history.size(); i++) {
            cout << (i + 1) << ". " << history[i].type
                 << " | Amount: $" << history[i].amount
                 << " | Balance After: $" << history[i].balanceAfter << "\n";
        }
    }
};

// ---------------------------------------------------------
// Helper function: finds an account by account number in a list.
// Returns a pointer so we can modify the actual account (not a copy).
// Returns nullptr (nothing) if not found.
// ---------------------------------------------------------
Account* findAccount(vector<Account>& accounts, int accNum) {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].accountNumber == accNum) {
            return &accounts[i];
        }
    }
    return nullptr;
}

int main() {
    vector<Account> accounts;   // holds all accounts created so far
    int nextAccountNumber = 1001;
    int nextCustomerId = 1;

    int choice;
    do {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Details\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << fixed << setprecision(2);

        if (choice == 1) {
            string name;
            double startingBalance;
            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter starting deposit amount: ";
            cin >> startingBalance;

            Customer newCustomer(nextCustomerId++, name);
            Account newAccount(nextAccountNumber, newCustomer, startingBalance);
            accounts.push_back(newAccount);

            cout << "Account created! Your account number is: " << nextAccountNumber << "\n";
            nextAccountNumber++;
        }
        else if (choice == 2) {
            int accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc == nullptr) {
                cout << "Account not found.\n";
            } else {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc->deposit(amount);
            }
        }
        else if (choice == 3) {
            int accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc == nullptr) {
                cout << "Account not found.\n";
            } else {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc->withdraw(amount);
            }
        }
        else if (choice == 4) {
            int fromAcc, toAcc;
            double amount;
            cout << "Enter YOUR account number: ";
            cin >> fromAcc;
            cout << "Enter RECEIVER's account number: ";
            cin >> toAcc;
            cout << "Enter amount to transfer: ";
            cin >> amount;

            Account* sender = findAccount(accounts, fromAcc);
            Account* receiver = findAccount(accounts, toAcc);

            if (sender == nullptr || receiver == nullptr) {
                cout << "One or both account numbers not found.\n";
            } else if (sender->withdraw(amount)) {
                // withdraw() already logged a "Withdraw" transaction;
                // now log it more specifically and complete the transfer.
                receiver->balance += amount;
                receiver->history.push_back(Transaction("Transfer In", amount, receiver->balance));
                cout << "Transfer successful!\n";
            }
        }
        else if (choice == 5) {
            int accNum;
            cout << "Enter account number: ";
            cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc == nullptr) cout << "Account not found.\n";
            else acc->showDetails();
        }
        else if (choice == 6) {
            int accNum;
            cout << "Enter account number: ";
            cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc == nullptr) cout << "Account not found.\n";
            else acc->showHistory();
        }
        else if (choice == 7) {
            cout << "Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid choice, try again.\n";
        }

    } while (choice != 7);

    return 0;
}
