#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"

using namespace std;

struct userData {
    string fullName;
    string userName;
    string phNumber;
    string email;
    string password;
    string confirmPassword;
    string role;
};

struct contact {
    string name;
    string contactNo;
};

static string roles[5] = {"manager", "employee"};
const int noOfUsers = 200;
const int noOfFields = 7;
int activeUser;
string usersInfo[noOfUsers][noOfFields];
string employeeInfo[noOfUsers][noOfFields];
string userContacts[50][3];

int getExistingUsers() {
    int i = 0;
    fstream UsersFile("usersInfo.txt", ios::in);
    if (!UsersFile.is_open()) {
        cout << "\nfile is not opened!!!\n";
        return 0;
    }
    while (!UsersFile.eof()) {
        UsersFile >> usersInfo[i][0]
                  >> usersInfo[i][1]
                  >> usersInfo[i][2]
                  >> usersInfo[i][3]
                  >> usersInfo[i][4]
                  >> usersInfo[i][5]
                  >> usersInfo[i][6];
        i++;
    }
    UsersFile.close();

    return i;
}

//Sign Up Module

void signUp() {
    int type, nUsers = getExistingUsers();
    userData userInfo;
    int lastId = stoi(usersInfo[nUsers - 2][0]);

    cout << endl;
    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t CREATE YOUR ACCOUNT... \t\t   |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;


    cout << "\tEnter Your Full Name : ";
    cin >> userInfo.fullName;

    int itr;
    while (1) {
        itr = 1;
        cout << "\tEnter Your User Name : ";
        cin >> userInfo.userName;
        for (int i = 0; i < nUsers; ++i) {
            if (userInfo.userName == usersInfo[i][2]) {
                ++itr;
            }
        }
        if (itr > 1) {
            cout << "\n\tUser Name Already Taken. Try with New One.\n\n";
        } else {
            break;
        }
    }

    while (1) {
        itr = 1;
        cout << "\tEnter a Valid Phone Number : ";
        cin >> userInfo.phNumber;
        for (int i = 0; i < nUsers; ++i) {
            if (userInfo.phNumber == usersInfo[i][3]) {
                ++itr;
            }
        }

        if (itr > 1) {
            cout << "\n\tPhone Number Already Taken. Try with New One.\n\n";
        } else {
            break;
        }
    }

    while (1) {
        itr = 1;
        cout << "\tEnter a Valid Email: ";
        cin >> userInfo.email;
        for (int i = 0; i < nUsers; ++i) {
            if (userInfo.email == usersInfo[i][4]) {
                ++itr;
            }
        }

        if (itr > 1) {
            cout << "\n\tEmail Already Taken. Try with New One.\n\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "\tEnter Password (at least 8 characters) : ";
        cin >> userInfo.password;
        if (userInfo.password.length() >= 8) {
            break;
        }
        cout << "\n\tPassword must be at least 8 characters.\n\n";
    }
    do {
        cout << "\tConfirm Password : ";
        cin >> userInfo.confirmPassword;
        if (userInfo.confirmPassword != userInfo.password) {
            cout << "\n\tPasswords Must be Same.\n\n";
        }
    } while (userInfo.confirmPassword != userInfo.password);


    cout << "\n\tYour account has been created successfully.\n";
    ofstream LoginData("usersInfo.txt", ios::app);
    if (LoginData.is_open()) {
        LoginData << lastId + 1 << " "
                  << userInfo.fullName << " "
                  << userInfo.userName << " "
                  << userInfo.phNumber << " "
                  << userInfo.email << " "
                  << userInfo.password << " "
                  << "user" << endl;
    }
    LoginData.close();
}


// Login Module

template<class T>

bool loginAuth(T userName, T pass) {
    getExistingUsers();
    for (int i = 0; i < noOfUsers; ++i) {
        if ((userName == usersInfo[i][2] || userName == usersInfo[i][4]) && pass == usersInfo[i][5]) {
            activeUser = i;
            return true;
        }
    }
    return false;
}

char login() {

    string role;
    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t LOGIN HERE... \t\t\t\t   |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;
    string userName, password;

    while (true) {
        cout << "\tEnter Your UserName or Email : ";
        cin >> userName;
        cout << "\tEnter Password : ";
        cin >> password;
        if (loginAuth(userName, password)) {
            role = usersInfo[activeUser][6];
            cout << "\nHi " << usersInfo[activeUser][1] << "\nWelcome on the Board !\n";
            break;
        } else {
            cout << "\n\tCredentials didn't match. Please Try Again.\n\n";
        }
    }

    return role[0];
}

int getContacts() {
    int i = 0, n = 0;
    string fileName = usersInfo[activeUser][2] + "Contacts.txt";
    fstream ContactsFile(fileName, ios::in);
    if (!ContactsFile.is_open()) {
        cout << "\nNo Contacts Found !!!\n";
        return 0;
    }
    while (!ContactsFile.eof()) {
        ContactsFile >> userContacts[i][0]
                     >> userContacts[i][1];
        i++;
    }
    ContactsFile.close();

    return i;
}

void addContact() {
    int nUsers = getExistingUsers(), occour = 0;
    string **UserContacts = new string *[1];

    for (int i = 0; i < nUsers; i++) {
        UserContacts[i] = new string[2];
    }

    cout << "Enter Contact Name : ";
    cin >> UserContacts[0][0];
    cout << "Enter Phone Number : ";
    cin >> UserContacts[0][1];
    cout << "Contact Added Successfully.\n";

    for (int i = 0; i < nUsers; i++) {
        if (UserContacts[0][1] == usersInfo[i][3]) {
            cout << "User With this Contact is linked to our Platform. You Can Chat with this user.\n";
            occour = 1;
        }
    }

    if (occour == 0) {
        cout << "Sorry! User with this contact is not Linked to Our Platform.\n";
    }

    string fileName = usersInfo[activeUser][2] + "Contacts.txt";

    fstream ContactsFile(fileName, ios::app);
    ContactsFile << UserContacts[0][0] << " "
                 << UserContacts[0][1] << endl;

    ContactsFile.close();

}

void loadPreviousChat() {

}

void readChats(string fileName) {
    fstream ChatFile(fileName, ios::in);
    if (!ChatFile.is_open()) {
        cout << "\nUnable to Load Chats!!!\n";
        return;
    }
    string line;
    cout << "\n";
    while (getline(ChatFile, line)) {
        cout << line << endl;
    }
    ChatFile.close();
}

void chatWithPerson(string fileName) {
    string message;
    int choice;
    cout << endl;
    while (1) {

        cout << "Enter Message (-1 to Exit) : ";
        getline(cin, message);
        if (message == "-1") {
            break;
        }

        fstream ChatFile(fileName, ios::app);
        if (ChatFile.is_open()) {
            ChatFile << usersInfo[activeUser][2] << ": " << message << endl;
        }
        ChatFile.close();

    }
}

void userPage() {
    int choice;
    do {
        cout << endl;
        cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
        cout << " |\t\t\t MAIN MENU \t\t\t\t   |" << endl;
        cout << " └─────────────────────────────────────────────────────────────────┘" << endl;
        cout << "1. Add More Contacts.";
        cout << "\n2. View Contacts.";
        cout << "\n3. Chats.";
        cout << "\n4. Exit.";
        cout << "\nEnter your Choice : ";
        cin >> choice;
        switch (choice) {
            case 1: {
                while (1) {
                    int iterator;
                    addContact();
                    cout << "\nEnter 0 to Go Main Menu and 1 to add More Contacts : ";
                    cin >> iterator;
                    if (iterator == 0) {
                        break;
                    }
                }
                break;
            }
            case 2: {
                int nContacts = getContacts();
                if (nContacts != 0) {
                    cout << "\nYour Contacts : \n";
                    for (int j = 0; j < nContacts - 1; ++j) {
                        cout << j + 1 << ". " << userContacts[j][0] << "\t" << userContacts[j][1] << endl;
                    }
                }
                break;
            }
            case 3: {
                int nContacts = getContacts(), iterator, chatIndex;
                int nUsers = getExistingUsers();
                string availableUsers[nContacts][2];
                string dataFileName;
                cout << "\nYou can Chat with these People in your contact List : " << endl;
                int n = 0;
                for (int j = 0; j < nContacts - 1; ++j) {
                    for (int i = 0; i < nUsers - 1; ++i) {
                        if (userContacts[j][1] == usersInfo[i][3]) {
                            availableUsers[n][0] = userContacts[j][0];
                            availableUsers[n][1] = userContacts[j][1];
                            ++n;
                        }
                    }
                }

                for (int i = 0; i < n; ++i) {
                    cout << i + 1 << ". " << userContacts[i][0] << "\t" << userContacts[i][1] << endl;
                }

                cout << "\nEnter Index to Chat with Person : ";
                cin >> chatIndex;
                cin.ignore(1000, '\n');

                cout << "\t\t----- " << availableUsers[chatIndex - 1][0] << " -----";

                if ((usersInfo[activeUser][2] == "Ali" && availableUsers[chatIndex - 1][0] == "Ahmed") ||
                     (usersInfo[activeUser][2] == "Ahmed" && availableUsers[chatIndex - 1][0] == "Ali"))
                    dataFileName = "Ali&AhmedChat.txt";
                else
                    dataFileName = "DummyChat.txt";
                readChats(dataFileName);
                chatWithPerson(dataFileName);
                if (iterator == 0) {
                    break;
                }
            }
        }
    } while (choice != 4);
}