#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <sstream>
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

static string groupSecurity[2] = {"Every Member can send Message", "Only Admins can send message"};
const int noOfUsers = 200;
const int noOfFields = 7;
int activeUser;
string usersInfo[noOfUsers][noOfFields];
string employeeInfo[noOfUsers][noOfFields];
string userContacts[50][3];
string groupNames[100];

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

int getGroupsNames() {
    int i = 0;
    fstream GroupsNames("groups/Groups.txt", ios::in);
    if (!GroupsNames.is_open()) {
        return 0;
    }
    while (getline(GroupsNames, groupNames[i])) {
        i++;
    }
    GroupsNames.close();

    return i;
}
//Sign Up Module

void signUp() {
    int nUsers = getExistingUsers();
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
    cout << " |\t\t\t     LOGIN HERE...  \t\t\t   |" << endl;
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
    int i = 0;
    string fileName = "contacts/" + usersInfo[activeUser][2] + "Contacts.txt";
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
    int nContacts = getContacts();
    string **UserContacts = new string *[1];

    for (int i = 0; i < nUsers; i++) {
        UserContacts[i] = new string[2];
    }


    int itr;
    while (1) {
        itr = 1;
        cout << "Enter Contact Name : ";
        cin >> UserContacts[0][0];
        for (int i = 0; i < nUsers; ++i) {
            if (UserContacts[0][0] == userContacts[i][0]) {
                ++itr;
            }
        }
        if (itr > 1) {
            cout << "\n\tContact With This Name Already Exists. Try with New One.\n\n";
        } else {
            break;
        }
    }

    while (1) {
        itr = 1;

        cout << "Enter Phone Number : ";
        cin >> UserContacts[0][1];
        for (int i = 0; i < nUsers; ++i) {
            if (UserContacts[0][1] == userContacts[i][1]) {
                ++itr;
            }
        }
        if (itr > 1) {
            cout << "\n\tPhone Number Already Exists. Try with New One.\n\n";
        } else {
            break;
        }
    }
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
    system("mkdir -p contacts");
    string fileName = "contacts/" + usersInfo[activeUser][2] + "Contacts.txt";

    fstream ContactsFile(fileName, ios::app);
    ContactsFile << UserContacts[0][0] << " "
                 << UserContacts[0][1] << endl;

    ContactsFile.close();

}

void readChats(string fileName) {
    fstream ChatFile(fileName, ios::in);
    if (!ChatFile.is_open()) {
        return;
    }
    string line;
    cout << "\n";
    while (getline(ChatFile, line)) {
        cout << "\t=> " << line << endl;
    }
    ChatFile.close();
}

void chatWithPerson(string fileName) {
    time_t now = time(0);
    string currentTime = ctime(&now);
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
            ChatFile << usersInfo[activeUser][2] << ": " << message << "\t\t\t" << currentTime;
        }
        ChatFile.close();
    }
}

int searchContact(string name, int n) {
    if (n < 0) {
        return -1;
    } else {
        if (name == userContacts[n][0]) {
            return n;
        }
        return searchContact(name, n - 1);
    }

    return -1;
}

