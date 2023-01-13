#ifndef Account_H
#define Account_H

#include <string>
#include <iostream>
using namespace std;

class Account
{
private:
    string username;
    string status;
public:
    Account(string username, string status = "Regular");//default arguments
    ~Account();
    string getStatus() const;
};
#endif //Account_H