#include <iostream>
#include <fstream>
#include <sstream>
#include "functions.h"

using namespace std;

struct userData {
    string fullName;
    string userName;
    string email;
    string password;
    string confirmPassword;
    string role;
};

static string roles[5] = {"manager", "employee"};
const int noOfUsers = 200;
const int noOfFields = 6;
int activeUser;
string usersInfo[noOfUsers][noOfFields];
string employeeInfo[noOfUsers][noOfFields];

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
                  >> usersInfo[i][5];
        i++;
    }
    UsersFile.close();

    return i;
}

int getEmployees() {
    int i = 0;
    fstream UsersFile("Employees.txt", ios::in);
    if (!UsersFile.is_open()) {
        cout << "\nfile is not opened!!!\n";
        return 0;
    }
    while (!UsersFile.eof()) {
        UsersFile >> employeeInfo[i][0]
                  >> employeeInfo[i][1]
                  >> employeeInfo[i][2]
                  >> employeeInfo[i][3]
                  >> employeeInfo[i][4]
                  >> employeeInfo[i][5];
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


    cout << "Which type of Account you Want to Create \n1. Manager \n2. Employee \nEnter Type Number : ";
    cin >> type;

    cout << "\tEnter Full Name : ";
    cin >> userInfo.fullName;

    int itr;
    while (1) {
        itr = 1;
        cout << "\tEnter User Name : ";
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
        cout << "\tEnter Email: ";
        cin >> userInfo.email;
        for (int i = 0; i < nUsers; ++i) {
            if (userInfo.email == usersInfo[i][3]) {
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
               << userInfo.email << " "
               << userInfo.password << " "
               << roles[type - 1] << endl;
    }
    LoginData.close();
}


// Login Module

template<class T>

bool loginAuth(T userName, T pass) {
    getExistingUsers();
    for (int i = 0; i < noOfUsers; ++i) {
        if ((userName == usersInfo[i][2] || userName == usersInfo[i][3]) && pass == usersInfo[i][4]) {
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
            role = usersInfo[activeUser][5];
            cout << "\nHi " << usersInfo[activeUser][1] << "\nWelcome on the Board !\n";
            break;
        } else {
            cout << "\n\tCredentials didn't match. Please Try Again.\n\n";
        }
    }

    return role[0];
}

// Admin Controls

void addEmployee() {
    int nEmployees = getEmployees(), itr, nUsers = getExistingUsers();
    userData EmployeeData;
    int lastUserId = stoi(usersInfo[nUsers - 2][0]);
    int lastEmpId = stoi(employeeInfo[nEmployees - 2][0]);
    float salary;

    cout << " ┌─────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t ADD EMPLOYEE... \t\t\t   |" << endl;
    cout << " └─────────────────────────────────────────────────────────────────┘" << endl;

    cout << "\tEnter Employee Name : ";
    cin >> EmployeeData.fullName;


    while (1) {
        itr = 1;
        cout << "\tEnter User Name for Employee : ";
        cin >> EmployeeData.userName;
        for (int i = 0; i < nUsers; ++i) {
            if (EmployeeData.userName == usersInfo[i][2]) {
                ++itr;
            }
        }
        if (itr > 1) {
            cout << "\n\tEmployee already Exists With this User Name. Try with New One.\n\n";
        } else {
            break;
        }
    }

    while (1) {
        itr = 1;
        cout << "\tEnter Email: ";
        cin >> EmployeeData.email;
        for (int i = 0; i < nUsers; ++i) {
            if (EmployeeData.email == usersInfo[i][3]) {
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
        cin >> EmployeeData.password;
        if (EmployeeData.password.length() >= 8) {
            break;
        }
        cout << "\n\tPassword must be at least 8 characters.\n\n";
    }
    do {
        cout << "\tConfirm Password : ";
        cin >> EmployeeData.confirmPassword;
        if (EmployeeData.confirmPassword != EmployeeData.password) {
            cout << "\n\tPasswords Must be Same.\n\n";
        }
    } while (EmployeeData.confirmPassword != EmployeeData.password);

    cout << "\tEnter Salary of Employee : ";
    cin >> salary;


    cout << "\n\tAccount for Employee has been created successfully.\n";

    ofstream LoginData("usersInfo.txt", ios::app);
    if (LoginData.is_open()) {
        LoginData << lastUserId + 1 << " "
                  << EmployeeData.fullName << " "
                  << EmployeeData.userName << " "
                  << EmployeeData.email << " "
                  << EmployeeData.password << " "
                  << roles[1] << endl;
    }
    LoginData.close();

    ofstream EmployeesData("Employees.txt", ios::app);
    if (EmployeesData.is_open()) {
        EmployeesData << lastEmpId + 1 << " "
                  << lastUserId + 1 << " "
                  << EmployeeData.fullName << " "
                  << "Present" << " "
                  << "TestProject" << " "
                  << salary << endl;
    }
    EmployeesData.close();

}

void adminPage() {
    addEmployee();
}