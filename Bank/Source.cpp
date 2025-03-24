#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct customer {
    int id, balance, transaction_amount;
    string name, password, address, mobile_no;
};

const int MAX_ACCOUNTS = 100;
customer accounts[MAX_ACCOUNTS];
int accountsNumber = 0;

void load_to_array();
void save_to_file();
void main_menu();
void login();
void create_account();
void deposit_menu(int account_no);
void withdraw_menu(int account_no);
void inquire(int account_no);
void show_info(int account_no);
void update_info(int account_no);




int main() {
    main_menu();
}



void main_menu() {
    int MainMenuChoice;
    cout << "==================================" << endl;
    cout << "welcome to NBA" << endl;
    cout << "______" << endl;
    cout << "press 1 to log in " << endl;
    cout << "press 2 to create an account" << endl;
    cout << "press 3 to exit" << endl;
    cin >> MainMenuChoice;

    switch (MainMenuChoice) {
    case 1: // login
        load_to_array();
        login();
        break;
    case 2:
        create_account();
        break;
    case 3: //exit
        save_to_file();
        break;
    default:
        cout << "choose one of the options above please" << endl;
        break;
    }

}

void load_to_array() {
    ifstream file("accounts.txt");
    accountsNumber = 0; // Reset the counter to prevent duplicates

    if (file.is_open()) {
        while (!file.eof() && accountsNumber < MAX_ACCOUNTS) {
            string temp;
            getline(file, accounts[accountsNumber].name);
            if (accounts[accountsNumber].name.empty()) break; // Stop at empty line

            getline(file, accounts[accountsNumber].password);
            file >> accounts[accountsNumber].id;
            file >> accounts[accountsNumber].balance;
            file.ignore(); // Ignore newline

            getline(file, accounts[accountsNumber].address);
            getline(file, accounts[accountsNumber].mobile_no);

            // Ignore any extra blank lines
            while (file.peek() == '\n' || file.peek() == '\r') file.ignore();

            accountsNumber++;
        }
        file.close();
    }
}

void save_to_file() {
    ofstream file("accounts.txt");
    if (file.is_open()) {
        for (int i = 0; i < accountsNumber;i++) {
            file << accounts[i].name << endl;
            file << accounts[i].password << endl;
            file << accounts[i].id << endl;
            file << accounts[i].balance << endl;
            file << accounts[i].address << endl;
            file << accounts[i].mobile_no << endl;
        }
        file.close();
    }
}



int validate_login(string username, string password) {
    for (int i = 0;i < accountsNumber; i++) {
        if (username == accounts[i].name && password == accounts[i].password)
            return i;
    }
    return -1;
}

void login() {
    string username, password;
    cout << "Enter User Name" << endl;
    cin >> username;
    cout << "Enter Password" << endl;
    cin >> password;

    int account_no = validate_login(username, password);

    if (account_no >= 0) {
        int choice;
        do {
            cout << "======== Welcome =========" << endl;
            cout << "Press 1 to make a deposit" << endl;
            cout << "Press 2 to make a withdraw" << endl;
            cout << "Press 3 to enquire about balance" << endl;
            cout << "Press 4 to show account info" << endl;
            cout << "Press 5 to update account info" << endl;
            cout << "Press 0 to logout to main menu" << endl;
            cin >> choice;
            switch (choice) {
            case 0:
                main_menu();
                break;
            case 1:
                deposit_menu(account_no);
                break;
            case 2:
                withdraw_menu(account_no);
                break;
            case 3:
                inquire(account_no);
                break;
            case 4:
                show_info(account_no);
                break;
            case 5:
                update_info(account_no);
                break;
            default:
                cout << "invalid choice" << endl;
                break;
            }
        } while (choice != 0);
    }
    else {
        cout << "=======================================" << endl;
        cout << endl;
        cout << "Invalid credentials" << endl;
        cout << endl;
        cout << "=======================================" << endl;
        main_menu();
    }
}


//function for creating accounts
void create_account() {
    cin.ignore();

    cout << "Enter Account NAME" << endl;
    getline(cin, accounts[accountsNumber].name);

    cout << "Enter Account PASSWORD" << endl;
    getline(cin, accounts[accountsNumber].password);

    cout << "Enter Account ID" << endl;
    cin >> accounts[accountsNumber].id;
    cin.ignore();

    cout << "Enter Account BALANCE" << endl;
    cin >> accounts[accountsNumber].balance;
    cin.ignore();

    cout << "Enter MOBILE NUMBER" << endl;
    cin >> accounts[accountsNumber].mobile_no;
    cin.ignore();

    cout << "Enter ADDRESS" << endl;
    getline(cin, accounts[accountsNumber].address);

    accountsNumber++;
    cout << "Total accounts = " << accountsNumber << endl;
    main_menu();
}//end of the func


void deposit_menu(int account_no) {
    cout << "Enter the amount you want to deposit" << endl;
    cin >> accounts[account_no].transaction_amount;
    accounts[account_no].balance += accounts[account_no].transaction_amount;
}

void withdraw_menu(int account_no) {
    cout << "Enter the amount you want to withdraw" << endl;
    cin >> accounts[account_no].transaction_amount;
    accounts[account_no].balance -= accounts[account_no].transaction_amount;
}

void inquire(int account_no) {
    cout << "Total BALANCE : " << accounts[account_no].balance << endl;
}

void show_info(int account_no) {
    cout << "=======================================" << endl;
    cout << endl;
    cout << "Account NAME : " << accounts[account_no].name << endl;
    cout << "Account ID : " << accounts[account_no].id << endl;
    cout << "Account BALANCE : " << accounts[account_no].balance << endl;
    cout << "ADDRESS :" << accounts[account_no].address << endl;
    cout << "Mobile NUMBER :" << accounts[account_no].mobile_no << endl;
    cout << endl;
    cout << "=======================================" << endl;
    cout << endl;
}

void update_info(int account_no) {
    int choice;
    cout << "=======================================" << endl;
    cout << endl;
    cout << "Press 1 to update USERNAME" << endl;
    cout << "Press 2 to update PASSWORD" << endl;
    cout << "Press 3 to update ADDRESS" << endl;
    cout << "Press 4 to update MOBILE NUMBER" << endl;
    cout << "Press 0 to logout to main menu" << endl;
    cout << endl;
    cout << "=======================================" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
    {
        cin.ignore();
        string new_user;
        cout << "Enter New USERNAME PLEASE :" << endl;
        getline(cin, new_user);
        accounts[account_no].name = new_user;
    }
    break;
    case 2:
    {
        cin.ignore();
        string new_password;
        cout << "Enter New Password : " << endl;
        getline(cin, new_password);
        accounts[account_no].password = new_password;
    }
    break;
    case 3:
    {
        cin.ignore();
        string new_address;
        cout << "Enter new ADDRESS : " << endl;
        getline(cin, new_address);
        accounts[account_no].address = new_address;
    }
    break;
    case 4:
    {
        cin.ignore();
        string new_mobile;
        cout << "Enter New Mobile: " << endl;
        getline(cin, new_mobile);
        accounts[account_no].mobile_no = new_mobile;
    }
    break;
    default:
        cout << "Invalid Choice" << endl;
        break;
    }
}
