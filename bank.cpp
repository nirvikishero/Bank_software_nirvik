#include <iostream>
#include <string>
#include <cctype>
#include <fstream> // for file handling
#include <algorithm> // for replacing spaces in the file name

using namespace std;

class Account {
public:
    string account_holder_name;
    long int account_number;
    double balance;
    virtual void deposit(double depo_amt) = 0;
    virtual void withdraw(double with_amt) = 0;
    virtual void display_details() = 0;
    virtual void save_to_file() = 0;  // function to save details to file
};

// Saving account class
class SavingAccount : public Account {
public:
    SavingAccount(string name = "Default name", long int accnum = 100000, double bal = 0.0) {
        account_holder_name = name;
        account_number = accnum;
        balance = bal;
    }

    void display_details() override {
        cout << "Saving account details" << endl << "________________" << endl;
        cout << "Name : " << account_holder_name << endl;
        cout << "Account number : " << account_number << endl;
        cout << "Balance : " << balance << endl << endl << endl;
    }

    void save_to_file() override {
        string file_name = get_file_name();
        ofstream file(file_name);

        if (file.is_open()) {
            file << "Saving Account Details\n";
            file << "______________________\n";
            file << "Name: " << account_holder_name << endl;
            file << "Account Number: " << account_number << endl;
            file << "Balance: " << balance << endl;
            file.close();
            cout << "Details saved to " << file_name << endl;
        } else {
            cout << "Error opening file to write!" << endl;
        }
    }

    string get_file_name() {
        string file_name = account_holder_name;
        replace(file_name.begin(), file_name.end(), ' ', '_');
        return file_name + ".txt";
    }

