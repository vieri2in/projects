#include <string>
#include <iostream>
using namespace std;

class InvalidInput
{
public:
    InvalidInput(string input) : message("Invalid input \"" + input + "\".")
    {}
    void print_reason() const {cout << message <<endl;} 
private:
    const string message;
};