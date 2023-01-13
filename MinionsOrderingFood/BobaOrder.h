#ifndef BobaOrder_H
#define BobaOrder_H

#include "DeliveryOrder.h"
#include <string>
#include <iostream>
using namespace std;

class BobaOrder :public DeliveryOrder{
private:
    string shopName;
    static int drinksCount;
public:
    BobaOrder(string name, string date, string phone, float miles, string shopName);
    ~BobaOrder();
    void receipt() const; //override the receipt() function
    float VIPdiscount() const; //overriding a base class's pure virtual function 
    float addDrink(string drinkName,bool addBoba = true, int count = 1);//default arguments
};

#endif //BobaOrder_H