void createGroup() {
    int nContacts = getContacts(), chatIndex;
    int nUsers = getExistingUsers();
    string groupName, description;
    string availableUsers[nContacts][2];
    string groupMembers[nContacts + 1][2];
    groupMembers[0][0] = usersInfo[activeUser][2];
    groupMembers[0][1] = usersInfo[activeUser][3];
    if (nContacts == 0) {
        cout << "\nYou dont have any contact. First Add any Contact";
        return;
    }

    cout << "\nEnter Group Name : ";
    getline(cin, groupName);
    cout << "Enter Group Description : ";
    getline(cin, description);

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

    cout << "Your Contacts : " << endl;

    for (int i = 0; i < n; ++i) {
        cout << "\t" << i + 1 << ". " << availableUsers[i][0] << "\t" << availableUsers[i][1] << endl;
    }

    cout << endl;
    int i = 1;
    while (1) {
        cout << "Enter Index to Add Person in Your Group";
        (i > 1) ? cout << " (or -1 to Exit ) : " : cout << " : ";
        cin >> chatIndex;
        if (chatIndex <= n) {
            groupMembers[i][0] = availableUsers[chatIndex - 1][0];
            groupMembers[i][1] = availableUsers[chatIndex - 1][1];
            i++;
        }
        if (chatIndex > n) {
            cout << "\nInvalid Input Try again" << endl;
        }
        if (chatIndex == -1) {
            break;
        }
    }

    cout << "\nGroup Members : \n";
    for (int j = 0; j < (i - 1); ++j) {
        cout << "\t" << j + 1 << ". " << groupMembers[j][0];
        (j == 0) ? cout << " (You) -> Group Admin" : cout << "";
        cout << "      " << groupMembers[j][1] << endl;
    }

    int grpSecurity;
    cout << "\nGroup Chat Options : ";
    cout << "\n1. Every Member can send Message.\n2. Only Admins can send message.";
    cout << "\nEnter Your Choice : ";
    cin >> grpSecurity;

    system("mkdir -p groups");
    string filePath = "groups/" + groupName + "GRP.txt";

    fstream GroupFile(filePath, ios::app);
    if (GroupFile.is_open()) {
        for (int j = 0; j < (i - 1); ++j) {
            GroupFile << groupMembers[j][0] << " ";
        }
        GroupFile << endl;
        GroupFile << "<<------ " << groupName << " ------>>" << endl;
        GroupFile << "Description : " << description << endl;
        GroupFile << "\t" << groupSecurity[grpSecurity - 1] << endl << endl;
    }

    GroupFile.close();

    fstream Groups("groups/Groups.txt", ios::app);
    if (Groups.is_open()) {
        Groups << groupName << endl;
    }
    Groups.close();

    cout << "Group Created Successfully";
}

bool checkGroupMembers(string grpName) {
    string fileName = "groups/" + grpName + "GRP.txt";
    string line;

    fstream GroupFile(fileName);

    if (!GroupFile.is_open()) {
        return false;
    }

    getline(GroupFile, line);
    GroupFile.close();

    istringstream iss(line);

    int nWords = 0;
    while (iss >> line) {
        nWords++;
    }

    fstream GroupInfo(fileName);

    string grpMembers[nWords];
    for (int i = 0; i < nWords; ++i) {
        GroupInfo >> grpMembers[i];
    }

    GroupInfo.close();

    for (int i = 0; i < nWords; ++i) {
        if (grpMembers[i] == usersInfo[activeUser][2])
            return true;
    }

    return false;
}

bool isAdmin(string grpName, string memberName) {
    string fileName = "groups/" + grpName + "GRP.txt";
    string line;

    fstream GroupFile(fileName);

    if (!GroupFile.is_open()) {
        return false;
    }

    getline(GroupFile, line);
    GroupFile.close();

    istringstream iss(line);

    int nWords = 0;
    while (iss >> line) {
        nWords++;
    }

    fstream GroupInfo(fileName);

    string grpMembers[nWords];
    for (int i = 0; i < nWords; ++i) {
        GroupInfo >> grpMembers[i];
    }

    GroupInfo.close();

    if (grpMembers[0] == memberName)
        return true;

    return false;
}

bool checkGroups() {
    int nGroups = getGroupsNames(), n = 0;
    string userGroups[nGroups];

    for (int i = 0; i < nGroups; ++i) {
        if (checkGroupMembers(groupNames[i])) {
            userGroups[n] = groupNames[i];
            n++;
        }
    }

    if (n > 0) {
        cout << "\nYou are Member of these Groups : " << endl;
        for (int i = 0; i < n; ++i) {
            cout << "\t" << i + 1 << ". " << userGroups[i] << endl;
        }
    } else {
        cout << "\nYou are Not Added in any Group";
        return false;
    }

    return true;
}

