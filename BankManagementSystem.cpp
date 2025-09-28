#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string name;
    double balance;

    BankAccount(int accNo, string accName, double bal) {
        accountNumber = accNo;
        name = accName;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void display() {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Name: " << name << "\n";
        cout << "Balance: " << balance << "\n";
    }
};

class BankSystem {
    vector<BankAccount> accounts;

    BankAccount* findAccount(int accNo) {
        for (auto& acc : accounts) {
            if (acc.accountNumber == accNo)
                return &acc;
        }
        return nullptr;
    }

public:
    void createAccount() {
        int accNo;
        string name;
        double balance;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        accounts.push_back(BankAccount(accNo, name, balance));
        cout << "Account Created Successfully!" << endl;
    }

    void depositMoney() {
        int accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Amount to Deposit: ";
        cin >> amount;
        BankAccount* acc = findAccount(accNo);
        if (acc) {
            acc->deposit(amount);
            cout << "Amount Deposited Successfully!" << endl;
        }
        else cout << "Account not found" << endl;
    }

    void withdrawMoney() {
        int accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;
        BankAccount* acc = findAccount(accNo);
        if (acc) {
            if (acc->withdraw(amount)) cout << "Amount Withdrawn Successfully!" << endl;
            else cout << "Insufficient Funds" << endl;
        }
        else cout << "Account not found" << endl;
    }

    void checkBalance() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;
        BankAccount* acc = findAccount(accNo);
        if (acc) acc->display();
        else cout << "Account not found" << endl;
    }

    void transferFunds() {
        int fromAcc, toAcc;
        double amount;
        cout << "Enter From Account Number: ";
        cin >> fromAcc;
        cout << "Enter To Account Number: ";
        cin >> toAcc;
        cout << "Enter Amount to Transfer: ";
        cin >> amount;
        BankAccount* from = findAccount(fromAcc);
        BankAccount* to = findAccount(toAcc);
        if (from && to) {
            if (from->withdraw(amount)) {
                to->deposit(amount);
                cout << "Transfer Successful!" << endl;
            }
            else {
                cout << "Insufficient Funds in Source Account" << endl;
            }
        }
        else {
            cout << "One or Both Accounts not found" << endl;
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n--- Bank Menu ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Transfer Funds" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: bank.createAccount();
                break;
        case 2: bank.depositMoney();
                break;
        case 3: bank.withdrawMoney();
                break;
        case 4: bank.checkBalance();
                break;
        case 5: bank.transferFunds();  
                break;
        case 6: cout << "Exiting..." << endl;
                break;
        default: cout << "Invalid choice" << endl;
        }
    } while (choice != 6);

    return 0;
}
