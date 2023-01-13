#include "Account.h"
#include "InvalidInput.h"
#include <string>
#include <iostream>
using namespace std;

//Constructor optional status :"VIP", "Owner", or "Regular"
Account :: Account(string username, string status ) {
    this->username = username;
    this->status = status;
}

//Destructor
Account ::~Account(){
    cout << "Account removed.\n";
}

//getter function to return the status of the account
string Account ::getStatus() const {
    return this->status;
}