void messageInGroup(string path, string msg) {
    time_t now = time(0);
    string currentTime = ctime(&now);
    fstream GroupFile(path, ios::app);

    if (GroupFile.is_open()) {
        GroupFile << "\t -> " << usersInfo[activeUser][2] << " : " << msg << "\t\t\t" << currentTime;
    }

    GroupFile.close();
}

void printGrpMembers(string grpName) {
    string fileName = "groups/" + grpName + "GRP.txt";
    string line;

    fstream GroupFile(fileName);

    if (!GroupFile.is_open()) {
        return;
    }

    getline(GroupFile, line);
    GroupFile.close();

    istringstream iss(line);

    int nMembers = 0;
    while (iss >> line) {
        nMembers++;
    }

    fstream GroupInfo(fileName);

    string grpMembers[nMembers];
    for (int i = 0; i < nMembers; ++i) {
        GroupInfo >> grpMembers[i];
    }

    for (int i = 0; i < nMembers; ++i) {
        cout << "\t" << i + 1 << ". " << grpMembers[i];
        (grpMembers[i] == usersInfo[activeUser][2]) ? cout << " ( YOU ) " : cout << "";
        (i == 0) ? cout << "\t\t( Admin )" : cout << "";
        cout << endl;
    }

    GroupInfo.close();
}

bool allCanSendMsg(string path) {
    string security;
    fstream GroupFile(path);

    if (GroupFile.is_open()) {
        for (int i = 0; i < 4; ++i) {
            getline(GroupFile, security);
        }
    }

    if ("\tEvery Member can send Message" == security) {
        return true;
    }

    return false;
}

void openGroup() {
    int grpIndex;
    string message;
    cout << "\n\nEnter index of Group to Open it : ";
    cin >> grpIndex;
    cin.ignore(1000, '\n');

    string filePath = "groups/" + groupNames[grpIndex - 1] + "GRP.txt";

    fstream GroupData(filePath);
    string line;
    cout << "\tGroup Members : ";
    while (getline(GroupData, line)) {
        cout << "\t" << line << endl;
    }
    cout << endl;
    int choice;
    do {
        cout << "\n\t1. Send Message in Group.";
        cout << "\n\t2. Open Group Settings.";
        cout << "\n\t3. View Group Members.";
        cout << "\n\t4. Exit.";
        cout << "\n\tEnter Your Choice : ";
        cin >> choice;
        cin.ignore(100, '\n');
        switch (choice) {
            case 1: {
                if (allCanSendMsg(filePath)) {
                    do {
                        cout << "Enter message to send ( -1 to Exit ) : ";
                        getline(cin, message);
                        if (message == "-1")
                            break;
                        messageInGroup(filePath, message);
                    } while (message != "-1");
                } else {
                    if (isAdmin(groupNames[grpIndex - 1], usersInfo[activeUser][2])) {
                        do {
                            cout << "Enter message to send ( -1 to Exit ) : ";
                            getline(cin, message);
                            if (message == "-1")
                                break;
                            messageInGroup(filePath, message);
                        } while (message != "-1");
                    } else {
                        cout << "\n\t> Only Admins Can send message in this group.\n";
                    }
                }
                break;
            }
            case 2: {
                cout << "\n\t <----- SETTINGS ----->";
                if (isAdmin(groupNames[grpIndex - 1], usersInfo[activeUser][2])) {
                    int settingChoice;
                    cout << "\n\n\tGroup Settings : " << endl;
                    cout << "\t1. Add More Members." << endl;
                    cout << "\t2. Exit." << endl;
                    cout << "\tEnter Your Choice : ";
                    cin >> settingChoice;

                    switch (settingChoice) {
                        case 1: {
                            cout << "\n\t <----- In Upcoming Updates ----->";
                            break;
                        }
                        case 2:{
                            break;
                        }
                        default:{
                            cout << "\n\tInvalid Input.";
                            break;
                        }
                    }

                } else {
                    cout << "\n\n\t> Only admins can change group settings.\n";
                }
                break;
            }
            case 3: {
                cout << "\n\t <----- GROUP MEMBERS ----->\n\n";
                printGrpMembers(groupNames[grpIndex - 1]);
                break;
            }
            case 4: {
                break;
            }
            default: {
                cout << "\nInvalid Input";
                break;
            }
        }
    } while (choice != 4);

}


