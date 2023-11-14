#include <iostream>
#include "functions.h"

using namespace std;

void App() {
    char choice;
    cout << " ┌──────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << " |\t\t\t\tWelcome To Employee Management   \t\t\t|" << endl;
    cout << " └──────────────────────────────────────────────────────────────────────────────────────┘" << endl;
    cout << "Press 'l' to Login. \n";
    cout << "Don't have account? Press 's' to create account : ";
    cin >> choice;
    cin.ignore();

    switch (tolower(choice)) {
        case 's': {
            signUp();
            cout << "Now You can Login to Here...\n";
        }
        case 'l': {
            char role = login();
            if(role == 'a'){
                adminPage();
            }
            else if(role=='u'){
//                userPage();
            }
            else if(role=='c'){
//                chefPage();
            }
            else if(role=='s'){
//                staffPage();
            }
            break;
        }
        default: {
            cout << "Invalid Input";
            break;
        }
    }
}

int main (){
    App();

    return 0;
}