#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isLoggedIn = false;
bool isInChat = false;
string currentChat;
string currentLogin;
string max_user_id;

void logOut()
{
    isLoggedIn = false;
}

void get_max_user_id()
{
    fstream file;
    file.open("users.txt", ios::app);
    max_user_id = "0";
    string needful, needless;
    while (file >> needful >> needless >> needless) {
        max_user_id = needful;
    }
    file.close();
}

void start_register()
{   
    string login, password, email;
    string input_login, input_password, input_email, id;

    string new_id = to_string(stoi(max_user_id) + 1);
    max_user_id = new_id;

    cout << "\nInput the new login\n";
    cin >> login;
    cout << "Input your email:\n";
    cin >> email;
    cout << "Type the new password\n";
    cin >> password;

    ifstream ifile;
    ifile.open("users.txt", ios::in);
    bool inFile = false;
    while (ifile >> id >> input_login >> input_email >> input_password)
    {
        if (input_login == login || input_email == email)
        {
            inFile = true;
            break;
        }
    }

    if (!inFile) {
        cout << "You are in the new account, registered with id " << new_id << "\n\n";

        fstream file;
        file.open("users.txt", ios::app);
        file << new_id << ' ' << login << ' ' << email << ' ' << password << '\n';
        file.close();

        isLoggedIn = true;
        currentLogin = login;
    }
    else
    {
        cout << "There's user in the system with the same email or login!\nRegistration is canceled\n\n";
    }
    ifile.close();
    return;
}


void login()
{   
    if (!isLoggedIn) {
        string login, needful, needless, password, inputted_password;
        cout << "\n\nInput your login: \n";
        cin >> login;
        ifstream ifile;
        ifile.open("users.txt", ios::in);
        bool inFile = false;
        while (ifile >> needless >> needful >> needless >> needless)
        {
            if (needful == login) {
                password = needless;
                inFile = true;
                break;
            }
        }
        if (!inFile)
        {
            cout << "There's not a user with that login!\n\n";
        }
        else
        {
            cout << "Now write your password: \n";
            cin >> inputted_password;
            if (inputted_password == password)
            {
                cout << "You successfully logged in!\n\n";
                isLoggedIn = true;
            }
            else
            {
                cout << "That's the wrong password!\n\n";
            }
        }
    }
    else
    {
        cout << "\n\nYou should log out first! (>>logOut)\n\n";
    }
}


void listen_commands()
{
    string command;
    cin >> command;
    while (command != ">>end") {
        if (command == ">>register")
        {   
            if (!isLoggedIn) {
                start_register();
            }
            else
            {
                cout << "You should log out first! (>>logOut)\n";
            }
        }
        else if (command == ">>login")
        {
            login();
        }
        else if (command == ">>logOut")
        {
            logOut();
        }
        else
        {
            cout << "You just inputted the wrong command!\n";
        }
        cin >> command;
    }
    return;
}

int main()
{
    get_max_user_id();

    listen_commands();
    return 0;
}