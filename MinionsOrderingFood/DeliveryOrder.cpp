#include "DeliveryOrder.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Initializing constant static member
const float DeliveryOrder::taxRate = 0.0887;
const int   DeliveryOrder::deliveryRate = 2;

//Foundamental type static member is by default 0
int DeliveryOrder::orderCount;

//Static function
int DeliveryOrder::getOrderCount(){
    return DeliveryOrder::orderCount;
}

//Constructor
DeliveryOrder::DeliveryOrder(string name, string date, string phone, float miles){
    this->name = name;
    this->date = date; //month/day/year)
    this->phone = phone;
    this->miles = miles;
    orderBalance = 0;
    DeliveryOrder::orderCount++;//update the count
}

DeliveryOrder::~DeliveryOrder(){
    cout << "DeliveryOrder destroyed.\n";
}

void DeliveryOrder::receipt() const {
    cout << "Order Detail:" << "\n";
    cout << "\tName: " << name << "\n";
    cout << "\tDate: " << date << "\n";
    cout << "\tPhone: " << phone << "\n";
    cout <<setprecision(2) << fixed;
    cout << "\tOrder Balance: $" << orderBalance << endl;
}

//calculate the delivery order balance by adding the tax and delivery fee
float DeliveryOrder::getTotalBalance() const {
    return orderBalance * (1 + DeliveryOrder::taxRate) + miles * DeliveryOrder::deliveryRate;;
}