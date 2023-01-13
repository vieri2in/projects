#ifndef FoodOrder_H
#define FoodOrder_H

#include "DeliveryOrder.h"
#include <string>
#include <iostream>
using namespace std;

class FoodOrder :public DeliveryOrder{
private:
    string restaurantName;
    static int foodCount;
public:
    FoodOrder(string name, string date, string phone, float miles, string restaurantName);
    ~FoodOrder();
    void receipt() const; //override the receipt() function
    float VIPdiscount() const; //overriding a base class's pure virtual function 
    float addFood(string courseName, int sides = 0, bool addSoup = false );//default arguments

};
#endif //FoodOrder_H