void userPage() {
    int choice;
    do {
        cout << endl;
        cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
        cout << " |\t\t\t     MAIN MENU  \t\t\t   |" << endl;
        cout << " └─────────────────────────────────────────────────────────────────┘" << endl;
        cout << "\t1. Add More Contacts.";
        cout << "\n\t2. View Contacts.";
        cout << "\n\t3. Chats.";
        cout << "\n\t4. Search Contact.";
        cout << "\n\t5. Groups.";
        cout << "\n\t6. Exit.";
        cout << "\n\tEnter your Choice : ";
        cin >> choice;
        switch (choice) {
            case 1: {
                while (1) {
                    int iterator;
                    addContact();
                    cout << "\n\tEnter 0 to Go Main Menu and 1 to add More Contacts : ";
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
                    cout << "\n\t\t\t--- Your Contacts --- \n";
                    for (int j = 0; j < nContacts - 1; ++j) {
                        cout << "\t" << j + 1 << ". " << userContacts[j][0] << "\t" << userContacts[j][1] << endl;
                    }
                }
                break;
            }
            case 3: {
                int nContacts = getContacts(), iterator, chatIndex;
                int nUsers = getExistingUsers();
                string availableUsers[nContacts][2];
                if (nContacts == 0)
                    break;
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
                    cout << "\t" << i + 1 << ". " << availableUsers[i][0] << "\t" << availableUsers[i][1] << endl;
                }

                cout << endl;
                while (1) {
                    cout << "\nEnter Index to Chat with Person : ";
                    cin >> chatIndex;
                    cin.ignore(1000, '\n');
                    if (chatIndex <= n) {
                        break;
                    }
                    cout << "Invalid Input Try again";
                }

                system("mkdir -p chats");

                string dataFileName =
                        "chats/" + usersInfo[activeUser][2] + "&" + availableUsers[chatIndex - 1][0] + "Chat.txt";
                fstream ChatFile(dataFileName);
                if (!ChatFile.is_open()) {
                    dataFileName =
                            "chats/" + availableUsers[chatIndex - 1][0] + "&" + usersInfo[activeUser][2] + "Chat.txt";
                }
                cout << "\t\t----- " << availableUsers[chatIndex - 1][0] << " -----";

                readChats(dataFileName);
                chatWithPerson(dataFileName);
                if (iterator == 0) {
                    break;
                }

                break;
            }
            case 4: {
                cout << "\n\t\t\t---SEARCH CONTACT---" << endl;
                string contactName;
                while (1) {
                    int nContacts = getContacts(), result;
                    cout << "\nType name to Search Contact ( 0 to EXIT ) : ";
                    cin >> contactName;
                    if (contactName == "0")
                        break;
                    result = searchContact(contactName, nContacts);
                    if (result != -1) {
                        cout << "\t" << userContacts[result][0] << "\t" << userContacts[result][1];
                    } else {
                        cout << "\tContact not Found With this name.";
                    }
                }

                break;
            }
            case 5: {
                int choice;
                while (1) {
                    cout << "\n\t\t\t--- GROUPS ---" << endl;
                    if (checkGroups())
                        openGroup();
                    cout << "\nEnter 1 to Create group (Else exit) : ";
                    cin >> choice;
                    cin.ignore(10000, '\n');
                    if (choice == 1) {
                        createGroup();
                    } else {
                        break;
                    }
                }
            }
        }
    } while (choice != 6);
}