    void withdraw(double with_amt) override {
        if (with_amt <= balance) {
            balance -= with_amt;
            cout << "You successfully withdrew Rs. " << with_amt << ". Your new balance is : " << balance << endl;
            save_to_file(); // Update the file with the new balance
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void deposit(double depo_amt) override {
        balance += depo_amt;
        cout << "You successfully deposited Rs. " << depo_amt << ". Your new balance is : " << balance << endl;
        save_to_file(); // Update the file with the new balance
    }
};

// Current account class
class CurrentAccount : public Account {
public:
    CurrentAccount(string name = "Default name", long int accnum = 100000, double bal = 0.0) {
        account_holder_name = name;
        account_number = accnum;
        balance = bal;
    }

    void withdraw(double with_amt) override {
        if (with_amt <= balance) {
            balance -= with_amt;
            cout << "You successfully withdrew Rs. " << with_amt << ". Your new balance is : " << balance << endl;
            save_to_file(); // Update the file with the new balance
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void deposit(double depo_amt) override {
        balance += depo_amt;
        cout << "You successfully deposited Rs. " << depo_amt << ". Your new balance is : " << balance << endl;
        save_to_file(); // Update the file with the new balance
    }

    void display_details() override {
        cout << "Current account details" << endl << "________________" << endl;
        cout << "Name : " << account_holder_name << endl;
        cout << "Account number : " << account_number << endl;
        cout << "Balance : " << balance << endl << endl << endl;
    }

    void save_to_file() override {
        string file_name = get_file_name();
        ofstream file(file_name);

        if (file.is_open()) {
            file << "Current Account Details\n";
            file << "______________________\n";
            file << "Name: " << account_holder_name << endl;
            file << "Account Number: " << account_number << endl;
            file << "Balance: " << balance << endl;
            file.close();
            cout << "Details saved to " << file_name << endl;
        } else {
            cout << "Error opening file to write!" << endl;
        }
    }

    string get_file_name() {
        string file_name = account_holder_name;
        replace(file_name.begin(), file_name.end(), ' ', '_');
        return file_name + ".txt";
    }
};

// Function to handle account creation
void get_details() {
    int no_of_accounts;
    cout << "Enter the number of accounts you want to create: ";
    cin >> no_of_accounts;

    Account* accounts[no_of_accounts]; // Array of pointers to Account objects

    for (int i = 0; i < no_of_accounts; i++) {
        string name;
        long int acc_number;
        double balance;
        string type;

        cin.ignore(); // to ignore the leftover newline from previous input
        cout << "Enter the name of the account holder: ";
        getline(cin, name);

        cout << "Enter account number: ";
        cin >> acc_number;

        cout << "Enter the balance: ";
        cin >> balance;

        cout << "Account type [saving or current]: ";
        cin >> type;

        for (char& c : type) {
            c = tolower(c);
        }

        if (type == "saving" || type == "savings") {
            accounts[i] = new SavingAccount(name, acc_number, balance);
        } else if (type == "current") {
            accounts[i] = new CurrentAccount(name, acc_number, balance);
        } else {
            cout << "Invalid account type! Defaulting to saving account." << endl;
            accounts[i] = new SavingAccount(name, acc_number, balance);
        }

        // Display details and save to file
        accounts[i]->display_details();
        accounts[i]->save_to_file();
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < no_of_accounts; i++) {
        delete accounts[i];
    }
}

// Function to get details from file of a particular account holder
void get_account_details_from_file(string account_holder_name) {
    string file_name = account_holder_name;
    replace(file_name.begin(), file_name.end(), ' ', '_');
    file_name += ".txt";

    ifstream file(file_name);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Account details not found for " << account_holder_name << endl;
    }
}

// Function to delete account
void delete_account(string account_holder_name) {
    string file_name = account_holder_name;
    replace(file_name.begin(), file_name.end(), ' ', '_');
    file_name += ".txt";

    if (remove(file_name.c_str()) == 0) {
        cout << "Account for " << account_holder_name << " has been successfully deleted.\n";
    } else {
        cout << "Error: Account for " << account_holder_name << " not found or could not be deleted.\n";
    }
}

// Function to deposit money into an account
void deposit_to_account(string account_holder_name, double deposit_amount) {
    string file_name = account_holder_name;
    replace(file_name.begin(), file_name.end(), ' ', '_');
    file_name += ".txt";

    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Account not found for " << account_holder_name << endl;
        return;
    }

    // Read existing balance
    string line;
    double balance = 0;
    while (getline(file, line)) {
        if (line.find("Balance: ") != string::npos) {
            balance = stod(line.substr(line.find(":") + 2));
        }
    }
    file.close();

    // Update balance and save
    balance += deposit_amount;
    ofstream file_out(file_name);
    file_out << "Saving Account Details\n";
    file_out << "______________________\n";
    file_out << "Name: " << account_holder_name << endl;
    file_out << "Account Number: " << "xxxxxxxx" << endl;  // Keep same account number
    file_out << "Balance: " << balance << endl;
    file_out.close();

    cout << "Successfully deposited Rs. " << deposit_amount << ". New balance: " << balance << endl;
}

// Function to withdraw money from an account
void withdraw_from_account(string account_holder_name, double withdraw_amount) {
    string file_name = account_holder_name;
    replace(file_name.begin(), file_name.end(), ' ', '_');
    file_name += ".txt";

    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Account not found for " << account_holder_name << endl;
        return;
    }

    // Read existing balance
    string line;
    double balance = 0;
    while (getline(file, line)) {
        if (line.find("Balance: ") != string::npos) {
            balance = stod(line.substr(line.find(":") + 2));
        }
    }
    file.close();

    // Check if balance is enough for the withdrawal
    if (balance < withdraw_amount) {
        cout << "Insufficient balance! Withdrawal failed." << endl;
        return;
    }

    // Update balance and save
    balance -= withdraw_amount;
    ofstream file_out(file_name);
    file_out << "Saving Account Details\n";
    file_out << "______________________\n";
    file_out << "Name: " << account_holder_name << endl;
    file_out << "Account Number: " << "xxxxxxxx" << endl;  // Keep same account number
    file_out << "Balance: " << balance << endl;
    file_out.close();

    cout << "Successfully withdrew Rs. " << withdraw_amount << ". New balance: " << balance << endl;
}

int main() {
    while (true) {
    string check;
    cout << "Who are you: ";
    cin >> check;

    if (check == "admin") {
        int attempt = 0;
        int max_attempt = 5 ;
        while (attempt < max_attempt) {
            string password;
            cout << "Enter the password: ";
            cin >> password;
            if (password == "Name@123") {
                cout << "Welcome Admin!!!!\n";
                int task;
                cout << "What do you want to do? :\n 1. Open account \n 0. Close account \n 2. Check account: ";
                cin >> task;

                if (task == 1) {
                    get_details();  // Create new accounts
                } 
                else if (task == 0) {
                    string account_name;
                    cout << "\nEnter the name of the account holder to delete details from file: ";
                    cin.ignore();
                    getline(cin, account_name);
                    delete_account(account_name);  // Delete account
                } 
                else if (task == 2) {
                    string account_name;
                    cout << "\nEnter the name of the account holder to fetch details from file: ";
                    cin.ignore();
                    getline(cin, account_name);
                    get_account_details_from_file(account_name);  // Check account details
                } 
                else {
                    cout << "Choose wisely!!!";
                    continue;
                }
                break;
            } 
            else {
                attempt++;
                if (attempt < max_attempt) {
                cout << "Wrong password! Recheck. You have " << (max_attempt - attempt) << " attempt(s) left.\n";
                continue;
                } else {
                cout << "You have reached the maximum number of attempts. Access denied.\n";
                break; // Exit the loop if the maximum number of attempts is reached
                }
            }
        }
    } 
    else {
        int task;
        cout << "Enter the task you want to perform: \n 1. Deposit \n 0. Withdraw \n 2. Get details: ";
        cin >> task;

        if (task == 2) {
            string account_name;
            cout << "\nEnter the name of the account holder to fetch details from file: ";
            cin.ignore();
            getline(cin, account_name);
            get_account_details_from_file(account_name);  // Get details
        } 
        else if (task == 1) {
            string account_name;
            double amount;
            cout << "\nEnter the name of the account holder to deposit money: ";
            cin.ignore();
            getline(cin, account_name);
            cout << "Enter the amount to deposit: ";
            cin >> amount;

            // Call deposit function
            deposit_to_account(account_name, amount);  // Function to handle deposit
        } 
        else if (task == 0) {
            string account_name;
            double amount;
            cout << "\nEnter the name of the account holder to withdraw money: ";
            cin.ignore();
            getline(cin, account_name);
            cout << "Enter the amount to withdraw: ";
            cin >> amount;

            // Call withdraw function
            withdraw_from_account(account_name, amount);  // Function to handle withdrawal
        }
    }
    }
    return 0;
}